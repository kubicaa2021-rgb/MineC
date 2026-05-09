#pragma once
#include <cstdlib>
class Util {
public:
  static inline bool isApxEqual(const float &A, const float &B,
                                const float &C) {
    return (std::abs(A - B) < C);
  }
};
