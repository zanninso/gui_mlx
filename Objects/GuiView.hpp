#ifndef GUI_VIEW_HPP
# define GUI_VIEW_HPP

#include "AGuiObject.hpp"
#include <vector>
#include <unordered_map>

class GuiView : public AGuiObject
{
    std::vector<AGuiObject *> objects;
    std::unordered_map<std::string, AGuiObject *> objects_map;

public:
    GuiView();
    GuiView(int x, int y, int width, int height, std::string const & name);
    GuiView(GuiView const &other);
    GuiView& operator=(GuiView const &other);
    ~GuiView();
    bool insert_object(AGuiObject const &object);
    AGuiObject *get_object(std::string const& name);
    AGuiObject *get_object_by_position(int x, int y);
    void draw(Image win_image) const;
    AGuiObject *clone() const;
};

#endif