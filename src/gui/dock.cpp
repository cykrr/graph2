#include "gui/dock.hpp"
#include "imgui/imgui_internal.h"

void Dock::update() {

  ImGuiViewport* m_viewport_ptr = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(m_viewport_ptr->Pos);
  ImGui::SetNextWindowSize(m_viewport_ptr->Size);

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
  ImGui::SetNextWindowSize(m_viewport_ptr->Size);
  ImGui::SetNextWindowPos(m_viewport_ptr->Pos);
  ImGui::Begin("DockSpace", NULL, window_flags);

  ImGuiID dockspace_id = ImGui::GetID("DockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0, 0),
                   ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_AutoHideTabBar
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

		/* split the dockspace into 2 nodes -- DockBuilderSplitNode takes in the
     * following args in the following order window ID to split, direction,
     * fraction (between 0 and 1), the final two setting let's us choose which
     * id we want (which ever one we DON'T set as NULL, will be returned by the
     * function)
     * 
     * out_id_at_dir is the id of the node in the direction we specified
     * earlier, out_id_at_opposite_dir is in the opposite direction*/

		m_dock_down = ImGui::DockBuilderSplitNode(
        dockspace_id, ImGuiDir_Down, 0.25f, nullptr, &dockspace_id);
		m_dock_left = ImGui::DockBuilderSplitNode(
        dockspace_id, ImGuiDir_Left, 0.25f, nullptr, &dockspace_id);
		m_dock_up = ImGui::DockBuilderSplitNode(
        dockspace_id, ImGuiDir_Up, 1.f, nullptr, &dockspace_id);


		// we now dock our windows into the docking node we made above
		// ImGui::DockBuilderDockWindow("Down", m_dock_down);
		ImGui::DockBuilderDockWindow("LeftDock", m_dock_left);
		ImGui::DockBuilderDockWindow("Viewport", m_dock_up);
    ImGui::DockBuilderDockWindow("SelectedEntity", m_dock_down);
		ImGui::DockBuilderFinish(dockspace_id);
	}
  ImGui::End();
}

