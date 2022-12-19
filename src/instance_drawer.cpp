#include "instance.hpp"
#include "instance_drawer.hpp"
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
  return this->position;
}
// template <class T> void InstanceDrawer<T>::show() {
//   std::vector<const char *> items;
//   std::vector<Instance<T> *> items_ptr;
//   for (Instance<T> *instance : instances) {
//     items.push_back(type.get_name());
//     items_ptr.push_back(instance);
//   }
//   static int listbox_item_current = -1;
//   if (ImGui::ListBox("listbox", &listbox_item_current, &items[0], items.size(),
//                      4)) {
//   }
//
//   ImGui::PushItemWidth(-1);
//   ImGui::PopItemWidth();
// }

#include "gui/views/cube.hpp"
template class InstanceDrawer<Cube>;
