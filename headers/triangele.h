#pragma once
#include "vector2.h"
#include "vector3.h"
#include <array>

class Triangle {
public:
  std::array<vector3, 3> vertex;
};
class Triangle2D {
public:
  std::array<vector2, 3> vertices;
  float avgZ;
  vector3 normal;
  float lightIntensity;
};
