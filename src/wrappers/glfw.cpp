#include "wrappers/glfw.hpp"
#include <GLFW/glfw3.h>

using namespace glfw;

bool Window::should_close()
{
  return glfwWindowShouldClose(window);
}

Window::Window(int width, int height, const char * window_name)
{
  this->window = glfwCreateWindow(width, height, window_name, NULL, NULL);
}

void Window::swap_buffers()
{
  glfwSwapBuffers(this->window);
}

void glfw::init() {
  glfwInit();
}

void Window::make_current_context()
{
  glfwMakeContextCurrent(window);
}

void Window::set_framebuffer_size_callback(GLFWframebuffersizefun f) {
  glfwSetFramebufferSizeCallback(this->window, f);
}
