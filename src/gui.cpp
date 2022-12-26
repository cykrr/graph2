#include "glad/glad.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "gui.hpp"
#include <cstdio>
#include "views/cube.hpp"
#include "shaders.hpp"
#include "program.hpp"

#include "components/name.hpp"
#include "components/view_proj.hpp"
#include "components/drawable.hpp"

bool handle_viewport_resize();


GUI::GUI(glfw::Window *window) {
  this->window = window;

  ImGui::CreateContext();
  ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  this->io = &ImGui::GetIO();
  this->io->ConfigDockingWithShift = true;

  // setup platform/renderer bindings
  if (!ImGui_ImplGlfw_InitForOpenGL(window->window, true)) {
    printf("Error init glfw imgui\n");
  }
  if (!ImGui_ImplOpenGL3_Init("#version 330 core")) {
    printf("Error init opengl imgui\n");
  }
}

void GUI::render() {

  Cube cube;
  Program* shader = Shaders::get_shader("main");
  m_viewport_window.bind_fbo();
  auto v = m_scene.m_registry.view<DrawableComponent>();
  glClearColor(1.0, 0,0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  v.each([](struct DrawableComponent &drawable){
        drawable.m_shader.use();
        drawable.m_shader.setMat4("m", glm::mat4(1.f));
        drawable.m_vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 108);

  });
    
  // shader->setMat4("m", glm::rotate(glm::mat4(1.f),
  //                                  ((float)ImGui::GetTime()),
  //                                  glm::vec3(0.f, 1.f, 1.f)
  //                                  )
  //                 );
        // make sure we clear the framebuffer's content
        
        
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::SetNextWindowSize(viewport->Size);

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
  ImGui::SetNextWindowSize(viewport->Size);
  ImGui::SetNextWindowPos(viewport->Pos);
  ImGui::Begin("DockSpace", NULL, window_flags);

  ImGuiID dockspace_id = ImGui::GetID("DockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0, 0),
                   ImGuiDockNodeFlags_PassthruCentralNode |
                   ImGuiDockNodeFlags_NoTabBar);

  static auto first_time = true;
  if (first_time)
	{
    first_time = false;

    m_viewport_window.update_fbo();
		ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
		ImGui::DockBuilderAddNode(dockspace_id,
                            ImGuiDockNodeFlags_PassthruCentralNode |
                            ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

		/* split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the
     * following args in the following order window ID to split, direction,
     * fraction (between 0 and 1), the final two setting let's us choose which
     * id we want (which ever one we DON'T set as NULL, will be returned by the
     * function)
     * 
     * out_id_at_dir is the id of the node in the direction we specified
     * earlier, out_id_at_opposite_dir is in the opposite direction*/

		auto dock_id_down = ImGui::DockBuilderSplitNode(
        dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);
		auto dock_id_left = ImGui::DockBuilderSplitNode(
        dockspace_id, ImGuiDir_Left, 0.25f, nullptr, &dockspace_id);
		auto dock_id_up = ImGui::DockBuilderSplitNode(
        dockspace_id, ImGuiDir_Up, 1.f, nullptr, &dockspace_id);


		// we now dock our windows into the docking node we made above
		ImGui::DockBuilderDockWindow("Down", dock_id_down);
		ImGui::DockBuilderDockWindow("Left", dock_id_left);
		ImGui::DockBuilderDockWindow("Viewport", dock_id_up);
		ImGui::DockBuilderFinish(dockspace_id);
	}
  ImGui::End();

  m_viewport_window.draw();

  ImGui::Begin("Left");
  char buf[50];
  if (ImGui::InputText("Create Entity", buf, 50,ImGuiInputTextFlags_EnterReturnsTrue)) {
    entt::entity e = m_scene.create_entity();
    m_scene.m_registry.emplace<NameComponent>(e, std::string(buf));
    m_scene.m_registry.emplace<DrawableComponent>(e, "main", cube.get_vao());
    printf("Creado %s %d\n", buf, e);
  }
  if (ImGui::BeginListBox("Entities")) {
    auto view = m_scene.m_registry.view<NameComponent, DrawableComponent>();
    (view.each([](const auto & ent, auto &name, auto &drawable) {

                 if (ImGui::Selectable(name.name.c_str())) {
                   ImGui::OpenPopup(name.name.c_str());
                 }
                 if(ImGui::BeginPopupModal(name.name.c_str())) {
                   ImGui::Text("Shader_name: %s", drawable.m_shader.get_shader_name().c_str());
                   ImGui::EndPopup();
                 }
               }));
    ImGui::EndListBox();
  }
  ImGui::End();




  // Update and Render additional Platform Windows
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  GLFWwindow* backup_current_context = glfwGetCurrentContext();
  if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
  }
  glfwMakeContextCurrent(backup_current_context);
}

bool handle_viewport_resize() {

}
