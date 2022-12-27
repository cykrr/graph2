#include "glad/glad.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "gui.hpp"
#include <cstdio>
#include <entt/entity/fwd.hpp>
#include <entt/entity/registry.hpp>
#include "views/cube.hpp"
#include "views/triangle.hpp"
#include "shaders.hpp"
#include "program.hpp"

#include "components/name.hpp"
#include "components/view_proj.hpp"
#include "components/drawable.hpp"

#include "entities/cube.hpp"
#include "entities/triangle.hpp"

bool handle_viewport_resize();


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
  auto draw_view = m_scene.m_registry.view<NameComponent,DrawableComponent>();
  m_viewport_window.bind_fbo();
  glClearColor(.2, .2,.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  draw_view.each([](NameComponent &name, struct DrawableComponent &drawable){
    draw_component(drawable);
  });
        
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  m_dockspace.update();

  m_viewport_window.update_fbo();

  m_viewport_window.draw();

  static const char * items_str[] = {"Triangle", "Cube"};
  entt::entity(*const items_func[10])(entt::registry &) = {create_triangle, create_cube};
  static entt::entity(*current_func)(entt::registry &) = NULL;
  static int item_current = 0;

  ImGui::Begin("Entities");
  char buf[50] = "";
  ImGui::Text("Create entity:");
  ImGui::Combo("Type", &item_current, items_str, IM_ARRAYSIZE(items_str));
  current_func = items_func[item_current];
  if (ImGui::InputText("name", buf, 50,ImGuiInputTextFlags_EnterReturnsTrue)) {
    entt::entity e = current_func(m_scene.m_registry);
    m_scene.m_registry.emplace<NameComponent>(e, buf);
    printf("Creado %s %d\n", buf, e);
  }
  if (ImGui::BeginListBox("Entities")) {
    auto view = m_scene.m_registry.view<NameComponent, DrawableComponent>();
    (view.each([](const auto & ent, auto &name, auto &drawable) {
                 if (ImGui::Selectable(name.name.c_str())) {
    
                 }
               }));
    ImGui::EndListBox();
  }
  ImGui::End();
  // Update and Render additional Platform Windows
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

bool handle_viewport_resize() {
  return false;
}

