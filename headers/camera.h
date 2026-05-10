#pragma once
#include "quaternion.h"
#include "vector3.h"

class Camera {
public:
  vector3 position = {0, 0, 0};
  Quaternion rotation = {1, 0, 0, 0};

  float D = 2.0f;
  float nearPlane = 0.1f;
  float sensitivity = 0.1f;
  float speed = 0.5f;

  void rotateY(const int &a);
};

inline void Camera::rotateY(const int &a) {
  rotation = rotation * Quaternion::FromAxisAngle({0, 1, 0}, a * sensitivity);
}
