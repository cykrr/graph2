#include "window.hpp"
#include "scene.hpp"
#include "util/color.hpp"
#include "entities/plane.hpp"
#include "entities/triangle.hpp"
#include "shaders.hpp"
#include "program.hpp"

#include <GLFW/glfw3.h>

static float screen_width, screen_height,
             mouse_x, mouse_y;

int main()
{
  GLFWwindow *w = initGLFW();
  Scene s;
  Entity triangle = create_plane(s.m_registry);

  add_position(triangle, 200.f, 200.f);
  add_scale(triangle, 25.f, 25.f);

  glfwSetWindowUserPointer(w, &s);

  glfwSetFramebufferSizeCallback(
      w, [](GLFWwindow *window, int width, int height){
        Scene *s = (Scene*)glfwGetWindowUserPointer(window);
        glViewport(0, 0, width, height);
        update_orthographic_camera(s->cam, width, height);
        Program::setMat4_id(Shaders::get_shader("main"), "vp", s->cam.matrix);
        screen_width = width;
        screen_height = height;
      });


  glfwSetCursorPosCallback(
      w, [](GLFWwindow *window, double x, double y) {
        mouse_x = x, mouse_y = y; 
      });

  glfwSwapInterval(0);

  Color clearColor("#202020");

  while (!glfwWindowShouldClose(w))
    {
      update_time();


      // printf("dt: %f\n", dt);
      // printf("fps: %f\n", 1.f/dt);
      // printf("x50: %f y: %f\n", mouse_x, mouse_y);  
      
      glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
      glClear(GL_COLOR_BUFFER_BIT);

      set_position(triangle, mouse_x, mouse_y);

      s.render();

      glfwSwapBuffers(w);
      glfwPollEvents();
    }
  return 0;
}

