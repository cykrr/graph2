#ifndef VIEWPORT_WINDOW_H
#define VIEWPORT_WINDOW_H
#include <cstdio>
#include "imgui.h"
#include "glad/glad.h"
#include "scene.hpp"
class ViewportWindow {
public:
  ViewportWindow();
  void draw();
  void update_fbo();
  void bind_fbo();
  void unbind_fbo();
  ImVec2       size;
  ImVec2       pos;
  Scene m_scene;
protected:
  unsigned int m_color_texture;
  unsigned int m_fbo;
  unsigned int m_rbo;

};
#endif

