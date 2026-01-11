
#pragma once
#include <cstdint>
// A fast, thread-safe PRNG for simulation/game/rendering, it is not intended
// for security-sensitive randomness. This random generator utility guarantees
// to be deterministic within the same platform/toolchain/lib version. The PNRG
// implementation may change under the hood therefore, the utility cannot
// guarantee deterministic behavior across different versions.
//
// Calling seed affects only the calling thread and if seed is not called a
// fixed default is used. The default fixed default seed (0x9E3779B97F4A7C15).
// If 0 is passed as input to seed then the default seed value will be used
// automatically.

namespace util::random {
// Returns a uniformly distributed interger in [min, max] (inclusive)
// throws std::invalid_argument if min > max
// thread safe as each thread has its own engine
int rand_int(int min, int max);

// Returns a random integer between 0 and the given max inclusive
int rand_int(int max);

// Returns a uniformly distributed real number in [min, max).
// Throws std::invalid_argument if min >= max.
// Thread-safe (thread-local RNG).
double rand_real(double min, double max);

double rand_real(double max);

// Affects the RNG for the current thread only - thread safe
void seed(std::uint64_t value) noexcept;

// calling seed with no parameters will seed the RNG
// with current time in milliseoncds
void seed() noexcept;

uint64_t current_milli();

} // namespace util::random
