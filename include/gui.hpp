#ifndef GUI_H
#define GUI_H
#include <GLFW/glfw3.h>
#include "wrappers/glfw.hpp"
class GUI {
public:
  GUI(glfw::Window *w);
  void render();
private :
};
#endif
