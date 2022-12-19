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
#include "gui/views/plane.hpp"

#include "util.hpp"

int main() {
    GLFWwindow *window = initGLFW();
    Renderer *renderer = new Renderer();
    Cam3D camm;

    lookupJoystick();
    renderer->setCam3d(camm);
    glfwSetWindowUserPointer(window, renderer);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int w, int h){
            static_cast<Renderer*>(glfwGetWindowUserPointer(window))
            ->update(w, h);
            });

    renderer->add(new Cube());
    Plane plane;
    renderer->add(&plane);
    renderer->prepare();

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
    while(!glfwWindowShouldClose(window)){
        updateTime(); //dt
        processInput(window, renderer); // input

        glClearColorHex("#202020"); //clear
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //plane
        plane.program->use();
        plane.program->setMat4("p", renderer->cam3d->projection);
        plane.program->setMat4("v", renderer->cam3d->view);
        plane.draw();

        renderer->program->use();
        renderer->program->setMat4("m", glm::mat4(1.f));
        renderer->program->setMat4("m", 
                glm::rotate(glm::mat4(1.0f),
                    currentTime, 
                    glm::vec3(1.f, 2.f, 3.f)
                    )
                );

        renderer->childs[0]->draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete renderer;
    glfwTerminate();

    return 0;
}
