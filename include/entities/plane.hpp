#ifndef PLANE_VIEW_H
#define PLANE_VIEW_H
#include <entt/entity/fwd.hpp>
#include "entity.hpp"

static const float vertices[]  =  { 
    -1.f, 1.f, 0.f,
    1.f, 1.f, 0.f,
    -1.f, -1.f, 0.f,
    -1.f, -1.f, 0.f,
    1.f, -1.f, 0.f,
    1.f, 1.f, 0.f,
};


inline Entity create_plane(entt::registry & r)
{
  static VAO vao;
  static VBO vbo(BufferType::array_buffer);
  return Entity(r, vertices, 6, vao, vbo);
}
#endif
