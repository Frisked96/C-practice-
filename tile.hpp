#pragma once

#include "point.hpp"

struct Tile {
  enum Type { Floor, Wall };

  Point pos;
  bool is_walkable;
  char glyph;

  Tile() : pos({0, 0}), is_walkable(true), glyph('.') {}

  Tile(Type t, int x, int y) : pos({x, y}) {
    switch (t) {
      case Floor:
        is_walkable = true;
        glyph = '.';
        break;
      case Wall:
        is_walkable = false;
        glyph = '#';
        break;
    }
  }
};
