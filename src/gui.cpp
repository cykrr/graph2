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

#include "entities/cube.hpp"
#include "entities/triangle.hpp"

#include "gui.hpp"

GUI::GUI(GLFWwindow *window) {

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

  auto rotation_view = m_scene.m_registry.view<RotationComponent, ModelComponent>();
  auto draw_view = m_scene.m_registry.view<DrawableComponent, ModelComponent>();

  rotation_view.each(
      [](RotationComponent & rc, ModelComponent & mc) {
          if(rc.axis.x + rc.axis.y + rc.axis.z)
            mc.matrix = glm::rotate(glm::mat4(1.f), rc.radians, rc.axis);
      });

  draw_view.each(
      [](const entt::entity & ent, struct DrawableComponent &drawable, struct ModelComponent &model){
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

  m_viewport_window.draw();
  entity_view_draw(m_scene.m_registry);

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
