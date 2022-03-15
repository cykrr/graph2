#include <iostream>

#include <GLFW/glfw3.h>

#include "ft2mm.hpp"

int main() {
    FreeType2::Library ft2lib;
    FreeType2::Face face(ft2lib, "fonts/Cantarell.otf", 0);
    face.setSize(0, 48);
    for( unsigned char c = 0; c < 128; c++)
    {
        face.loadChar(c, FT_LOAD_RENDER);
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0, 
                GL_RED,
                face.base->glyph->bitmap.width,
                face.base->glyph->bitmap.rows,
                0, 
                GL_RED,
                GL_UNSIGNED_BYTE,
                face.base->glyph->bitmap.buffer
                );

        glTexParameteri(
                GL_TEXTURE_2D, 
                GL_TEXTURE_WRAP_S, 
                GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D,
                GL_TEXTURE_WRAP_T,
                GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D,
                GL_TEXTURE_MIN_FILTER,
                GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D,
                GL_TEXTURE_MAG_FILTER,
                GL_LINEAR);
    }


}
