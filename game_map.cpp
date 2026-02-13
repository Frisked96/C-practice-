#include "game_map.hpp"
#include "FastNoiseLite.h"

Game_map::Game_map() : width(0), height(0), depth(0) {}

void Game_map::generate(int w, int h, int d) {
  width = w;
  height = h;
  depth = d;

  tiles.assign(width * height * depth, Tile());

  FastNoiseLite noise;
  noise.SetSeed(1337);
  noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
  noise.SetFrequency(0.1f); 

  for (int z = 0; z < depth; ++z) {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        float value = noise.GetNoise((float)x, (float)y, (float)z * 10.0f);
        
        // Threshold for "Buildings" vs "Streets"
        if (value > 0.2f) {
          tiles[z * (width * height) + y * width + x] = Tile(Tile::Wall, x, y);
        } else {
          tiles[z * (width * height) + y * width + x] = Tile(Tile::Floor, x, y);
        }
      }
    }
  }
}
