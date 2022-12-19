#ifndef GLFW_WRAPPER_H
#define GLFW_WRAPPER_H
#include <GLFW/glfw3.h>
namespace glfw {

class Window {
public:
  Window(int width, int height, const char * window_name);
  bool should_close();
  void swap_buffers();
protected:
  GLFWwindow *window;
};

extern void init();

}
#endif
