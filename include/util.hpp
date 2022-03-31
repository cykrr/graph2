#ifndef UTIL_H
#define UTIL_H

#define isPressed(x, y) (glfwGetKey(x, y) == GLFW_PRESS)

#include <GLFW/glfw3.h>
extern float dt;
extern float currentTime;
extern float prevTime;
void updateTime();
#endif