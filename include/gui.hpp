#ifndef GUI_H
#define GUI_H
#include "gui/viewport_window.hpp"
#include <GLFW/glfw3.h>
#include "wrappers/glfw.hpp"
#include "imgui/imgui.h"
#include "scene.hpp"
#include "gui/dock.hpp"

class GUI {
public:
  GUI(glfw::Window *w);
  void render();
private :
        ImGuiIO * m_io;
   glfw::Window * m_window;
   ViewportWindow m_viewport_window;
            Scene m_scene;
             Dock m_dockspace;
};
#endif
