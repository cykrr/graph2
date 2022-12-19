#ifndef INSTANCEDRAWER_H
#define INSTANCEDRAWER_H
#include <list>
#include "instance.hpp"

template <class T> class InstanceDrawer {
public:
  void draw();
  void insert(Instance<T> *instance);
  void show();

private:
  T type;
  std::list<Instance<T> *> instances;
};

#endif
