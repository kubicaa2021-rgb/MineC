#pragma once
#include "camera.h"
#include "vector3.h"
class Player {
public:
  Camera camera = Camera();
  vector3 position = {0, 0, 0};
  Player();

  void move(const vector3 &v);

private:
  vector3 cameraOffset = {0, 1, 0};
};

inline Player::Player() { camera.position = camera.position + cameraOffset; }

inline void Player::move(const vector3 &v) {
  position += rotatePointQuater(v, camera.rotation);
  camera.position = position + cameraOffset;
}
