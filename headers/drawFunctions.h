#pragma once

#include "settings.h"
#include "triangele.h"
#include "vector2.h"
#include <SDL3/SDL_render.h>

class DrawLib {
public:
  static vector2 toScreen(const vector2 &p);

  static void drawPoint(SDL_Renderer *rn, vector2 v);

  static void drawTriangle(SDL_Renderer *rn, const Triangle2D &p);

  static void drawFilledTriangle(SDL_Renderer *rn, const Triangle2D &p);
};

inline vector2 DrawLib::toScreen(const vector2 &p) {
  return {(WinSettings::WIDTH / 2.0f * p.x) + WinSettings::WIDTH / 2.0f, // {{{
          WinSettings::HEIGHT / 2.0f - (WinSettings::HEIGHT / 2.0f * p.y)};
} // }}}

inline void DrawLib::drawPoint(SDL_Renderer *rn, vector2 v) {
  SDL_SetRenderDrawColor(rn, 255, 255, 255, 255); // {{{
  vector2 V_sc = toScreen(v);
  const SDL_FRect rect = {V_sc.x - 5, (V_sc.y - 5), 10, 10};
  SDL_RenderFillRect(rn, &rect);
} // }}}

inline void DrawLib::drawTriangle(SDL_Renderer *rn, const Triangle2D &p) {
  vector2 A_sc = toScreen(p.vertices[0]); // {{{
  vector2 B_sc = toScreen(p.vertices[1]);
  vector2 C_sc = toScreen(p.vertices[2]);
  SDL_SetRenderDrawColor(rn, 0, 0, 255, 255);
  SDL_RenderLine(rn, A_sc.x, A_sc.y, B_sc.x, B_sc.y);
  SDL_RenderLine(rn, A_sc.x, A_sc.y, C_sc.x, C_sc.y);
  SDL_RenderLine(rn, C_sc.x, C_sc.y, B_sc.x, B_sc.y);
} // }}}

inline void DrawLib::drawFilledTriangle(SDL_Renderer *rn, const Triangle2D &p) {
  vector2 A_sc = toScreen(p.vertices[0]); // {{{
  vector2 B_sc = toScreen(p.vertices[1]);
  vector2 C_sc = toScreen(p.vertices[2]);

  // Can change the "1" to desired color on screen
  float colorR = 1 * Settings::lightStrength * p.lightIntensity;
  float colorG = 1 * Settings::lightStrength * p.lightIntensity;
  float colorB = 1 * Settings::lightStrength * p.lightIntensity;

  SDL_Vertex geo[3] = {{A_sc.x, A_sc.y, colorR, colorG, colorB, 255},
                       {B_sc.x, B_sc.y, colorR, colorG, colorB, 255},
                       {C_sc.x, C_sc.y, colorR, colorG, colorB, 255}};

  SDL_RenderGeometry(rn, nullptr, geo, 3, nullptr, 0);
} // }}}
