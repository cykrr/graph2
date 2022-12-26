#include <list>

#include "imgui.h"

#include "VAO.hpp"
#include "VBO.hpp"
#include "util/color.hpp"
#include "views/cube.hpp"
#include "views/triangle.hpp"
#include "window.hpp"
#include "shaders.hpp"

#include "instance_drawer.hpp"
#include "instance.hpp"

#include "gui.hpp"
#include "wrappers/gl.hpp"
#include "wrappers/glfw.hpp"
  
int main() {
  printf("TT_TT my take on OpenGL Engines\n");
  glfw::Window *window = initGLFW();
  GUI gui(window);

  while (!window->should_close()) {

    gl::clear_color(Color("#202020")); // clear
    glClear(gl::Bits::color_buffer | gl::Bits::depth_buffer);

    gui.render();

    window->swap_buffers();
    glfwPollEvents();
  }
}
