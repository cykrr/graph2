#include "entt/entity/registry.hpp"

void create_entity_draw(entt::registry & r);
void entity_picker(entt::registry &r, entt::entity &selection, bool &selected);
void selected_entity_view_draw(entt::registry & r, entt::entity & selection);
