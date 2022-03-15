#include <iostream>

#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace FreeType2 {
    class Library 
    {
    public:
        FT_Library base;
        Library();
    };
    
    class Face 
    {
        public:
            FT_Face base;

            Face(Library     library, 
                std::string  filePath,
                int          faceIndex);

            void setSize(int pxW, int pxH);
    };
    
};

namespace FreeType2 
{
    Library::Library()
    {
        if (FT_Init_FreeType(&base))
            std::cout << "ERROR: couldn\'t init ft2\n";
    }

    Face::Face( Library     library, 
                std::string filePath,
                int     faceIndex)
    {
        if (FT_New_Face(library.base, filePath.c_str(),
                    faceIndex, &base))
            std::cout << "ERROR: couldn\'t load font\n";
    }

    void Face::setSize(int pxW, int pxH)
    {
        if (FT_Set_Pixel_Sizes(base, pxW, pxH))
            std::cout << "ERROR: couldn\'t set font size\n";

    }
}
            


int main() {
    FreeType2::Library ft2lib;
    FreeType2::Face face(ft2lib, "fonts/Cantarell.otf", 0);
    face.setSize(0, 48);


}
