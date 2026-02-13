#pragma once
#include <entt/entt.hpp>
#include "game_map.hpp"

class Renderer {
public:
  Renderer();
  ~Renderer();

  void render(const Game_map& map, entt::registry& registry, Point camera_pos);

private:
  const int VIEW_W = 20;
  const int VIEW_H = 10;
};
