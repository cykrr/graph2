#ifndef GLFW_WRAPPER_H
#define GLFW_WRAPPER_H
#include <GLFW/glfw3.h>
namespace glfw {

typedef void (* GLFWframebuffersizefun)(GLFWwindow* window, int width, int height);

class Window {
public:
  Window(int width, int height, const char * window_name);
  bool should_close();
  void swap_buffers();
  void make_current_context();
  void set_framebuffer_size_callback(GLFWframebuffersizefun);
  GLFWwindow *window;
protected:
};

void init();

}
#endif
