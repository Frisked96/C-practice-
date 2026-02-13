#pragma once

#include "point.hpp"

struct Tile {
  enum Type { Street, Building, NeonSign };

  Point pos;
  bool is_walkable;
  char glyph;

  Tile() : pos({0, 0}), is_walkable(true), glyph('.') {}

  Tile(Type t, int x, int y) : pos({x, y}) {
    switch (t) {
      case Street:
        is_walkable = true;
        glyph = '.'; 
        break;
      case Building:
        is_walkable = false;
        glyph = '#'; 
        break;
      case NeonSign:
        is_walkable = false;
        glyph = '*'; 
        break;
    }
  }
};
