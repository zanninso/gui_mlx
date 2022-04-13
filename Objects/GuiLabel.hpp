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

#endif