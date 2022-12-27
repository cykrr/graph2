#ifndef GUI_H
#define GUI_H
#include "gui/viewport_window.hpp"
#include <GLFW/glfw3.h>
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
   glfw::Window * m_window;
   ViewportWindow m_viewport_window;
            Scene m_scene;
             Dock m_dockspace;

               void entity_view_draw(entt::registry &r);
          entity_fn_t entity_type_picker_draw(entt::registry &);

};
#endif
