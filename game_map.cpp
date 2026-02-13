#include "game_map.hpp"
#include "FastNoiseLite.h"

Game_map::Game_map() : width(0), height(0), depth(0) {}

void Game_map::generate(int w, int h, int d) {
  width = w;
  height = h;
  depth = d;

  tiles.assign(width * height * depth, Tile());

  FastNoiseLite noise;
  noise.SetSeed(42);
  noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
  noise.SetFrequency(0.15f);

  for (int z = 0; z < depth; ++z) {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        int idx = z * (width * height) + y * width + x;

        // 1. Major Avenues (3 tiles wide)
        if ((x % 60) < 3 || (y % 60) < 3) {
          tiles[idx] = Tile(Tile::Street, x, y);
          continue;
        }

        // 2. Minor Alleys (1 tile wide)
        if ((x % 20) == 0 || (y % 20) == 0) {
          tiles[idx] = Tile(Tile::Street, x, y);
          continue;
        }

        // 3. Dense Building Blocks
        float val = noise.GetNoise((float)x, (float)y);
        
        if (val > -0.1f) {
          tiles[idx] = Tile(Tile::Building, x, y); 
        } else {
          tiles[idx] = Tile(Tile::Street, x, y);
        }

        // 4. Random Neon ads on buildings
        if (tiles[idx].glyph == '#' && (x * 7 + y * 13) % 47 == 0) {
            tiles[idx] = Tile(Tile::NeonSign, x, y);
        }
      }
    }
  }
}
