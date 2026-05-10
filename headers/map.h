#pragma once
#include "camera.h"
#include "cube.h"
#include "player.h"
#include "vector3.h"
#include <SDL3/SDL_render.h>
#include <vector>

class Map {
public:
  std::vector<Cube> mapCubes;
  SDL_Renderer *rn;
  Player *player;

  Map();
  Map(SDL_Renderer *rend, Player *pl);

  void drawMap();
  void addCube(Cube &cb);
};

inline Map::Map() {}

inline void Map::drawMap() {

  std::sort(mapCubes.begin(), mapCubes.end(),
            [this](const Cube &a, const Cube &b) {
              return vector3::getDistance(a.position, player->camera.position) >
                     vector3::getDistance(b.position, player->camera.position);
            });

  for (Cube &c : mapCubes) {
    c.drawCube(rn, player->camera);
  };
};
inline Map::Map(SDL_Renderer *rend, Player *pl) : rn(rend), player(pl) {}
inline void Map::addCube(Cube &cb) { mapCubes.emplace_back(cb); }
