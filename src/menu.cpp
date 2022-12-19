#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void gui_render(double dt) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  bool my_tool_active = true;
  ImGui::Begin("My First Tool", &my_tool_active);
  if (ImGui::Button("Add Triangle:")) {
  }
  if (ImGui::Button("Add Cube:")) {
    // printf("press\n");
    // cube_drawer->insert(new Instance<Cube>());
  }

  ImGui::Text("Elements:");
  ImGui::BeginChild("Scrolling");
  // cube_drawer->show();
  ImGui::EndChild();

  ImGui::End();
  ImGui::EndFrame();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
