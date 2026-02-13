#pragma once
#include <entt/entt.hpp>

class Entity {
public:
  Entity() = default;
  Entity(entt::entity handle, entt::registry* registry)
      : entity_handle(handle), registry(registry) {}

  template <typename T, typename... Args>
  T& add_component(Args&&... args) {
    return registry->emplace<T>(entity_handle, std::forward<Args>(args)...);
  }

  template <typename T>
  T& get_component() {
    return registry->get<T>(entity_handle);
  }

  template <typename T>
  bool has_component() {
    return registry->all_of<T>(entity_handle);
  }

  operator entt::entity() const { return entity_handle; }

private:
  entt::entity entity_handle{entt::null};
  entt::registry* registry{nullptr};
};
