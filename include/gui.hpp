#ifndef GUI_H
#define GUI_H
#include <GLFW/glfw3.h>
#include "wrappers/glfw.hpp"
#include "imgui/imgui.h"
class GUI {
public:
  GUI(glfw::Window *w);
  void render();
private :
  ImGuiIO * io;
  unsigned int texture;
  unsigned int fbo;
  ImVec2 viewport_size;
  glfw::Window *window;
};
#endif
