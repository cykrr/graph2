#include "input.hpp"
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


void processInput(GLFWwindow *window, Renderer *renderer) {

    GLFWgamepadstate state;
    glfwGetGamepadState(GLFW_JOYSTICK_2, &state);
    
    if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -0.1 ||
            isPressed(window, GLFW_KEY_W) ) {
        renderer->cam3d->pos += renderer->cam3d->front * renderer->cam3d->speed * dt  ;
    }
        
    if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > 0.1 || 
            isPressed(window, GLFW_KEY_S)){
        renderer->cam3d->pos -= renderer->cam3d->front * renderer->cam3d->speed * dt;
    }

    if(state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -0.1 ||
            isPressed(window, GLFW_KEY_A))
        renderer->cam3d->pos += glm::normalize(glm::cross(renderer->cam3d->up, renderer->cam3d->front)) *
            renderer->cam3d->speed * dt;

    if(state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > 0.1 ||
            isPressed(window, GLFW_KEY_D))
        renderer->cam3d->pos -= glm::normalize(glm::cross(renderer->cam3d->up, renderer->cam3d->front)) *
            renderer->cam3d->speed * dt;

    if(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] > 0.1 ||
            state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] < -0.1){
        printf ("%f\n", state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);
        renderer->cam3d->yaw += state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
    }

    if(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] > 0.1 ||
            state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] < -0.1){
        renderer->cam3d->pitch -= state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
    }

    if(isPressed(window, GLFW_KEY_Q))
        glfwSetWindowShouldClose(window, true);


    renderer->cam3d->updateDirection();

    renderer->sendView();
}

void lookupJoystick() {
    int joystickPresent = glfwJoystickPresent(GLFW_JOYSTICK_2);
    if (joystickPresent) {
        std::cout << "1:" << 
            glfwGetJoystickName(GLFW_JOYSTICK_1) << '\n';
        std::cout << "2:" << 
            glfwGetJoystickName(GLFW_JOYSTICK_2) << '\n';
        std::cout << "3:" << 
            glfwGetJoystickName(GLFW_JOYSTICK_3) << '\n';
        std::cout << "4:" << 
            glfwGetJoystickName(GLFW_JOYSTICK_4) << '\n';
        
    }

}
