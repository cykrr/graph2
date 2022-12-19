#ifndef CUBE_H
#define CUBE_H
#include "gui/drawable.hpp"
class Cube : public Drawable {
    public:
    Cube();
    void draw() override;
    static const char *get_name() {
        return "Cube";
    }
    private:
    static float cubeVertices[];
};

#endif
