#include "gui/input.hpp"
void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    Renderer *renderer = static_cast<Renderer *>
        (glfwGetWindowUserPointer(window));

    if (renderer->cam3d->firstMouse) {
        renderer->cam3d->lastX = xpos;  
        renderer->cam3d->lastY = ypos;  
        renderer->cam3d->firstMouse = false;
    }

    float xoff = xpos - renderer->cam3d->lastX;
    float yoff = ypos - renderer->cam3d->lastY;

    renderer->cam3d->lastX = xpos;
    renderer->cam3d->lastY = ypos;

    xoff *= renderer->cam3d->sensitivity;
    yoff *= renderer->cam3d->sensitivity;

    renderer->cam3d->yaw += xoff;
    renderer->cam3d->pitch -= yoff;

    if(renderer->cam3d->pitch > 89.0f) 
        renderer->cam3d->pitch = 89.f;
    if(renderer->cam3d->pitch < -89.f)
        renderer->cam3d->pitch = -89.f;

    renderer->cam3d->updateDirection();
}

void kbCallback(GLFWwindow *win, int key,
        int scanCode, int action, int mode) 
{
    if(key == GLFW_KEY_Q && action != GLFW_PRESS) {
        glfwSetWindowShouldClose(win, true);
    }
}
