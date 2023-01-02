#include <entt/entity/fwd.hpp>
#include "wrappers/gl.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "entity.hpp"

#include "entities/triangle.hpp"

static float vertices[] =  {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

Entity create_triangle(entt::registry & r) {
  static VAO vao;
  static VBO vbo(BufferType::array_buffer);
  return Entity(r, vertices, 3, vao, vbo);
}
