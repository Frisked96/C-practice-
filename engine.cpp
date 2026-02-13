#include "engine.hpp"
#include "components.hpp"
#include <iostream>

Engine::Engine() : running(true) {}
Engine::~Engine() {}

void Engine::init() {
  map.generate(1000, 1000);

  int start_x = 500;
  int start_y = 500;
  
  // Find nearest walkable tile
  while (!map.is_walkable(start_x, start_y)) {
    start_x++;
    if (start_x >= map.get_width()) {
      start_x = 0;
      start_y++;
    }
  }

  player = Entity(registry.create(), &registry);
  player.add_component<Name>("Player");
  player.add_component<Position>(Point{start_x, start_y});
  player.add_component<Sprite>('@');
}

void Engine::update() {
  auto action = input_handler.handle_input();
  if (action) {
    action->perform(registry, player, map);
  }

  if (player.has_component<QuitTag>()) {
    stop();
  }
}

void Engine::render() {
  if (player.has_component<Position>()) {
    renderer.render(map, registry, player.get_component<Position>().p);
  }
}
