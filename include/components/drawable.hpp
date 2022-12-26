#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H
#include "program.hpp"
#include "VAO.hpp"
struct DrawableComponent
{
  Program m_shader;
  VAO m_vao;

  DrawableComponent() = default;
  DrawableComponent(const char * shader_name, const unsigned int vao) : m_shader(shader_name), m_vao(vao) {};
  DrawableComponent(const char * shader_name) : m_shader(shader_name){};
  DrawableComponent(DrawableComponent &&) = default;
  DrawableComponent(const DrawableComponent &) = default;
  ~DrawableComponent() = default;
};
#endif
