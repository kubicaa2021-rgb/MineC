#pragma once

#include "vector3.h"
class WinSettings {
public:
  static constexpr int HEIGHT = 600;
  static constexpr int WIDTH = 1200;
  static constexpr float HEIGHT_to_WIDTH = HEIGHT / float(WIDTH);
};
class Settings {
public:
  static constexpr vector3 lightDirection{0.666f, -0.666f, 0.333f};

  static constexpr float MouseSens = 0.01f;

  static constexpr float lightStrength = 1.0f;

  static constexpr const char *filePath = "models/cube.obj";
};
