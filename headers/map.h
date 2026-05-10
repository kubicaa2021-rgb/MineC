#pragma once
#include "camera.h"
#include "cube.h"
#include <SDL3/SDL_render.h>
#include <vector>

class Map {
public:
  std::vector<Cube> mapCubes;
  SDL_Renderer *rn;
  Camera *cam;

  Map();
  Map(SDL_Renderer *rend, Camera *camera);

  void drawMap();
  void addCube(Cube &cb);
};

inline Map::Map() {}

inline void Map::drawMap() {
  for (Cube &c : mapCubes) {
    c.drawCube(rn, cam);
  };
};
inline Map::Map(SDL_Renderer *rend, Camera *camera) : rn(rend), cam(camera) {}
inline void Map::addCube(Cube &cb) { mapCubes.emplace_back(cb); }
