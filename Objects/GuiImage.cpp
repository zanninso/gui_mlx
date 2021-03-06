#include "./GuiImage.hpp"
#include "../Gui.hpp"

GuiImage::GuiImage(int x,int y, std::string const &name, std::string const &path): AGuiObject(x, y, name), path(path)
{
    img = mlx_xpm_file_to_image(Gui::get().get_mlx_instance(), (char *)path.c_str(), 
                                                  &width, &height);
    addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
    set_width(width);
    set_height(height);
    border_size = 0;
}

void GuiImage::draw(Image win_image) const {
    if (hidden == false) {
        GuiDrawer::draw_border(win_image, Point(x,y), Point(x_max,y_max), border_size, border_color);
        GuiDrawer::draw_image(win_image, Point(x,y), (int *)addr, width, height);
    }
}

AGuiObject *GuiImage::clone() const{
    return new GuiImage(*this);
}

GuiImage::GuiImage(GuiImage const &other) {
    *this = other;
}

GuiImage& GuiImage::operator=(GuiImage const &other) {
    if (this != &other)
    {
        this->img = other.img; // deep copy needed here
	    this->addr = other.addr; // deep copy needed here
	    this->bits_per_pixel = other.bits_per_pixel;
	    this->line_length = other.line_length;
	    this->endian = other.endian;
        this->length = other.length;
        AGuiObject::operator=(other);
    }
    return *this;
}

GuiImage::~GuiImage()
{
}