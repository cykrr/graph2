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

  entity_view_draw(m_scene.m_registry);

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


void GUI::entity_view_draw(entt::registry &r)
{
  ImGui::Begin("Entities");
    ImGui::Text("Create entity:");
    std::tuple<const char *, entity_fn_t> entity_desc =  entity_type_picker_draw(r);
    static ImVec4 col(0,0,0,1.);
    static Color color("#00ff00");
    // static bool send_color = false;
    if (ImGui::ColorEdit3("Color", &col.x, ImGuiColorEditFlags_DisplayHex |
                      ImGuiColorEditFlags_InputRGB |
                      ImGuiColorEditFlags_NoAlpha)) {
    color = Color(col);
      // send_color = true;

    }

    char buf[50] = "";
    if (
      ImGui::InputText("name", buf, 50,ImGuiInputTextFlags_EnterReturnsTrue) &&
      strlen(buf) != 0 
    ) {
      entt::entity e = std::get<1>(entity_desc)(r);
      const char * n = std::get<0>(entity_desc);
      NameComponent nc(buf,  n);

      m_scene.m_registry.emplace<NameComponent>(e, nc);
      // if(send_color) {
        printf("sendin\n");
        DrawableComponent & c = r.get<DrawableComponent>(e);
        c.m_color = color;

      // }
    }

    static entt::entity selection;
    static bool selected = false;
    if (ImGui::BeginListBox("Entities")) {
      auto view = r.view<NameComponent, DrawableComponent>();
      (view.each([](const auto & ent, auto &name, auto &drawable) {
                   if (ImGui::Selectable(name.m_name)) {
                     selected = true;
                     selection = ent;
                   }
                 }));
      ImGui::EndListBox();
    }
  ImGui::End();
  if (selected) {
    ImGui::Begin("SelectedEntity");
      DrawableComponent & dc = m_scene.m_registry.get<DrawableComponent>(selection);
      NameComponent & nc = m_scene.m_registry.get<NameComponent>(selection);
      ImGui::Text("Name: %s", nc.m_name); 
      ImGui::Text("Type: %s", nc.m_type); 

      ImGui::Text("Color:"); ImGui::SameLine();
      ImGui::ColorButton("Color", (ImVec4){dc.m_color.r, dc.m_color.g, dc.m_color.b, dc.m_color.a});
    ImGui::End();
  }

}


std::tuple<const char *, entity_fn_t> GUI::entity_type_picker_draw(entt::registry & r)
{
  static const char * items_str[] = {"Triangle", "Cube"};

  const entity_fn_t items_func[10] = {create_triangle, create_cube};
  static entity_fn_t current_func = NULL;

  static int item_current = 0;

  ImGui::Combo("Type", &item_current, items_str, IM_ARRAYSIZE(items_str));
  current_func = items_func[item_current];
  return std::tuple<const char *, entity_fn_t>(items_str[item_current], current_func);
}

    // printf("%f %f %f %f\n",
    //        color.r ,
    //        color.g ,
    //        color.b ,
    //        color.a);
//
    // printf("Creado %s\n", name.m_name);
    // printf("%f %f %f %f\n",
    //        drawable.m_color.r ,
    //        drawable.m_color.g ,
    //        drawable.m_color.b ,
    //        drawable.m_color.a);
