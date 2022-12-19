#include "VAO.hpp"
#include "VBO.hpp"
#include "gui/color.hpp"
#include "gui/views/cube.hpp"
#include "gui/views/triangle.hpp"
#include "gui/window.hpp"
#include "shaders.hpp"

#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <list>

void gui_render(double dt);

template <class T> class Instance {
public:
  void set_position(glm::vec3 &position);
  const glm::vec3 &get_position();

private:
  glm::vec3 position;
  glm::vec3 scale;
  // DrawableType type;
};

template <class T> class InstanceDrawer {
public:
  void draw();
  void insert(Instance<T> *instance);
  void show();

private:
  T type;
  std::list<Instance<T> *> instances;
};

template <class T> void InstanceDrawer<T>::insert(Instance<T> *instance) {
  instances.push_back(instance);
}

template <class T> void InstanceDrawer<T>::draw() {
  for (Instance<T> *t : instances) {
    type.translate(t->get_position());
    type.draw();
  }
}

template <class T> const glm::vec3 &Instance<T>::get_position() {
  this->position += glm::vec3(dt, 0, 0);
  return this->position;
}

template <class T> void InstanceDrawer<T>::show() {
  std::vector<const char *> items;
  std::vector<Instance<T> *> items_ptr;
  for (Instance<T> *instance : instances) {
    items.push_back(type.get_name());
    items_ptr.push_back(instance);
  }
  static int listbox_item_current = -1;
  if (ImGui::ListBox("listbox", &listbox_item_current, &items[0], items.size(),
                     4)) {
  }

  ImGui::PushItemWidth(-1);
  ImGui::PopItemWidth();
}

glm::vec3 rotate;
glm::vec3 scale(1.f);

std::list<Drawable *> drawables;

int initImGui(GLFWwindow *window) {
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  // setup platform/renderer bindings
  if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
    return 0;
  }
  if (!ImGui_ImplOpenGL3_Init("#version 330 core")) {
    return 0;
  }
  return 0;
}

InstanceDrawer<Cube> *cube_drawer = NULL;
int main() {
  printf("TT_TT\n");
  GLFWwindow *window = initGLFW();
  initImGui(window);
  cube_drawer = new InstanceDrawer<Cube>();

  double dt = 0;
  double then = 0;

  while (!glfwWindowShouldClose(window)) {

    double now = glfwGetTime();
    dt = now - then;
    then = now;

    glClearColorHex("#202020"); // clear
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    cube_drawer->draw();
    gui_render(dt);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

// enum DrawableType {
//   Triangle,
//   Cube,
//   Circle
// };

void gui_render(double dt) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  bool my_tool_active = true;
  ImGui::Begin("My First Tool", &my_tool_active);
  if (ImGui::Button("Add Triangle:")) {
  }
  if (ImGui::Button("Add Cube:")) {
    printf("press\n");
    cube_drawer->insert(new Instance<Cube>());
  }

  ImGui::Text("Elements:");
  ImGui::BeginChild("Scrolling");
  cube_drawer->show();
  ImGui::EndChild();

  ImGui::End();
  ImGui::EndFrame();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
