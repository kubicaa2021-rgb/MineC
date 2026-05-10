#include "camera.h"
#include "cube.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "quaternion.h"
#include "settings.h"
#include "vector3.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <map>

Player player = Player();
Map map = Map();

int main(int argc, char *argv[]) {
  // {{{
  // SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "x11");

  SDL_Window *window = SDL_CreateWindow("My renderer", WinSettings::WIDTH,
                                        WinSettings::HEIGHT, 0);

  if (!window) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s",
                 SDL_GetError());
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s",
                 SDL_GetError());
    return 1;
  }
  if (SDL_SetRenderVSync(renderer, 1) == false) {
    SDL_Log("Could not enable VSync! SDL error: %s\n", SDL_GetError());
  }
  SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_ADAPTIVE);
  // }}}

  map.player = &player;
  map.rn = renderer;

  Quaternion qt = Quaternion::FromAxisAngle({0, 1, 0}, 0.1f);

  Cube temp = Cube();
  Cube temp2 = Cube();

  temp.position = {0, 0, 5};
  temp2.position = {-1, 0, 8};
  temp2.rotation = {0, 1, 0, 2};
  temp2.rotation.Normalize();

  map.addCube(temp);
  map.addCube(temp2);

  // Main loop
  bool done = false;
  SDL_Event event;
  std::map<SDL_Scancode, bool> keyState;

  while (!done) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        done = true;
      } else if (event.type == SDL_EVENT_KEY_DOWN) {
        keyState[event.key.scancode] = true;
      } else if (event.type == SDL_EVENT_KEY_UP) {
        keyState[event.key.scancode] = false;
      }
    }

    Input::parseInput(keyState, player);

    SDL_SetRenderDrawColor(renderer, 10, 10, 30, 255);
    SDL_RenderClear(renderer);
    // map.mapCubes[0].rotation = map.mapCubes[0].rotation * qt;

    map.drawMap();

    // Swap buffers and present
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
