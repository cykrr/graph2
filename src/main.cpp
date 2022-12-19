#include <list>

#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "VAO.hpp"
#include "VBO.hpp"
#include "gui/color.hpp"
#include "gui/views/cube.hpp"
#include "gui/views/triangle.hpp"
#include "gui/window.hpp"
#include "shaders.hpp"

#include "instance_drawer.hpp"
#include "instance.hpp"


void gui_render(double dt);



glm::vec3 rotate;
glm::vec3 scale(1.f);

std::list<Drawable *> drawables;

int initImGui(GLFWwindow *window) {
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // setup platform/renderer bindings
  if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
    return 0;
  }
  if (!ImGui_ImplOpenGL3_Init("#version 330 core")) {
    return 0;
  }
  return 0;
}

InstanceDrawer<Cube> *cube_drawer = NULL;
int main() {
  printf("TT_TT\n");
  GLFWwindow *window = initGLFW();
  initImGui(window);
  cube_drawer = new InstanceDrawer<Cube>();

  double dt = 0;
  double then = 0;

  while (!glfwWindowShouldClose(window)) {

    double now = glfwGetTime();
    dt = now - then;
    then = now;

    glClearColorHex("#202020"); // clear
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    cube_drawer->draw();
    gui_render(dt);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}
