#ifndef GUI_FONT_HPP
# define GUI_FONT_HPP

#include <string>
#include <exception>
#include "Structs.hpp"
#include <sys/_types/_u_int.h>
extern "C"
{
   
    #include "ft2build.h"
    #include "freetype/freetype.h"
    #include "freetype/ftglyph.h"
}

class GuiFont
{
private:
    FT_Library ft;
	FT_Face face;
    u_int32_t size;
	u_int bbox_ymax;
	u_int bbox_ymin;
    int x_off;
    int y_off;
    u_int advance;
    
public:
    GuiFont(std::string const &font_path);
    ~GuiFont();
    int get_x_off();
    int get_y_off();
	u_int get_bbox_ymax();
    u_int get_advance();
	FT_Face get_face();
	FontDim get_string_dim(std::string const &str, u_int size);

    void set_size(u_int size);
    void render_char(char c);
};

#endif