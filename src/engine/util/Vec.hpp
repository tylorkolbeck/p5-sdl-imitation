#pragma once
#include <cmath>

struct Vec {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  Vec() = default;

  Vec(float x_, float y_, float z_ = 0.0f) : x(x_), y(y_), z(z_) {}

  Vec operator-(const Vec &rhs) const {
    return {x - rhs.x, y - rhs.y, z - rhs.z};
  }

  Vec operator+(const Vec &rhs) const {
    return {x + rhs.x, y + rhs.y, z + rhs.z};
  }

  Vec operator*(float value) const { return {x * value, y * value, z * value}; }

  Vec &operator+=(const Vec &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  Vec &operator*=(float s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  Vec &operator-=(const Vec &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  void Limit(float max) {
    float lenSq = LengthSq();
    float maxSq = max * max;

    if (lenSq > maxSq && lenSq > 0.0f) {
      float scale = max / std::sqrt(lenSq);
      *this *= scale;
    }
  }

  float LengthSq() const { return x * x + y * y + z * z; }
};

inline float Mag(const Vec &vec) { return sqrt(vec.LengthSq()); }
