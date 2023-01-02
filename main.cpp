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
  GLFWwindow *w = initGLFW();
  GUI gui(w);
  Scene &s = gui.m_scene;

  glfwSetWindowUserPointer(w, &s);
  glfwSetFramebufferSizeCallback(w, [](GLFWwindow *w, int width, int height) {
    Scene *s = (Scene *)glfwGetWindowUserPointer(w) ;
    s->cam.update(width, height);
    Program::setMat4_id(Shaders::get_shader("main"), "vp", s->cam.matrix);
    // TODO: vector with all the shaders that need updating to batch the process
    // of inserting vp matrix
  });

  while (!glfwWindowShouldClose(w)){
    Color clear_color("#202020");
    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a); // clear
    glClear(gl::Bits::color_buffer | gl::Bits::depth_buffer);

    gui.render();

    glfwSwapBuffers(w);
    glfwPollEvents();
  }
}
