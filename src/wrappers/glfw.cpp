#include "wrappers/glfw.hpp"

using namespace glfw;

bool Window::should_close()
{
  return glfwWindowShouldClose(window);
}

Window::Window(int width, int height, const char * window_name);
{
  this->window = glfwCreateWindow(width, height, window_name, NULL, NULL);
}

void Window::swap_buffers()
{
  glfwSwapBuffers(this->window);
}

void init() {
  glfwInit();
}


