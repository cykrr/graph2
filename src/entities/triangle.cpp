#include "entities/triangle.hpp"
#include "drawable.hpp"
#include "components/drawable.hpp"
#include <entt/entity/fwd.hpp>
static float vertices[] =  {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

entt::entity create_triangle(entt::registry & r) {
  static VAO vao;
  static VBO vbo(BufferType::array_buffer);
  DrawableComponent component = {
    Shaders::get_shader("main"),
    vao.get_id(),
    3,
    Color("#ffffff")
  };

  vao.bind();
  vbo.bind_buffer();
  vbo.send_data(sizeof(vertices), vertices, GL_STATIC_DRAW);
  vao.set_vertex_attr_ptr(0,  3, GL_FLOAT, 3 * sizeof(float), NULL);
  vao.enable_vertex_attr_array(0);

  vbo.unbind();
  vao.unbind();
  entt::entity e =r.create();
  r.emplace<DrawableComponent>(e, component);
  return e;

}
