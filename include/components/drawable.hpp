#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H
#include "model.hpp"
#include "program.hpp"
#include "VAO.hpp"
#include "shaders.hpp"
#include "util/color.hpp"
struct DrawableComponent
{

  unsigned int m_shader;
  unsigned int m_vao;
  unsigned int m_vert_count;

  Color m_color;
  bool m_show_wireframe;

  DrawableComponent() = default;
  DrawableComponent(DrawableComponent &&) = default;
  DrawableComponent(const DrawableComponent &) = default;
  ~DrawableComponent() = default;
};

extern void draw_component(DrawableComponent &, ModelComponent &);

#endif
