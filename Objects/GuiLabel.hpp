#ifndef GUI_LABEL_HPP
# define GUI_LABEL_HPP

#include "AGuiObject.hpp"
#include <string>

class GuiLabel : public AGuiObject
{
private:
    int size;
    std::string value;

public:
    GuiLabel();
    GuiLabel(int x, int y, std::string const & name, std::string const & value);
    GuiLabel(GuiLabel const &other);
    GuiLabel& operator=(GuiLabel const &other);
    ~GuiLabel();
    int get_size() const;
    std::string const &get_value() const;
    void set_size(int size);
    void set_value(std::string const &value);
    void draw(Image win_image) const;
    AGuiObject *clone() const;
};

GuiLabel::GuiLabel():AGuiObject(0, 0, ""), value("") {
    size = 14;
    color = 0;
    width = 0;
    height = 0;
}

GuiLabel::GuiLabel(int x, int y, std::string const & name,
        std::string const & value):AGuiObject(x, y, name), value(value) {
    size = 14;
    color = 0;
    // calculate and set the height and width of the text(each time text or size changed)
}

GuiLabel::GuiLabel(GuiLabel const &other){
     *this = other;
}

GuiLabel& GuiLabel::operator=(GuiLabel const &other) {
    if (this != &other)
    {
        this->color = other.color; 
	    this->size = other.size;
	    this->value = other.value;
        AGuiObject::operator=(other);
    }
    return *this;
}

GuiLabel::~GuiLabel() {}

int GuiLabel::get_size() const {
    return size;
}

std::string const &GuiLabel::get_value() const {
    return value;
}


void GuiLabel::set_size(int size) {
    this->size = size;
    FontDim fdim = GuiFont("./assets/font/timeburner-font/Timeburner-xJB8.ttf").get_string_dim(value, size);
    set_width(fdim.width);
    set_height(fdim.height);
}

void GuiLabel::set_value(std::string const &value) {
    this->value = value;
    FontDim fdim = GuiFont("./assets/font/timeburner-font/Timeburner-xJB8.ttf").get_string_dim(value, size);
    set_width(fdim.width);
    set_height(fdim.height);
}

void GuiLabel::draw(Image win_image) const {
    if (hidden == false) {
        GuiDrawer::draw_string(win_image, Point(x, y), value, size, color);
    }
}

AGuiObject *GuiLabel::clone() const {
    return new GuiLabel(*this);
}

#endif