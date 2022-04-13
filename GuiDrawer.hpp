#ifndef GUI_DRAWER_HPP
#define GUI_DRAWER_HPP

#include <cmath>
#include <sys/_types/_u_int.h>
#include <sys/_types/_u_char.h>
// #include "Gui.hpp"
#include "Structs.hpp"
#include "GuiFont.hpp"


class GuiDrawer
{
private:
    GuiDrawer(/* args */);
	static GuiFont *font;
public:
    static void init_font(std::string const& file_path);
    static inline bool put_pixel(Image &image, Point p, int color);
	static inline bool put_pixel_cord(Image &image, int x, int y, int color);
    static void draw_rectangle(Image &image, Point p1, Point p2, int color);
    static void draw_border(Image &image, Point p1, Point p2, int size, int color);
	static void draw_string(Image &image, Point p, std::string const &string, int size, int color);
	static bool draw_image(Image &image, Point p, int *data, size_t width, size_t heigth);
};

#endif