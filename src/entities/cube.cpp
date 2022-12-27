#include "entities/cube.hpp"
#include "components/drawable.hpp"
#include "VBO.hpp"

static float l_cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
    -0.5f,  0.5f, -0.5f,  
    -0.5f, -0.5f, -0.5f,  
    -0.5f, -0.5f,  0.5f,  
     0.5f, -0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
    -0.5f,  0.5f,  0.5f,  
    -0.5f, -0.5f,  0.5f,  
    -0.5f,  0.5f,  0.5f,  
    -0.5f,  0.5f, -0.5f,  
    -0.5f, -0.5f, -0.5f,  
    -0.5f, -0.5f, -0.5f,  
    -0.5f, -0.5f,  0.5f,  
    -0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
    -0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f, -0.5f,  
     0.5f, -0.5f,  0.5f,  
     0.5f, -0.5f,  0.5f,  
    -0.5f, -0.5f,  0.5f,  
    -0.5f, -0.5f, -0.5f,  
    -0.5f,  0.5f, -0.5f,  
     0.5f,  0.5f, -0.5f,  
     0.5f,  0.5f,  0.5f,  
     0.5f,  0.5f,  0.5f,  
    -0.5f,  0.5f,  0.5f,  
    -0.5f,  0.5f, -0.5f,  
}; 

entt::entity create_cube(entt::registry & r)
{
  static VAO vao;
  static VBO vbo(BufferType::array_buffer);

  DrawableComponent component = {
    Shaders::get_shader("main"),
    vao.get_id(),
    108,
    Color("#000000")
  };

  vao.bind();
  vbo.bind_buffer();
  vbo.send_data(sizeof(l_cubeVertices), l_cubeVertices, GL_STATIC_DRAW);
  vao.set_vertex_attr_ptr(0,  3, GL_FLOAT, 3 * sizeof(float), NULL);
  vao.enable_vertex_attr_array(0);

  vbo.unbind();
  vao.unbind();
  entt::entity e =r.create();
  r.emplace<DrawableComponent>(e, component);
  return e;
}

