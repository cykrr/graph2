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


  unsigned int fbo;

  glGenFramebuffers(1, &fbo);
  this->fbo = fbo;
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);




  unsigned int texture;

  glGenTextures(1, &texture);
  this->texture = texture;
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 600, 600, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         texture, 0);

  unsigned int rbo;

  glGenRenderbuffers(1, &rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 600, 600);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, rbo);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  	printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
  glBindFramebuffer(GL_FRAMEBUFFER, 0);



}

void GUI::render() {

  Cube cube;
  Program* shader = Shaders::get_shader("main");
  shader->use();
  shader->setMat4("m", glm::rotate(glm::mat4(1.f), ((float)ImGui::GetTime()), glm::vec3(0.f, 1.f, 1.f)));
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glViewport(0, 0, viewport_size.x, viewport_size.y);
        // make sure we clear the framebuffer's content
        glClearColor(0, 0,0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube.draw();
        
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
  ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoTabBar);

  static auto first_time = true;
  if (first_time)
	{
    first_time = false;

		ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
		ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

		// split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the following args in the following order
		//   window ID to split, direction, fraction (between 0 and 1), the final two setting let's us choose which id we want (which ever one we DON'T set as NULL, will be returned by the function)
		//                                                              out_id_at_dir is the id of the node in the direction we specified earlier, out_id_at_opposite_dir is in the opposite direction
		auto dock_id_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
		auto dock_id_down = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);
		auto dock_id_up = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Up, 1.f, nullptr, &dockspace_id);


		// we now dock our windows into the docking node we made above
		ImGui::DockBuilderDockWindow("Down", dock_id_down);
		ImGui::DockBuilderDockWindow("Viewport", dock_id_up);
		ImGui::DockBuilderFinish(dockspace_id);
	}
  ImGui::End();

  ImGui::Begin("Down");
    ImGui::Text("OLA");
  ImGui::End();

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("Viewport", NULL);
    this->viewport_size = ImGui::GetWindowSize();
    ImGui::Image((void*)texture, ImVec2(600, 600), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
    ImGui::PopStyleVar();



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
