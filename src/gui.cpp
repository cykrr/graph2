#include <cstdio>
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>

#include "glad/glad.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


#include "views/cube.hpp"
#include "views/triangle.hpp"
#include "shaders.hpp"
#include "program.hpp"

#include "components/gui.hpp"
#include "components/model.hpp"
#include "components/view_proj.hpp"
#include "components/mesh.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"

#include "entities/cube.hpp"
#include "entities/triangle.hpp"

#include "gui.hpp"
#include "gui/views/entity.hpp"

#include "gui/easings.h"
#include "gui/matrix.hpp"

Easings::easings animation_picker() {
  static int current_animation = 0;
  ImGui::Combo("Easings", &current_animation, Easings::name_array, IM_ARRAYSIZE(Easings::name_array));
  return (Easings::easings)current_animation;

}


GUI::GUI(GLFWwindow *window) : m_window(window) {

  ImGui::CreateContext();
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  this->m_io = &ImGui::GetIO();
  this->m_io->Fonts->AddFontFromFileTTF("res/fonts/cantarell.ttf", 20);
  // this->io->ConfigDockingWithShift = true;

  // setup platform/renderer bindings
  if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
    printf("Error init glfw imgui\n");
  }
  if (!ImGui_ImplOpenGL3_Init("#version 330 core")) {
    printf("Error init opengl imgui\n");
  }
}

void GUI::render() {
  // Render Scene

  m_viewport_window.bind_fbo();
  m_scene.render();
  m_viewport_window.unbind_fbo();

  // Begin frame

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Update views
  m_dockspace.update();
  m_viewport_window.update_fbo();

  // Draw child views

  static double posx, posy;
  glfwGetCursorPos(m_window, &posx, &posy);

  ImGui::ShowMetricsWindow(NULL);

  m_viewport_window.draw();

  ImGui::Begin("LeftDock"); 
  create_entity_draw(m_scene.m_registry);

  static entt::entity selection;
  static bool selected = false;
  entity_picker(m_scene.m_registry, selection, selected);

  matrix_draw(m_scene.cam.matrix);

  ImGui::End(); 
  if (selected) {
    selected_entity_view_draw(m_scene.m_registry, selection);
  }



  // Update and Render ImGUI

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  GLFWwindow* backup_current_context = glfwGetCurrentContext();
  if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
  glfwMakeContextCurrent(backup_current_context);
}

/***
 *
  ImGui::Text("Mouse: %f %f", posx, posy);
  ImGui::Text("Window: %f %f",
              m_viewport_window.pos.x, m_viewport_window.pos.y);

  ImGui::Text("MouseWindow: %f %f",
              posx - m_viewport_window.pos.x, posy - m_viewport_window.pos.y);
*/
