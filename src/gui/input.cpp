#include "gui/input.hpp"
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_TRUE)
        glfwSetWindowShouldClose(window, true);
}
