#include "gui/dock.hpp"
#include "imgui/imgui_internal.h"

void Dock::update() {

  ImGuiViewport* m_viewport_ptr = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(m_viewport_ptr->Pos);
  ImGui::SetNextWindowSize(m_viewport_ptr->Size);

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize;
  ImGui::SetNextWindowSize(m_viewport_ptr->Size);
  ImGui::SetNextWindowPos(m_viewport_ptr->Pos);
  ImGui::Begin("DockSpace", NULL, window_flags);

  ImGuiID dockspace_id = ImGui::GetID("DockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0, 0),
                   ImGuiDockNodeFlags_PassthruCentralNode
                   // ImGuiDockNodeFlags_NoTabBar
                   );

  static auto first_time = true;
  if (first_time)
	{
    first_time = false;
		ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
		ImGui::DockBuilderAddNode(dockspace_id,
                            ImGuiDockNodeFlags_PassthruCentralNode |
                            ImGuiDockNodeFlags_DockSpace |ImGuiDockNodeFlags_AutoHideTabBar);
		ImGui::DockBuilderSetNodeSize(dockspace_id, m_viewport_ptr->Size);

		ImGui::DockBuilderDockWindow("Viewport", dockspace_id);

		unsigned int m_dock_right = ImGui::DockBuilderSplitNode(
        dockspace_id, ImGuiDir_Right, 0.2f, nullptr, &dockspace_id);
    ImGui::DockBuilderDockWindow("Dear ImGui Metrics/Debugger", m_dock_right);

		m_dock_left = ImGui::DockBuilderSplitNode(
        dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dockspace_id);
		ImGui::DockBuilderDockWindow("LeftDock", m_dock_left);

		unsigned int m_dock_left_down = ImGui::DockBuilderSplitNode(
        m_dock_left, ImGuiDir_Down, 0.5f, nullptr, &m_dock_left);
    ImGui::DockBuilderDockWindow("SelectedEntity", m_dock_left_down);


		// we now dock our windows into the docking node we made above
		// ImGui::DockBuilderDockWindow("Down", m_dock_down);
		ImGui::DockBuilderFinish(dockspace_id);
	}
  ImGui::End();
}

