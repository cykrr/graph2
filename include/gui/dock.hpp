#ifndef DOCK_H
#define DOCK_H
#include "imgui.h"

class Dock {
public:
  void update();
  unsigned int 
    m_dockspace_id,
    m_dock_up,  
    m_dock_right,  
    m_dock_down,  
    m_dock_left;
private:

};
#endif
