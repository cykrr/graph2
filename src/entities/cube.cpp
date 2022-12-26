#include "entities/cube.hpp"
#include "components/drawable.hpp"
entt::entity create_cube(entt::registry r)
{
  entt::entity e =r.create();
  r.emplace<DrawableComponent>(e, "a");
}

