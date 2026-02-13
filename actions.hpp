#pragma once
#include "point.hpp"
#include <entt/entt.hpp>

class Game_map;

class Action {
public:
  virtual ~Action() = default;
  virtual void perform(entt::registry& registry, entt::entity entity, const Game_map& map) = 0;
};

class MoveAction : public Action {
public:
  MoveAction(int dx, int dy) : dx(dx), dy(dy) {}
  void perform(entt::registry& registry, entt::entity entity, const Game_map& map) override;

private:
  int dx, dy;
};

class QuitAction : public Action {
public:
  void perform(entt::registry& registry, entt::entity entity, const Game_map& map) override;
};
