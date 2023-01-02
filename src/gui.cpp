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
#include "components/rotate.hpp"
#include "components/scale.hpp"

#include "entities/cube.hpp"
#include "entities/triangle.hpp"

#include "gui.hpp"
#include "gui/views/entity.hpp"

#include "gui/desc/easings.h"
#include "gui/elements/matrix.hpp"

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

void gui_render(GUI & gui) {
  // Render Scene

  gui.m_viewport_window.bind_fbo();
  gui.m_scene.render();
  gui.m_viewport_window.unbind_fbo();

  // Begin frame

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Update views
  gui.m_dockspace.update();
  gui.m_viewport_window.update_fbo();

  // Draw child views

  static double posx, posy;
  glfwGetCursorPos(gui.m_window, &posx, &posy);

  ImGui::ShowMetricsWindow(NULL);

  gui.m_viewport_window.draw();

  ImGui::Begin("LeftDock"); 
  static entt::entity selection;
  static bool selected = false;
  Views::Entity::create(gui.m_scene.m_registry, selection, selected);
  Views::Entity::pick(gui.m_scene.m_registry, selection, selected);

  ImGui::Text("Projection");
  Views::matrix(gui.m_scene.cam.matrix);

  ImGui::End(); 
  if (selected)
    Views::Entity::view(gui.m_scene.m_registry, selection);



  // Update and Render ImGUI

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  GLFWwindow* backup_current_context = glfwGetCurrentContext();
  if (gui.m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
  glfwMakeContextCurrent(backup_current_context);
}

