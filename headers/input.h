#pragma once
#include "camera.h"
#include "player.h"
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_scancode.h>
#include <map>
class Input {
public:
  static void parseInput(std::map<SDL_Scancode, bool> &keyStatus, Player &pl);
};

inline void Input::parseInput(std::map<SDL_Scancode, bool> &keyStatus,
                              Player &pl) {
  if (keyStatus[SDL_SCANCODE_W]) {
    pl.move({0, 0, 1});
  }
  if (keyStatus[SDL_SCANCODE_S]) {
    pl.move({0, 0, -1});
  }
  if (keyStatus[SDL_SCANCODE_D]) {
    pl.camera.rotateY(1);
  }
  if (keyStatus[SDL_SCANCODE_A]) {
    pl.camera.rotateY(-1);
  }
}
