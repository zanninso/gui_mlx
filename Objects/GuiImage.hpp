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


#endif