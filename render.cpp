#include "render.hpp"
#include "components.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

Renderer::Renderer() {}
Renderer::~Renderer() {}

void Renderer::render(const Game_map& map, entt::registry& registry, Point camera_pos) {
  std::cout << "\033[2J\033[H";

  // Calculate top-left corner of the viewport
  int start_x = std::max(0, std::min(map.get_width() - VIEW_W, camera_pos.x - VIEW_W / 2));
  int start_y = std::max(0, std::min(map.get_height() - VIEW_H, camera_pos.y - VIEW_H / 2));

  std::vector<std::string> buffer(VIEW_H, std::string(VIEW_W, ' '));

  // 1. Draw Map Tiles within viewport
  for (int y = 0; y < VIEW_H; ++y) {
    for (int x = 0; x < VIEW_W; ++x) {
      int map_x = start_x + x;
      int map_y = start_y + y;
      buffer[y][x] = map.get_tile(map_x, map_y).glyph;
    }
  }

  // 2. Overlay Entities within viewport
  auto view = registry.view<Position, Sprite>();
  for (auto entity : view) {
    auto &pos = view.get<Position>(entity);
    auto &sprite = view.get<Sprite>(entity);

    int screen_x = pos.p.x - start_x;
    int screen_y = pos.p.y - start_y;

    if (screen_x >= 0 && screen_x < VIEW_W && screen_y >= 0 && screen_y < VIEW_H) {
      buffer[screen_y][screen_x] = sprite.glyph;
    }
  }

  // 3. Print buffer
  for (const auto& line : buffer) {
    std::cout << line << "\n";
  }
}
