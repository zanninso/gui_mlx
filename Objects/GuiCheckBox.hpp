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
    void set_size(u_int size);
    void set_label_value(std::string const &label);
    void set_label_size(int size);
    void set_label_color(int color);
    void draw(Image win_image) const;
    AGuiObject *clone() const;
private:
    void set_check_box_event();
};

GuiCheckBox::GuiCheckBox():AGuiObject(0, 0, "") {
    set_size(10);
    set_width(size);
    set_height(size);
    checked = false;
    padding = 5;
    set_label_value("");
    set_check_box_event();
}

GuiCheckBox::GuiCheckBox(int x, int y, std::string const & name,
        std::string const & label, u_int size):AGuiObject(x, y, name) {
    set_size(size);
    set_width(size);
    set_height(size);
    this->checked = false;
    this->padding = 5;
    set_label_value(label);
    set_label_size(20);
    set_check_box_event();
}

GuiCheckBox::GuiCheckBox(GuiCheckBox const &other){
     *this = other;
}

GuiCheckBox& GuiCheckBox::operator=(GuiCheckBox const &other) {
    if (this != &other)
    {
	    this->size = other.size;
	    this->label = other.label;
	    this->checked = other.checked;
        this->offset = other.offset;
        this->padding = other.padding;
        AGuiObject::operator=(other);
    }
    return *this;
}

GuiCheckBox::~GuiCheckBox() {}

u_int GuiCheckBox::get_size() {
    return size;
}

void GuiCheckBox::set_size(u_int size) {
    if (size >= 10 and size <= 200)
    {
        this->size = size;
        border_size = round(size/100. * 10);
        offset = round(size/100. * 15);
    }
}

void GuiCheckBox::set_label_value(std::string const &label) {
    this->label.value = label;
    FontDim fdim = GuiFont("./assets/font/timeburner-font/Timeburner-xJB8.ttf").get_string_dim(label, this->label.size);
    this->label.set_x(x + size + padding);
    this->label.set_y(y + (this->height - fdim.height) / 2);
}

void GuiCheckBox::set_label_size(int size) {
    this->label.size = size;
    FontDim fdim = GuiFont("./assets/font/timeburner-font/Timeburner-xJB8.ttf").get_string_dim(label.value, this->label.size);
    this->label.set_x(x + size + padding);
    this->label.set_y(y + (this->height - fdim.height) / 2);
}

void GuiCheckBox::set_label_color(int color) {
    label.set_color(color);
}

void GuiCheckBox::set_check_box_event() {
    desing_events[MouseClick] = [](int x, int y, int btn, void *param) {
        GuiCheckBox *self = (GuiCheckBox *)param;
        if (self /*&& btn == ?*/ ) {
            if (self->checked)
                self->checked = false;
            else 
                self->checked = true;
        }
    }; 
}

void GuiCheckBox::draw(Image win_image) const {
    if (hidden == false) {
        Point pb0_0(x + border_size, y + border_size);
        Point pb0_1(x + size - border_size, y + size - border_size);
        Point pb1_0(pb0_0.x + offset, pb0_0.y + offset);
        Point pb1_1(pb0_1.x - offset, pb0_1.y - offset);
        GuiDrawer::draw_border(win_image, pb0_0, pb0_1, border_size, border_color);
        GuiDrawer::draw_border(win_image, pb1_0, pb1_1, offset, 0xdad8d8);
        GuiDrawer::draw_rectangle(win_image, pb1_0, pb1_1, checked ? color : 0xdad8d8);
        label.draw(win_image);
    }
}

AGuiObject *GuiCheckBox::clone() const {
    return new GuiCheckBox(*this);
}

#endif