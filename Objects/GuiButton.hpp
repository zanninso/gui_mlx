#ifndef GUI_BUTTON_HPP
# define GUI_BUTTON_HPP

#include "AGuiObject.hpp"
#include "GuiLabel.hpp"

class GuiButton: public AGuiObject
{
private:
    GuiLabel label;
public:
    GuiButton(Point p,u_int width,u_int height, std::string const & name, std::string const & label);
    GuiButton(GuiButton const &other);
    GuiButton& operator=(GuiButton const &other);
    ~GuiButton();
    void    set_label_value(std::string const &label);
    void    set_label_size(int size);
    void    set_label_color(int color);

    void    set_x(int x);
    void    set_y(int y);
    void    set_width(int width);
    void    set_height(int height);

    void draw(Image win_image) const;
    AGuiObject *clone() const;
};

#endif