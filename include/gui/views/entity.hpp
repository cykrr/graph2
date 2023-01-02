#include "entt/entity/registry.hpp"
namespace Views {
namespace Entity {
void create(entt::registry & r, entt::entity & selection, bool &selected);
void pick(entt::registry &r, entt::entity &selection, bool &selected);
void view(entt::registry & r, entt::entity & selection);
    }
  }
