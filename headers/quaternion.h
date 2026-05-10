#pragma once

#include "utils.h"
#include <cmath>
class vector3;

class Quaternion {
public:
  float w, x, y, z;

  inline Quaternion operator*(const Quaternion &A) const;

  static Quaternion FromAxisAngle(const vector3 &v, const float &angle);

  inline void Normalize();
  Quaternion Inversed() const;
};

#include <vector3.h>
inline Quaternion Quaternion::FromAxisAngle(const vector3 &v,
                                            const float &angle) {
  vector3 norm = vector3::normalizeVector(v); // {{{
  float w_axis = cosf(angle / 2.0f);
  float s = sinf(angle / 2.0f);
  return {w_axis, norm.x * s, norm.y * s, norm.z * s};
}; // }}}

inline Quaternion Quaternion::operator*(const Quaternion &A) const {
  vector3 va = {x, y, z}; // {{{
  vector3 vb = {A.x, A.y, A.z};

  float newW = w * A.w - dotProduct(va, vb);
  vector3 newV = (vb * w) + (va * A.w) + crossProduct(va, vb);

  return {newW, newV.x, newV.y, newV.z};
}; // }}}
inline void Quaternion::Normalize() {
  // {{{
  float len = w * w + x * x + y * y + z * z;
  if (Util::isApxEqual(len, 0, 0.0001f)) {
    w = 1;
    x = 0;
    y = 0;
    z = 0;
  }
  float invLen = 1.0f / sqrtf(len);

  w = w * invLen;
  x = x * invLen;
  y = y * invLen;
  z = z * invLen;
}; // }}}
inline Quaternion Quaternion::Inversed() const { return {w, -x, -y, -z}; }
