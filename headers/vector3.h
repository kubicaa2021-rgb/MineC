#pragma once
#include "vector2.h"
#include <cmath>

class vector3 {

public:
  float x, y, z;
  constexpr vector3(float x, float y, float z) : x(x), y(y), z(z) {}
  vector3() : x(0), y(0), z(0) {}

  vector3 operator+(const vector3 &A) const {
    return {x + A.x, y + A.y, z + A.z};
  }
  vector3 operator-(const vector3 &A) const {
    return {x - A.x, y - A.y, z - A.z};
  }
  vector3 operator*(const float &A) const { return {x * A, y * A, z * A}; }

  vector3 &operator+=(const vector3 &A) {
    x += A.x;
    y += A.y;
    z += A.z;
    return *this;
  }
  vector3 &operator-=(const vector3 &A) {
    x -= A.x;
    y -= A.y;
    z -= A.z;
    return *this;
  }

  static vector3 normalizeVector(const vector3 &A);

  inline vector3 crossProduct(const vector3 &A, const vector3 &B);
};
inline vector3 vector3::normalizeVector(const vector3 &A) {
  float len, invLen; // {{{
  len = sqrt(A.x * A.x + A.y * A.y + A.z * A.z);
  if (len == 0)
    return {0, 0, 0};
  invLen = 1.0f / len;
  return {A.x * invLen, A.y * invLen, A.z * invLen};
} // }}}

inline float dotProduct(const vector3 &A, const vector3 &B) {
  return A.x * B.x + A.y * B.y + A.z * B.z; // {{{
} // }}}

inline vector3 crossProduct(const vector3 &A, const vector3 &B) {
  float x, y, z; // {{{
  x = A.y * B.z - A.z * B.y;
  y = A.z * B.x - A.x * B.z;
  z = A.x * B.y - A.y * B.x;
  return {x, y, z};
} // }}}

#include "quaternion.h"
inline vector3 rotateY(const vector3 &v, float sin, float cos) {
  float x, y, z; // {{{
  y = v.y;
  x = v.x * cos - v.z * sin;
  z = v.x * sin + v.z * cos;
  return {x, y, z};
} // }}}

inline vector2 convert3Dto2DPoint(const vector3 &v, int D) {
  if (v.z <= 0.1f) { // {{{
    return {0, 0};
  }
  float d_z = D * (1 / v.z);
  float x = v.x * d_z;
  float y = v.y * d_z;
  return {x, y};
} // }}}

inline vector3 rotatePointQuater(const vector3 &v, const Quaternion &q) {
  Quaternion v_quat = {1, v.x, v.y, v.z}; // {{{
  v_quat.Normalize();

  Quaternion q_rev = {q.w, -q.x, -q.y, -q.z};

  Quaternion v_rotated = (q * v_quat) * q_rev;

  return {v_rotated.x, v_rotated.y, v_rotated.z};
} // }}}
