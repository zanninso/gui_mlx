#include "./GuiDrawer.hpp"

GuiFont *GuiDrawer::font;

void  GuiDrawer::init_font(std::string const& file_path) 
{
	font = new GuiFont(file_path);
}

bool    GuiDrawer::put_pixel(Image &image, Point p, int color)
{
	if (between(p.x, 0, image.width) && between(p.y, 0, image.height))
    {
		// ((int *)image.data)[p.y * image.width + p.x] = color;
		int i = (p.x * image.bits_per_pixel / 8) + (p.y * image.line_length);
		double percent = ((u_char *)&color)[3] / 255.;
		double rpercent = 1 - percent;
		for (size_t shift = 0; shift < 24; shift += 8, i++)
			// image.data[i] = round(image.data[i] * percent + (color >> shift) * rpercent);
			image.data[i] = round((u_char)image.data[i] * percent + (u_char)(color >> shift) * rpercent);
        return true;
    }
    return false;
}

bool    GuiDrawer::put_pixel_cord(Image &image, int x, int y, int color)
{
	if (between(x, 0, image.width) && between(y, 0, image.height))
    {
		// ((int *)image.data)[y * image.width + x] = color;
		int i = (x * image.bits_per_pixel / 8) + (y * image.line_length);
		double percent = ((u_char *)&color)[3] / 255.;
		double rpercent = 1 - percent;
		for (size_t shift = 0; shift < 24; shift += 8, i++)
			// image.data[i] = round(image.data[i] * percent + (color >> shift) * rpercent);
			image.data[i] = round((u_char)image.data[i] * percent + (u_char)(color >> shift) * rpercent);
        return true;
    }
    return false;
}

bool    GuiDrawer::draw_image(Image &image, Point p, int *data, size_t width, size_t heigth)
{
	for (size_t yd = 0, y = p.y ; yd < heigth ; y++, yd++)
	{
		for (size_t xd = 0, x = p.x ; xd < width ; x++, xd++)
		{
			if (!put_pixel_cord(image, x, y, data[yd * width + xd]))
				break;
		}
	}
    return false;
}

void    GuiDrawer::draw_rectangle(Image &image, Point p1, Point p2, int color)
{
	int	i;
	if ((color >> 24) != 255)
		while (p1.y <= p2.y)
		{
			i = p1.x;
			while (i <= p2.x)
			{
				if (!put_pixel(image, Point(i,  p1.y), color))
					break;
				i++;
			}
			p1.y++;
		}
}

void    GuiDrawer::draw_border(Image &image, Point p1, Point p2, int size, int color)
{
	int	i;
	if (size > 0) {
		Point pb1(p1.x - size, p1.y - size);
		Point pb2(p2.x + size, p2.y + size);
		draw_rectangle(image, pb1, Point(p2.x + size, p1.y), color);
		draw_rectangle(image, pb1, Point(p1.x, p2.y + size), color);
		draw_rectangle(image, Point(p2.x, p1.y), pb2, color);
		draw_rectangle(image, Point(p1.x, p2.y), pb2, color);
	}
}


void	GuiDrawer::draw_string(Image &image, Point p, std::string const &string, int size, int color)
{
	if (font == nullptr)
		init_font("./assets/font/timeburner-font/Timeburner-xJB8.ttf");
	font->set_size(size);
	FT_Face face = font->get_face();
	for (size_t i = 0; i < string.length(); i++)
	{
		font->render_char(string[i]);
		int y_off = font->get_y_off();
		int x_off = font->get_x_off();

		int rows = face->glyph->bitmap.rows;
		int width = face->glyph->bitmap.width;
		for (int i = 0; i < rows; i++)
		{
			int row_offset = p.y + i + y_off;
			for (int j = 0; j < width; j++)
			{
				uint8_t pixel = face->glyph->bitmap.buffer[i * width + j];
				if (pixel) {
					((uint8_t *)(&color))[3] = 255 - pixel;
					put_pixel(image, Point(p.x + j + x_off, row_offset), color);
				}
			}
		}
		p.x += font->get_advance();
	}
}