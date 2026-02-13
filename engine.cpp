#include "engine.hpp"
#include "components.hpp"
#include <iostream>

Engine::Engine() : running(true) {}
Engine::~Engine() {}

void Engine::init() {
  map.generate(1000, 1000);

  // Spawn near a major intersection to see the structure
  int start_x = 50;
  int start_y = 50;
  
  while (!map.is_walkable(start_x, start_y)) {
    start_x++;
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
