#include <list>

#include "imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "VAO.hpp"
#include "VBO.hpp"
#include "gui/color.hpp"
#include "gui/views/cube.hpp"
#include "gui/views/triangle.hpp"
#include "gui/window.hpp"
#include "shaders.hpp"

#include "instance_drawer.hpp"
#include "instance.hpp"

#include "gui.hpp"

int main() {
  printf("TT_TT my take on OpenGL Engines\n");
  GLFWwindow *window = initGLFW();
  GUI gui(window);

  while (!glfwWindowShouldClose(window)) {

    glClearColorHex("#202020"); // clear
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    gui.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
