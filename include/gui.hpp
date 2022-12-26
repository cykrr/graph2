#ifndef GUI_H
#define GUI_H
#include "gui/viewport_window.hpp"
#include <GLFW/glfw3.h>
#include "wrappers/glfw.hpp"
#include "imgui/imgui.h"
#include "scene.hpp"
class GUI {
public:
  GUI(glfw::Window *w);
  void render();
private :
  ImGuiIO * io;
  glfw::Window *window;
  ViewportWindow m_viewport_window;
  Scene m_scene;
};
#endif
