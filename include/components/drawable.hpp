#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H
#include "program.hpp"
#include "VAO.hpp"
#include "shaders.hpp"
struct DrawableComponent
{
  Program m_shader;
  VAO m_vao;
  unsigned int m_vert_count;

  DrawableComponent() = default;
  DrawableComponent(const char * shader_name, const unsigned int vao, unsigned int vert_count):
      m_shader(Shaders::get_shader("main"))
  {
      m_vao = VAO(vao);
      m_vert_count = vert_count;

  }

  DrawableComponent(DrawableComponent &&) = default;
  DrawableComponent(const DrawableComponent &) = default;
  ~DrawableComponent() = default;
};

extern void draw_component(DrawableComponent &);

#endif
