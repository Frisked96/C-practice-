#pragma once
#include "point.hpp"

struct Position {
  Point p;
};

struct Sprite {
  char glyph;
};

struct Name {
  const char* name;
};

struct QuitTag {};
