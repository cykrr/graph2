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

static float mdx = 0, mdy = 0;

/***
 *
  ImGui::Text("Mouse: %f %f", posx, posy);
  ImGui::Text("Window: %f %f",
              m_viewport_window.pos.x, m_viewport_window.pos.y);

  ImGui::Text("MouseWindow: %f %f",
              posx - m_viewport_window.pos.x, posy - m_viewport_window.pos.y);
*/
  
int main() {
  printf("TT_TT my take on OpenGL Engines\n");
  GLFWwindow *w = initGLFW();
  GUI gui(w);

  glfwSetWindowUserPointer(w, &gui);
  glfwSetScrollCallback(w, [](GLFWwindow* w, double dx, double dy) {
      printf("dx: %f dy: %f\n", dx, dy);
      mdx = dx; mdy = dy;
     
  });
  glfwSetFramebufferSizeCallback(w, [](GLFWwindow *w, int width, int height) {
    GUI *s = (GUI *)glfwGetWindowUserPointer(w) ;
    s->m_scene.cam.update(s->m_viewport_window.size.x, s->m_viewport_window.size.y);
    Program::setMat4_id(Shaders::get_shader("main"), "vp", s->m_scene.cam.matrix);
    // TODO: vector with all the shaders that need updating to batch the process
    // of inserting vp matrix
  });

  while (!glfwWindowShouldClose(w)){
    Color clear_color("#202020");
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a); // clear
    glClear(gl::Bits::color_buffer | gl::Bits::depth_buffer);

    gui_render(gui);

    glfwSwapBuffers(w);
    glfwPollEvents();
  }
}
