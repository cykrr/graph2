#include "entities/triangle.hpp"
#include "components/drawable.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"
#include <entt/entity/fwd.hpp>
#include "wrappers/gl.hpp"
#include "entity.hpp"
static float vertices[] =  {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

entt::entity create_triangle(entt::registry & r) {
  return create_entity(r, vertices, 3);
}
