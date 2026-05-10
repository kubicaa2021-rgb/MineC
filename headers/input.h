#pragma once
#include "camera.h"
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_scancode.h>
#include <map>
class Input {
public:
  static void parseInput(std::map<SDL_Scancode, bool> &keyStatus, Camera &cam);
};

inline void Input::parseInput(std::map<SDL_Scancode, bool> &keyStatus,
                              Camera &cam) {

  if (keyStatus[SDL_SCANCODE_W]) {
    cam.move({0, 0, 1});
  }
  if (keyStatus[SDL_SCANCODE_S]) {
    cam.move({0, 0, -1});
  }
  if (keyStatus[SDL_SCANCODE_D]) {
    cam.rotateY(1);
  }
  if (keyStatus[SDL_SCANCODE_A]) {
    cam.rotateY(-1);
  }
}
