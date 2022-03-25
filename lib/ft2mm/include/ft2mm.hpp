#ifndef FT2MM_H
#define FT2MM_H
#include <freetype2/freetype/freetype.h>
#include <string>

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
            FT_GlyphSlotRec_ **glyph = &(base->glyph);

            void setSize(int pxW, int pxH);
            void loadChar(char c, long attr);
    };
    
};
#endif
