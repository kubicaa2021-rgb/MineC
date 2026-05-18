#pragma once
#include "camera.h"
#include "player.h"
#include "settings.h"
#include "vector2.h"
#include "vector3.h"
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_scancode.h>
#include <iostream>
#include <map>
#include <ostream>
class Input {
public:
  static void parseInput(std::map<SDL_Scancode, bool> &keyStatus, Player &pl);
  void parseMouseInput(const vector2 &mv, Player &pl);

private:
  vector2 lastMove;
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
    //    pl.camera.rotateY(1);
    pl.move({1, 0, 0});
  }
  if (keyStatus[SDL_SCANCODE_A]) {
    // pl.camera.rotateY(-1);
    pl.move({-1, 0, 0});
  }
}

inline void Input::parseMouseInput(const vector2 &mv, Player &pl) {
  pl.camera.rotateY((lastMove.x - mv.x) * Settings::MouseSens);
  // pl.camera.rotateX((lastMove.y - mv.y) * Settings::MouseSens);
  std::cout << "X: " << lastMove.x - mv.x << "Y: " << lastMove.y - mv.y
            << std::endl;

  lastMove = mv;
}
