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

#include "components/name.hpp"
#include "components/model.hpp"
#include "components/view_proj.hpp"
#include "components/drawable.hpp"
#include "components/rotation.hpp"
#include "components/scale.hpp"

#include "entities/cube.hpp"
#include "entities/triangle.hpp"

#include "gui.hpp"
#include "gui/views/entity.hpp"


GUI::GUI(GLFWwindow *window) : m_window(window) {

  ImGui::CreateContext();
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  this->m_io = &ImGui::GetIO();
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
  Color clear("#656565");
  glClearColor(clear.x, clear.y, clear.z, clear.w);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto rotation_view = 
    m_scene.m_registry.view<RotationComponent, ModelComponent>();
  auto scale_view = 
    m_scene.m_registry.view<ScaleComponent, ModelComponent>();
  auto draw_view = 
    m_scene.m_registry.view<DrawableComponent, ModelComponent>();

  // SRT

  scale_view.each(
      [](ScaleComponent & rc, ModelComponent & mc) {
        scale_model(mc, rc);
      });

  rotation_view.each(
      [](RotationComponent & rc, ModelComponent & mc) {
        rotate_model(mc, rc);
      });

  draw_view.each([](struct DrawableComponent &drawable,
                    struct ModelComponent &model) {
                   draw_component(drawable, model);
                 });

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

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


  m_viewport_window.draw();

  ImGui::Begin("LeftDock"); 
  create_entity_draw(m_scene.m_registry);

  static entt::entity selection;
  static bool selected = false;
  entity_picker(m_scene.m_registry, selection, selected);
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
