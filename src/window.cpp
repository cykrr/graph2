#include "glad/glad.h"
#include "window.hpp"
#include "GLFW/glfw3.h"
GLFWwindow *initGLFW()
{
  glfwInit();

  GLFWwindow *w = glfwCreateWindow(800, 600, "fons", NULL,NULL);

  glfwWindowHint(
      GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(
      GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(
      GLFW_OPENGL_PROFILE, 
      GLFW_OPENGL_CORE_PROFILE);

  // glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

  glfwMakeContextCurrent(w);
  // glfwSetCursorPosCallback(window, mouseCallback);


  glfwSetFramebufferSizeCallback(w, 
      [](GLFWwindow *win, int w, int h) {
        glViewport(0, 0, w, h);
      });


    if(!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress)
    ){
        // std::cout << "Error loading GLAD\n";
    }

    // glEnable(GL_DEPTH_TEST);
    return w;
}
