#pragma once
#include "camera.h"
#include "drawFunctions.h"
#include "mesh.h"
#include "quaternion.h"
#include "settings.h"
#include "vector2.h"
#include "vector3.h"
#include <SDL3/SDL_render.h>
#include <algorithm>

class Cube {
public:
  inline static Mesh cubeMesh = {{
                                     // {{{
                                     {-0.5f, -0.5f, 0.5f}, // 0
                                     {0.5f, -0.5f, 0.5f},  // 1
                                     {0.5f, 0.5f, 0.5f},   // 2
                                     {-0.5f, 0.5f, 0.5f},  // 3

                                     {-0.5f, -0.5f, -0.5f}, // 4
                                     {0.5f, -0.5f, -0.5f},  // 5
                                     {0.5f, 0.5f, -0.5f},   // 6
                                     {-0.5f, 0.5f, -0.5f}   // 7
                                 },
                                 {// Front
                                  0, 1, 2, 0, 2, 3,
                                  // Right
                                  1, 5, 6, 1, 6, 2,
                                  // Back
                                  5, 4, 7, 5, 7, 6,
                                  // Left
                                  4, 0, 3, 4, 3, 7,
                                  // Top
                                  3, 2, 6, 3, 6, 7,
                                  // Bottom
                                  4, 5, 1, 4, 1, 0}}; // }}}
  vector3 position;
  Quaternion rotation = {1, 0, 0, 0};

  Cube();
  void drawCube(SDL_Renderer *rn, Camera *camera);

private:
};
inline Cube::Cube() {

};
inline void Cube::drawCube(SDL_Renderer *rn, Camera *camera) {
  rotation.Normalize();
  Quaternion qt = Quaternion::FromAxisAngle({0, 1, 0}, 0.01f);
  for (int i = 0; i < Cube::cubeMesh.indices.size(); i += 3) { // {{{
    vector3 v1, v2, v3;
    v1 = Cube::cubeMesh.vertices[Cube::cubeMesh.indices[i]];
    v2 = Cube::cubeMesh.vertices[Cube::cubeMesh.indices[i + 1]];
    v3 = Cube::cubeMesh.vertices[Cube::cubeMesh.indices[i + 2]];

    // Rotate
    v1 = rotatePointQuater(v1, rotation);
    v2 = rotatePointQuater(v2, rotation);
    v3 = rotatePointQuater(v3, rotation);

    // World space
    v1 += position;
    v2 += position;
    v3 += position;

    // Backface culling
    vector3 normal = vector3::normalizeVector(crossProduct(v2 - v1, v3 - v1));

    // Calculate if triangle visible
    vector3 view = vector3{0, 0, 0} - v1;
    if (dotProduct(normal, view) <= 0) {
      continue; // If facing away from camera dont draw it
    }

    // Camera space
    v1 -= camera->position;
    v2 -= camera->position;
    v3 -= camera->position;

    // Rotate around camera
    v1 = rotatePointQuater(v1, camera->rotation.Inversed());
    v2 = rotatePointQuater(v2, camera->rotation.Inversed());
    v3 = rotatePointQuater(v3, camera->rotation.Inversed());

    if (v1.z <= camera->nearPlane || v2.z <= camera->nearPlane ||
        v3.z <= camera->nearPlane) {
      continue;
    }

    // projection
    vector2 s1 = convert3Dto2DPoint(v1, camera->D);
    vector2 s2 = convert3Dto2DPoint(v2, camera->D);
    vector2 s3 = convert3Dto2DPoint(v3, camera->D);

    // TODO: draw triangle
    s1 = DrawLib::toScreen(s1);
    s2 = DrawLib::toScreen(s2);
    s3 = DrawLib::toScreen(s3);

    float lightI =
        std::max(0.0f, -dotProduct(Settings::lightDirection, normal));

    float colorR = 1 * Settings::lightStrength * lightI;
    float colorG = 1 * Settings::lightStrength * lightI;
    float colorB = 1 * Settings::lightStrength * lightI;

    SDL_Vertex triangle[3] = {{s1.x, s1.y, colorR, colorG, colorB, 1},
                              {s2.x, s2.y, colorR, colorG, colorB, 1},
                              {s3.x, s3.y, colorR, colorG, colorB, 1}};

    SDL_RenderGeometry(rn, nullptr, triangle, 3, nullptr, 0);
  }
} // }}}
