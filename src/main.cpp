#include <iostream>
#include <stdint.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/glad.h"


#include "gui/color.hpp"
#include "gui/window.hpp"
#include "gui/program.hpp"
#include "gui/renderer.hpp"
#include "gui/input.hpp"
#include "gui/cam.hpp"
#include "gui/views/rectangle.hpp"
#include "gui/views/cube.hpp"
#include "gui/views/3drect.hpp"

#include "util.hpp"



int Swidth = 0; 
int Sheight = 0;

void draw2(){
    float arr[12] = {
     0.5f,  0.5f, -3.0f,  // top right
     0.5f, -0.5f, -3.0f,  // bottom right
    -0.5f, -0.5f, -3.0f,  // bottom left
    -0.5f,  0.5f, -3.0f   // top left 
    };  

    unsigned int arr2[6] = {
        0, 1, 3, 1, 2, 3
    };

    glBufferSubData(GL_ARRAY_BUFFER, 
            0, 12 * sizeof(float), 
            arr);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 
            0, 6 * sizeof(unsigned int), 
            arr2);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
}

int main() {
    GLFWwindow *window = initGLFW();

    Renderer *renderer = new Renderer();

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

    glEnable(GL_DEPTH_TEST);

    renderer->program->use();

    renderer->w = 800; renderer->h = 800;

    Cam3D camm;
    camm.speed = 2.5f;

    renderer->setCam3d(camm);

    glfwSetWindowUserPointer(window, renderer);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int w, int h){
            static_cast<Renderer*>(glfwGetWindowUserPointer(window))
            ->update(w, h);
            });

    renderer->add(new Rect3d());
    renderer->add(new Cube());
    renderer->prepare();


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    while(!glfwWindowShouldClose(window)){
        GLFWgamepadstate state;
        glfwGetGamepadState(GLFW_JOYSTICK_2, &state);

        updateTime();

        glClearColorHex("#202020");
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        renderer->program->use();

        if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -0.1 ||
                isPressed(window, GLFW_KEY_W) ) {
            camm.pos += camm.front * camm.speed * dt  ;
        }
            
        if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > 0.1 || 
                isPressed(window, GLFW_KEY_S)){
            camm.pos -= camm.front * camm.speed * dt;
        }

        if(state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -0.1 ||
                isPressed(window, GLFW_KEY_A))
            camm.pos += glm::normalize(glm::cross(camm.up, camm.front)) *
                camm.speed * dt;

        if(state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > 0.1 ||
                isPressed(window, GLFW_KEY_D))
            camm.pos -= glm::normalize(glm::cross(camm.up, camm.front)) *
                camm.speed * dt;

        if(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] > 0.1 ||
                state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] < -0.1){
            printf ("%f\n", state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);
            camm.yaw += state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
        }

        if(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] > 0.1 ||
                state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] < -0.1){
            camm.pitch -= state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
        }


        if(renderer->cam3d->pitch > 89.0f) 
            renderer->cam3d->pitch = 89.f;
        if(renderer->cam3d->pitch < -89.f)
            renderer->cam3d->pitch = -89.f;

        renderer->cam3d->updateDirection();

        renderer->sendView();




        renderer->program->setMat4("m", glm::mat4(1.f));

        renderer->childs[0]->draw();
        renderer->childs[1]->draw();

        
        renderer->program->setMat4("m", glm::rotate(glm::mat4(1.0f), currentTime, glm::vec3(1.f, 2.f, 3.f)));
        glBindVertexArray(renderer->VAO);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &renderer->VAO);
    glDeleteBuffers(1, &renderer->VBO);
    glfwTerminate();

    return 0;
}
