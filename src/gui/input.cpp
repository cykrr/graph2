#include "gui/input.hpp"
void processInput(GLFWwindow *window)
{
    Renderer *renderer = static_cast<Renderer *>
        (glfwGetWindowUserPointer(window));
    MovingCamera *movingCam = static_cast<MovingCamera *>
        (renderer->camera);

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_TRUE)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_TRUE){
        renderer->camera->moveFront();
        printf("in %f\n", (movingCam->speed * movingCam->vFront * dt).z);

    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_TRUE)
        renderer->camera->moveBack();

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_TRUE)
        renderer->camera->moveLeft();

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_TRUE)
        renderer->camera->moveRight();

}
