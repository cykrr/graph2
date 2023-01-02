#ifndef GUI_H
#define GUI_H
#include "gui/views/viewport_window.hpp"
#include "wrappers/glfw.hpp"
#include "imgui/imgui.h"
#include "scene.hpp"
#include "gui/dock.hpp"


struct GUI {
        ImGuiIO * m_io;
   ViewportWindow m_viewport_window;
            Scene m_scene;
             Dock m_dockspace;
     GLFWwindow * m_window;
  GUI(GLFWwindow *w);
};
void gui_render(GUI & gui);
#endif
