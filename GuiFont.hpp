#ifndef GUI_FONT_HPP
# define GUI_FONT_HPP

#include <string>
#include <exception>
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
    u_int size;
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

GuiFont::GuiFont(std::string const &font_path)
{
    int error;
    try
    {
        error = FT_Init_FreeType(&ft);
        if (!error)
            error = FT_New_Face(ft, font_path.c_str(), 0, &face);
        if (error)
            throw std::runtime_error(FT_Error_String(error));
    }
    catch(const std::exception& e)
    {
        FT_Done_FreeType(ft);
        FT_Done_Face(face);
    }
    
}

int GuiFont::get_x_off() { return x_off; }

int GuiFont::get_y_off() { return y_off; }

u_int GuiFont::get_bbox_ymax() { return bbox_ymax; }

u_int GuiFont::get_advance() { return advance; }

FT_Face GuiFont::get_face() { return face; }

FontDim GuiFont::get_string_dim(std::string const &str, u_int size) {
    int width = 0;

    set_size(size);
    for (size_t i = 0; i < str.length(); i++)
    {
	    FT_Load_Char(face, str[i], FT_LOAD_DEFAULT);
        width += face->glyph->metrics.horiAdvance >> 6;
    }
    return FontDim(width, bbox_ymax);
}

void GuiFont::set_size(u_int size)
{
    FT_Set_Pixel_Sizes(face, 0, size);
    this->size = size;
    render_char(' ');
    int vertadvance = face->glyph->metrics.vertAdvance / 64;
    bbox_ymax = FT_MulFix(face->bbox.yMax, face->size->metrics.y_scale) >> 6;
    bbox_ymin = FT_MulFix(face->bbox.yMin, face->size->metrics.y_scale) >> 6;
    // bbox_ymax = vertadvance > bbox_ymax ? bbox_ymax : vertadvance;
    // int desc = FT_MulFix(face->descender, face->size->metrics.y_scale) >> 6;
    bbox_ymax = (bbox_ymax + bbox_ymin);
}

void GuiFont::render_char(char c)
{
	FT_Load_Char(face, c, FT_LOAD_RENDER);
	advance = face->glyph->metrics.horiAdvance >> 6;
    x_off = (advance - (face->glyph->metrics.width >> 6)) / 2;
	y_off = (bbox_ymax - face->glyph->metrics.horiBearingY / 64);
}

GuiFont::~GuiFont()
{
    // FT_Done_FreeType(ft);
    // FT_Done_Face(face);
}




#endif