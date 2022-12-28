#ifndef GUI_H
#define GUI_H
#include "gui/viewport_window.hpp"
#include "wrappers/glfw.hpp"
#include "imgui/imgui.h"
#include "scene.hpp"
#include "gui/dock.hpp"

typedef  entt::entity(*entity_fn_t)(entt::registry &);

class GUI {
public:
  GUI(GLFWwindow *w);
  void render();
private:
        ImGuiIO * m_io;
   ViewportWindow m_viewport_window;
            Scene m_scene;
             Dock m_dockspace;
     GLFWwindow * m_window;


};
#endif
