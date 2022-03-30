#ifndef RENDERER_H
#define RENDERER_H
#include "glad/glad.h"
#include "gui/program.hpp"
#include "gui/element.hpp"
#include "gui/cam.hpp"
#include <vector>
class Renderer {
    public:
        Renderer();

        unsigned int VAO, VBO, EBO;

        void initVAO();
        void initVBO();
        void initEBO();

        Program *program;
        void add(Element *element);
        std::vector<Element *>childs;

        void prepare();
        Element *bigger=NULL;

        void draw();
        void setCam(Camera &camera);
        void applyCam();
        Camera *camera = NULL;

        void update(int w, int h);
        int w; 
        int h;

};
#endif
