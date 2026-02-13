#pragma once
#include <vector>
#include "tile.hpp"

class Game_map {
public:
  Game_map();
  void generate(int w, int h, int d = 1); // d for depth/z-levels

  int get_width() const { return width; }
  int get_height() const { return height; }
  int get_depth() const { return depth; }

  const Tile& get_tile(int x, int y, int z = 0) const {
    return tiles[z * (width * height) + y * width + x];
  }

  bool is_in_bounds(int x, int y, int z = 0) const {
    return x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < depth;
  }

  bool is_walkable(int x, int y, int z = 0) const {
    return is_in_bounds(x, y, z) && get_tile(x, y, z).is_walkable;
  }

private:
  int width;
  int height;
  int depth;
  std::vector<Tile> tiles;
};
