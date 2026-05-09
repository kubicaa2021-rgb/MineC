#pragma once
#include "quaternion.h"
#include "vector3.h"

class Camera {
public:
  float D = 2.0f;
  vector3 position = {0, 0, 0};
  Quaternion rotation;
  vector3 lookAngle;
};
