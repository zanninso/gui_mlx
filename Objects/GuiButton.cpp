
#include "./GuiButton.hpp"

GuiButton::GuiButton(Point p, u_int width, u_int height, std::string const & name, std::string const & label)
                    :AGuiObject(p.x, p.y, name), label(p.x, p.y, name, label)
{
    color = Color_Carrot_Orange;
    set_width(width);
    set_height(height);
    printf("label %d, %d\n", this->label.get_x(), this->label.get_y());
    set_label_value(label);
    set_label_size(14);
    desing_events[MouseMove] = [](int x, int y, int btn, void *param) {
        GuiButton *self = (GuiButton *)param;
        if (self) {
            if (self->is_mouse_on) {
                self->border_size = 6;
                // self->label.size = 30;
                self->set_label_size(30);
            }
            else {
                self->border_size = 1;
                // self->label.size = 14;
                self->set_label_size(14);
            }
        }
    };
    printf("label %d, %d\n", this->label.get_x(), this->label.get_y());
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
    this->label.set_value(label);
    this->label.set_x(this->x +  (this->width - this->label.get_width()) / 2);
    this->label.set_y(this->y + (this->height - this->label.get_height()) / 2);
}

void GuiButton::set_label_size(int size) {
    this->label.set_size(size);
    this->label.set_x(this->x +  (this->width - label.get_width()) / 2);
    this->label.set_y(this->y + (this->height - label.get_height()) / 2);
}

void GuiButton::set_label_color(int color) {
    label.set_color(color);
}

void    GuiButton::set_x(int x) {
    this->x = x;
    this->x_max = x + width;
    set_label_size(label.get_size());
}

void    GuiButton::set_y(int y) {
    this->y = y;
    this->y_max = y + height;
    set_label_size(label.get_size());
}

void    GuiButton::set_width(int width) {
    this->width = width;
    this->x_max = x + width;
    set_label_size(label.get_size());
}

void    GuiButton::set_height(int height) {
    this->height = height;
    this->y_max = y + height;
    set_label_size(label.get_size());
}

void GuiButton::draw(Image win_image) const {
    if (hidden == false) {
        GuiDrawer::draw_border(win_image, Point(x,y), Point(x_max,y_max), border_size, border_color);
        GuiDrawer::draw_rectangle(win_image, Point(x,y), Point(x_max, y_max), color);
        label.draw(win_image);
    }
}

AGuiObject *GuiButton::clone() const{
    return new GuiButton(*this);
}
