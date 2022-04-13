#ifndef GUI_CHECK_BOX_HPP
# define GUI_CHECK_BOX_HPP

#include "AGuiObject.hpp"
#include "GuiLabel.hpp"
#include <cmath>

class GuiCheckBox : public AGuiObject
{
public:
    bool checked;

private:
    GuiLabel label;
    u_int offset;
    u_int size;
    u_int padding;

public:
    GuiCheckBox();
    GuiCheckBox(int x, int y, std::string const & name, std::string const & label, u_int size = 10);
    GuiCheckBox(GuiCheckBox const &other);
    GuiCheckBox& operator=(GuiCheckBox const &other);
    ~GuiCheckBox();
    u_int get_size();
    void    set_size(u_int size);
    void    set_padding(u_int size);
    void    set_label_value(std::string const &label);
    void    set_label_size(int size);
    void    set_label_color(int color);

    void    set_x(int x);
    void    set_y(int y);
    void    set_width(int width);
    void    set_height(int height);

    void draw(Image win_image) const;
    AGuiObject *clone() const;
private:
    void set_check_box_event();
};

#endif