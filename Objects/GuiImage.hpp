#ifndef GUI_IMAGE_HPP
#define GUI_IMAGE_HPP

#include "./AGuiObject.hpp"

class GuiImage: public AGuiObject
{
private:
    std::string path;
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     length;
public:
    GuiImage(int x,int y, std::string const &name, std::string const &path);
    GuiImage(GuiImage const &other);
    GuiImage& operator=(GuiImage const &other);
    ~GuiImage();
    void draw(Image win_image) const;
    AGuiObject *clone() const;

};


GuiImage::GuiImage(int x,int y, std::string const &name, std::string const &path): AGuiObject(x, y, name), path(path)
{
    img = mlx_xpm_file_to_image(Gui::get().get_mlx_instance(), (char *)path.c_str(), 
                                                  &width, &height);
    addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
    set_width(width);
    set_height(height);
}

void GuiImage::draw(Image win_image) const {
    if (hidden == false) {
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

#endif