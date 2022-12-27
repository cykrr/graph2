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

#include "entt/entity/registry.hpp"
  
int main() {
  printf("TT_TT my take on OpenGL Engines\n");
  GLFWwindow *window = initGLFW();
  GUI gui(window);

  while (!glfwWindowShouldClose(window)){
    Color clear_color("#202020");
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a); // clear
    glClear(gl::Bits::color_buffer | gl::Bits::depth_buffer);

    gui.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
