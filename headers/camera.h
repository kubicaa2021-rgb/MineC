#pragma once
#include "quaternion.h"
#include "vector3.h"

class Camera {
public:
  float D = 2.0f;
  float nearPlane = 0.1f;
  vector3 position = {0, 0, 0};
  Quaternion rotation = {1, 0, 0, 0};
  vector3 lookAngle;
};
