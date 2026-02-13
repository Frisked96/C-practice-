#include "actions.hpp"
#include "components.hpp"
#include "game_map.hpp"

void MoveAction::perform(entt::registry& registry, entt::entity entity, const Game_map& map) {
  if (registry.all_of<Position>(entity)) {
    auto &pos = registry.get<Position>(entity);
    int new_x = pos.p.x + dx;
    int new_y = pos.p.y + dy;

    if (map.is_walkable(new_x, new_y)) {
      pos.p.x = new_x;
      pos.p.y = new_y;
    }
  }
}

void QuitAction::perform(entt::registry& registry, entt::entity entity, const Game_map& /*map*/) {
  registry.emplace_or_replace<QuitTag>(entity);
}
