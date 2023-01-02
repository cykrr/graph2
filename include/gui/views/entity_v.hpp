#ifndef ENT_VIEW
#define ENT_VIEW
#include "gui/views.hpp"
#include "entity.hpp"
namespace Views{
namespace VEntity {
  void create(entt::registry & r, struct Entity & selection, bool &selected);
  void pick(entt::registry &r, struct Entity &selection, bool &selected);
  void view(struct Entity & selection);
}
}

#endif
