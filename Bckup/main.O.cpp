#include "camera.h"
#include "cube.h"
#include "drawFunctions.h"
#include "quaternion.h"
#include "settings.h"
#include "triangele.h"
#include "vector3.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_stdinc.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Make cube.h file and rendering function to render cube based on its center
// and just compute the centers
//  and also a rotation vector

Camera camera = Camera();

struct {
  vector3 pos = {0.0f, -3.0f, 10.0f};
  vector3 rotation;
  float R = 1;
  float G = 1;
  float B = 1;
} object;

float angle_Y = 0.0f;
std::vector<vector3> vertices;
std::vector<int> triangles;

std::vector<vector3> mapCubes;

void loadModel(std::string path);

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
  loadModel(Settings::filePath);

  // Main loop
  bool done = false;
  SDL_Event event;

  while (!done) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        done = true;
      }
      if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
        case SDLK_W:
          camera.position.z += 1;
          break;
        case SDLK_S:
          camera.position.z -= 1;
          break;
        }
      }
    }
    SDL_SetRenderDrawColor(renderer, 10, 10, 30, 255);
    SDL_RenderClear(renderer);

    // Drawing and sorting triangles
    std::vector<Triangle2D> TrianglesDraw2D; // {{{
    // float cosY = std::cos(object.rotation.y);
    // float sinY = std::sin(object.rotation.y);
    vector3 rotAxis{0, 1, 0};
    float sinAngle = sinf(object.rotation.y / 2);

    Quaternion quan_rot{cosf(object.rotation.y / 2), rotAxis.x * sinAngle,
                        rotAxis.y * sinAngle, rotAxis.z * sinAngle};

    for (int i = 0; i < triangles.size(); i += 3) {
      vector3 vec[] = {vertices[triangles[i]], vertices[triangles[i + 1]],
                       vertices[triangles[i + 2]]};

      //      vec[0] = rotateY(vec[0], sinY, cosY);
      //      vec[1] = rotateY(vec[1], sinY, cosY);
      //      vec[2] = rotateY(vec[2], sinY, cosY);

      vec[0] = rotatePointQuater(vec[0], quan_rot);
      vec[1] = rotatePointQuater(vec[1], quan_rot);
      vec[2] = rotatePointQuater(vec[2], quan_rot);

      vec[0] += object.pos;
      vec[1] += object.pos;
      vec[2] += object.pos;

      vector3 edge1 = vec[1] - vec[0];
      vector3 edge2 = vec[2] - vec[0];

      vector3 normal = crossProduct(edge1, edge2);
      normal = normalizeVector(normal);
      std::array<vector2, 3> vec2 = {convert3Dto2DPoint(vec[0], camera.D),
                                     convert3Dto2DPoint(vec[1], camera.D),
                                     convert3Dto2DPoint(vec[2], camera.D)};

      // Calculate if triangle visible
      vector3 view = camera.position - vec[0];
      float dotViewNormal =
          normal.x * view.x + normal.y * view.y + normal.z * view.z;
      if (dotViewNormal <= 0) {
        continue; // swap to <= or >= 0 renders back side (based on CCW or CW)
                  // also change LightI plus/minus because it is flipped
      }

      // Calculate avg distance from camera
      float avgZ = (vec[0].z + vec[1].z + vec[2].z) / 3.0f;
      float avgY = (vec[0].y + vec[1].y + vec[2].y) / 3.0f;
      if (avgY >= 1)
        continue;

      float lightI = -(Settings::lightDirection.x * normal.x +
                       Settings::lightDirection.y * normal.y +
                       Settings::lightDirection.z * normal.z);
      TrianglesDraw2D.push_back({vec2, avgZ, normal, std::max(0.0f, lightI)});
    }

    // Sort by distance from camera
    std::sort(TrianglesDraw2D.begin(), TrianglesDraw2D.end(),
              [](const Triangle2D &a, const Triangle2D &b) {
                return a.avgZ > b.avgZ;
              });

    // Draw ordered by distance
    for (const Triangle2D &a : TrianglesDraw2D) {
      DrawLib::drawFilledTriangle(renderer, a); // Shaded faces overlapping
      // drawTriangle(renderer, a); // Wireframe
    }
    object.rotation.y += SDL_PI_F / 80;

    // Swap buffers and present
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

void loadModel(std::string path) {
  std::ifstream file(path); // {{{
  if (!file.is_open()) {
    std::cerr << "Error opening file.\n";
  }

  std::string line;

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string type;

    ss >> type;

    if (type == "v") {
      float x, y, z;
      ss >> x >> y >> z;
      vertices.emplace_back(
          x, y, z); // Chanege z and y if model look like laying on side

    } else if (type == "f") {
      std::string v1, v2, v3;
      ss >> v1 >> v2 >> v3;

      auto getIndex = [](std::string &s) {
        std::stringstream strS(s);
        int v, t, n; //
        char ch;
        strS >> v >> ch >> t >> ch >> n;
        return v - 1;
      };

      triangles.emplace_back(getIndex(v1));
      triangles.emplace_back(getIndex(v2));
      triangles.emplace_back(getIndex(v3));
    }
  }
  file.close();
} // }}}
