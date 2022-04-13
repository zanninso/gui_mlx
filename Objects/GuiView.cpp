#include "./GuiView.hpp"

GuiView::GuiView():AGuiObject(0, 0, "") {}

GuiView::GuiView(int x, int y, int width, int height, std::string const &name):AGuiObject(x, y, name) {
    this->width = width;
    this->height = height;
    this->x_max = x + width;
    this->y_max = y + height;
}

GuiView::GuiView(GuiView const &other){
     *this = other;
}

GuiView& GuiView::operator=(GuiView const &other) {
    if (this != &other)
    {
        this->objects.clear();
        this->objects_map.clear();
        for (auto *obj: other.objects)
        {
            AGuiObject *co = obj->clone();
            objects_map.insert(std::pair<std::string, AGuiObject *>(co->get_name(), co));
            objects.push_back(co);
        }
        //     this->objects = other.objects;
        // this->objects_map = other.objects_map;
        AGuiObject::operator=(other);
    }
    return *this;
}

GuiView::~GuiView() {}

bool GuiView::insert_object(AGuiObject const &object) {
    AGuiObject *co = object.clone();
    co->set_x(co->get_x() + x);
    co->set_y(co->get_y() + y);
    std::pair<std::string, AGuiObject *> item(co->get_name(), co);
    if (objects_map.insert(item).second == false)
    {
        delete co;
        return false;
    }
    objects.push_back(co);
    return true;
}

AGuiObject *GuiView::get_object(std::string const& name) {
    auto it = objects_map.find(name); 
    if (it == objects_map.end())
        return nullptr;
    return it->second;
}

AGuiObject * GuiView::get_object_by_position(int x, int y) {
    auto end = objects.rend();
    for (auto it = objects.rbegin(); it != end; it++) {
        if (between(x, (*it)->get_x(), (*it)->get_x_max()) && between(y, (*it)->get_y(), (*it)->get_y_max()))
        {
            if (!(*it)->is_hidden() && (*it)->is_enabled())
                return *it;
        }
    }
    return this;    
}

void GuiView::draw(Image win_image) const {
    if (hidden == false) {
        GuiDrawer::draw_border(win_image, Point(x,y), Point(x_max, y_max), border_size, border_color);
        GuiDrawer::draw_rectangle(win_image, Point(x,y), Point(x_max, y_max), color);
        auto end = objects.end();
        for (auto it = objects.begin() ; it != end; it++)
            (*it)->draw(win_image);
    }
}

AGuiObject *GuiView::clone() const {
    return new GuiView(*this);
}