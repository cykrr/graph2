#ifndef INPUT_H
#define INPUT_H
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "gui/renderer.hpp"
void processInput(GLFWwindow *window);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
#endif
