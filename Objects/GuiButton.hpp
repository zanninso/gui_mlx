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
    void set_label_value(std::string const &label);
    void set_label_size(int size);
    void set_label_color(int color);
    void draw(Image win_image) const;
    AGuiObject *clone() const;
};

GuiButton::GuiButton(Point p, u_int width, u_int height, std::string const & name, std::string const & label)
                    :AGuiObject(p.x, p.y, name), label(p.x, p.y, name, label)
{
    set_width(width);
    set_height(height);
    set_label_value(label);

    desing_events[MouseMove] = [](int x, int y, int btn, void *param) {
        GuiButton *self = (GuiButton *)param;
        if (self) {
            if (self->is_mouse_on) {
                self->border_size = 6;
                self->label.size = 30;
                self->set_label_value("hover in");
            }
            else {
                self->border_size = 1;
                self->label.size = 14;
                self->set_label_value("hover out");
            }
        }
    };

}

GuiButton::GuiButton(GuiButton const &other) {
     *this = other;
}

GuiButton& GuiButton::operator=(GuiButton const &other) {
    if (this != &other)
    {
        label = other.label;
        AGuiObject::operator=(other);
    }
    return *this;
}

GuiButton::~GuiButton() {}

void GuiButton::set_label_value(std::string const &label) {
    this->label.value = label;
    FontDim fdim = GuiFont("./assets/font/timeburner-font/Timeburner-xJB8.ttf").get_string_dim(label, this->label.size);
    this->label.set_x(this->x +  (this->width - fdim.width) / 2);
    this->label.set_y(this->y + (this->height - fdim.height) / 2);
}

void GuiButton::set_label_size(int size) {
    this->label.size = size;
    FontDim fdim = GuiFont("./assets/font/timeburner-font/Timeburner-xJB8.ttf").get_string_dim(label.value, this->label.size);
    this->label.set_x(this->x +  (this->width - fdim.width) / 2);
    this->label.set_y(this->y + (this->height - fdim.height) / 2);
}

void GuiButton::set_label_color(int color) {
    label.set_color(color);
}


void GuiButton::draw(Image win_image) const {
    if (hidden == false) {
        GuiDrawer::draw_border(win_image, Point(x,y), Point(x_max,y_max), border_size, border_color);
        GuiDrawer::draw_rectangle(win_image, Point(x,y), Point(x_max, y_max), 0);
        label.draw(win_image);
    }
}

AGuiObject *GuiButton::clone() const{
    return new GuiButton(*this);
}

#endif