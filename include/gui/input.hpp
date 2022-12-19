#ifndef INPUT_H
#define INPUT_H
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "gui/renderer.hpp"
void mouseCallback(GLFWwindow *window, double xpos, double ypos);

void kbCallback(GLFWwindow *window,
        int key, int scanCode, int action, 
        int mode);

#endif
void processInput(GLFWwindow *window, Renderer *renderer);
void lookupJoystick();
