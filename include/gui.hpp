#ifndef GUI_H
#define GUI_H
#include "gui/viewport_window.hpp"
#include "wrappers/glfw.hpp"
#include "imgui/imgui.h"
#include "scene.hpp"
#include "gui/dock.hpp"


class GUI {
public:
  GUI(GLFWwindow *w);
  void render();
        ImGuiIO * m_io;
   ViewportWindow m_viewport_window;
            Scene m_scene;
             Dock m_dockspace;
     GLFWwindow * m_window;
private:


};
#endif
