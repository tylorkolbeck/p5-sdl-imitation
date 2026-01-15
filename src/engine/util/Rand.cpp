
#include "Rand.hpp"
#include <chrono>
#include <cstdint>
#include <limits>
#include <random>
#include <stdexcept>

namespace util::random {

namespace {
// Fixed default seed
constexpr std::uint64_t DEFAULT_SEED = 0x9E3779B97F4A7C15;

// One RNG state per thread
thread_local std::uint64_t g_state = DEFAULT_SEED;

// xorshift64* (fast, small state, non-crypto)
// Produces 64 bits of pseudo-random output and updates g_state.
std::uint64_t next_u64() noexcept {
  std::uint64_t x = g_state;
  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;
  g_state = x;

  return x * 2685821657736338717ULL;
}
} // namespace

void seed(std::uint64_t value) noexcept {
  g_state = (value == 0) ? DEFAULT_SEED : value;
}

void seed() noexcept {
  std::random_device rd;

  std::uint64_t s = (static_cast<std::uint64_t>(rd()) << 32) ^
                    static_cast<std::uint64_t>(rd());

  seed(s);
}

int rand_int(int max) {
  if (max < 0) {
    throw std::invalid_argument("rand_int: max must be >= 0");
  }

  return rand_int(0, max);
}

int rand_int(int min, int max) {
  if (min > max) {
    throw std::invalid_argument("rand_int: min must be <= max");
  }

  // Safe span computation in 64-bit (avoids signed overflow)
  const std::int64_t min64 = static_cast<std::int64_t>(min);
  const std::int64_t max64 = static_cast<std::int64_t>(max);
  const std::uint64_t span = static_cast<std::uint64_t>((max64 - min64) + 1);

  const std::uint64_t u64_max = std::numeric_limits<std::uint64_t>::max();
  const std::uint64_t limit = u64_max - (u64_max % span);

  std::uint64_t r;
  do {
    r = next_u64();
  } while (r >= limit);

  const std::uint64_t offset = r % span;
  const std::int64_t result64 = min64 + static_cast<std::int64_t>(offset);
  return static_cast<int>(result64);
}

double rand_real(double min, double max) {
  if (min >= max) {
    throw std::invalid_argument("rand_real: min must be < max");
  }

  const std::uint64_t r = next_u64();

  // normalize to [0.0, 1.0)
  constexpr long double inv =
      1.0L /
      (static_cast<long double>(std::numeric_limits<std::uint64_t>::max()) +
       1.0L);

  const long double unit = static_cast<long double>(r) * inv; // [0,1)
  return min + static_cast<double>(unit * (max - min));
}

double rand_real(double max) {
  if (max <= 0) {
    throw std::invalid_argument("rand_int: max must be >= 0");
  }

  return rand_real(0.0, max);
}

uint64_t current_milli() {
  auto now = std::chrono::system_clock::now();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
      now.time_since_epoch());

  return milliseconds.count();
}
} // namespace util::random
