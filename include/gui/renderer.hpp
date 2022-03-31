#ifndef RENDERER_H
#define RENDERER_H
#define GLFW_INCLUDE_NONE
#include "gui/program.hpp"
#include "gui/element.hpp"
#include "gui/cam.hpp"
#include <vector>
#include "glad/glad.h"
class Renderer {
    public:
        Renderer();

        unsigned int VAO, VBO, EBO;

        void initVAO();
        void initVBO();
        void initEBO();

        Program *program = NULL;
        void add(Element *element);
        std::vector<Element *>childs;

        void prepare();
        Element *bigger = NULL;

        void draw();
        void setCam3d(Cam3D & cam);
        void applyCam();
        Cam3D *cam3d = NULL;

        void update(int w, int h);
        int w; 
        int h;

        void sendView();

};
#endif