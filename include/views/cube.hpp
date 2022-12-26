#ifndef CUBE_H
#define CUBE_H
#include "drawable.hpp"
class Cube : public Drawable {
    public:
    Cube();
    void draw() override;
    static const char *get_name() {
        return "Cube";
    }
    static const float * get_vert() {return cubeVertices;}
    private:
    static float cubeVertices[];
};

#endif
