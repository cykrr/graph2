#include <iostream>

#include <glm/glm.hpp>

#include "ft2mm.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "vkfw/vkfw.hpp"

namespace GUI {
    bool init();
}
namespace GUI {
    bool init()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        return EXIT_SUCCESS;
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
    }
}

int main() {
    GUI::init();
}
