#pragma once
#include <entt/entt.hpp>
#include "game_map.hpp"
#include "render.hpp"
#include "input_handler.hpp"
#include "entity.hpp"

class Engine {
public:
  Engine();
  ~Engine();

  void init();
  void update();
  void render();

  void stop() { running = false; }
  bool is_running() const { return running; }

private:
  entt::registry registry;
  Game_map map;
  Renderer renderer;
  InputHandler input_handler;
  Entity player;
  bool running;
};
