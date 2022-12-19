#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "gui.hpp"
#include <cstdio>

void GUI::render() {
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


GUI::GUI(GLFWwindow *window) {
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // setup platform/renderer bindings
  if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
    printf("Error init glfw imgui\n");
  }
  if (!ImGui_ImplOpenGL3_Init("#version 330 core")) {
    printf("Error init opengl imgui\n");
  }
}
