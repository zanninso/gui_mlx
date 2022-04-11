#ifndef GUI_LABEL_HPP
# define GUI_LABEL_HPP

#include "AGuiObject.hpp"

class GuiLabel : public AGuiObject
{
private:

public:
    int size;
    std::string value;

public:
    GuiLabel();
    GuiLabel(int x, int y, std::string const & name, std::string const & value);
    GuiLabel(GuiLabel const &other);
    GuiLabel& operator=(GuiLabel const &other);
    ~GuiLabel();
    void draw(Image win_image) const;
    AGuiObject *clone() const;
};

GuiLabel::GuiLabel():AGuiObject(0, 0, ""), value("") {
    size = 14;
    color = 0;
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

void GuiLabel::draw(Image win_image) const {
    if (hidden == false) {
        GuiDrawer::draw_string(win_image, Point(x,y), value, size, color);
    }
}

AGuiObject *GuiLabel::clone() const {
    return new GuiLabel(*this);
}

#endif