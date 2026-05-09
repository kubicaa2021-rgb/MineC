#pragma once
#include "vector3.h"
#include <vector>
class Mesh {
public:
  std::vector<vector3> vertices;
  std::vector<int> indices;

  Mesh() = default;

  Mesh(const std::vector<vector3> &v, const std::vector<int> &i)
      : vertices(v), indices(i) {};
};
