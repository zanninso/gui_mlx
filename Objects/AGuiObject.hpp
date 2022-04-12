#ifndef A_GUI_OBJECT_HPP
#define A_GUI_OBJECT_HPP

# include <functional>
# include <iostream>
# include <string>
# include "color.hpp"
# include "../Gui.hpp"
# include "../Structs.hpp"
# include "../GuiDrawer.hpp"

extern "C"
{
    #include <mlx.h>
}

enum GuiMouseEvents{
    MouseMove,
    MouseClick,
    MouseDown,
    MouseUp,
};

enum GuiKeyEvents{
    KeyPress,
};

class AGuiObject
{

private:
    static AGuiObject *click_object;
    static AGuiObject *hover_object;
    static AGuiObject *focused_object;

public:
    static void    key_press_event(int keycode, void *param);

protected:
    int x;
    int y;
    int x_max;
    int y_max;
    int width;
    int height;
    bool enabled;
    bool hidden;
    bool is_mouse_on;
    std::string name;
    int color;
    int border_size; 
    int border_color; 
    std::function<void(int x, int y, int button, void *param)> mouse_events[4];
    std::function<void(int x, int y, int button, void *param)> desing_events[4];
    AGuiObject();

public:
    AGuiObject(int x, int y,std::string const &name);
    AGuiObject(AGuiObject const &other);
    AGuiObject& operator=(AGuiObject const &other);
    virtual ~AGuiObject();
    virtual void    mouse_move(int x, int y, void *param);
    virtual void    mouse_click(int x, int y, int button, void *param);
    virtual void    mouse_down(int x,int y, int button, void *param);
    virtual void    mouse_up(int x,int y, int button, void *param);
    virtual void    key_press(int keycode,void *param); // we will use it if we do need to get input
    void            set_mouse_event(std::function<void(int x, int y, int button, void *param)> f, GuiMouseEvents event);
    void            set_desing_event(std::function<void(int x, int y, int button, void *param)> f, GuiMouseEvents event);
    

    void            set_hidden(bool hide);
    void            set_enabled(bool hide);
    void            set_color(int color);
    virtual void    set_x(int x);
    virtual void    set_y(int y);
    virtual void    set_width(int width);
    virtual void    set_height(int height);
    void            set_border_color(int color);
    void            set_border_size(int size);

    bool            is_hidden() const;
    bool            is_enabled() const;
    std::string const& get_name() const;
    int get_x() const;
    int get_y() const;
    int get_x_max() const;
    int get_y_max() const;
    int get_width() const;
    int get_height() const;
    virtual AGuiObject *get_object_by_position(int x, int y);
    virtual AGuiObject *clone() const = 0;
    virtual void    draw(Image win_image) const = 0;
};

AGuiObject *AGuiObject::click_object;
AGuiObject *AGuiObject::hover_object;
AGuiObject *AGuiObject::focused_object;

void AGuiObject::key_press_event(int keycode, void *param) {
    if (focused_object != nullptr)
        focused_object->key_press(keycode, param);
}

AGuiObject::AGuiObject(){}

AGuiObject::AGuiObject(int x, int y, std::string const& name) : x(x), y(y), name(name) {
    color = 0;
    enabled  = true;
    hidden = false;
    is_mouse_on = false;
    border_size = 1;
    border_color = 0;
    memset(desing_events,0,sizeof(desing_events));
    memset(mouse_events,0,sizeof(mouse_events));
    std::cout << "object " << this->name << " created" << std::endl;
}

AGuiObject::AGuiObject(AGuiObject const &other) {
    *this = other;
}

AGuiObject& AGuiObject::operator=(AGuiObject const &other) {
    this->x = other.x;
    this->y = other.y;
    this->x_max = other.x_max;
    this->y_max = other.y_max;
    this->height = other.height;
    this->width =  other.width;
    this->color = other.color;
    this->border_color = other.border_color;
    this->border_size = other.border_size;
    this->enabled = other.enabled;
    this->hidden = other.hidden;
    this->is_mouse_on = other.is_mouse_on;
    this->name = other.name;
    for (size_t i = 0; i < 4; i++) {
        this->desing_events[i] = other.desing_events[i];
        this->mouse_events[i] = other.mouse_events[i];
    }
    return *this;
}

void AGuiObject::mouse_move(int x, int y, void *param) {
    if (enabled)
    {
        if (hover_object != nullptr) {
            hover_object->is_mouse_on = false;
            if (hover_object->desing_events[MouseMove] != nullptr)
                hover_object->desing_events[MouseMove](x, y, 0, hover_object);
            if (hover_object->mouse_events[MouseMove] != nullptr)
                hover_object->mouse_events[MouseMove](x, y, 0, hover_object);
        }
        this->is_mouse_on = true;
        hover_object = this;
        if (desing_events[MouseMove] != nullptr)
            desing_events[MouseMove](x, y, 0, this);
        if (mouse_events[MouseMove] != nullptr)
            mouse_events[MouseMove](x, y, 0, this);
    }
};

void AGuiObject::mouse_click(int x, int y, int button, void *param) {
    if (enabled)
    {
        focused_object = this;
        if (desing_events[MouseClick] != nullptr)
            desing_events[MouseClick](x, y, button, this);
        if (mouse_events[MouseClick] != nullptr)
            mouse_events[MouseClick](x, y, button, this);
        std::cout << "object " << name << " clicked\n";
    }
};

void AGuiObject::mouse_down(int x, int y, int button, void *param) {
    if (enabled)
    {
        AGuiObject::click_object = this;
        if (desing_events[MouseDown] != nullptr)
            desing_events[MouseDown](x, y, button, this);
        if (mouse_events[MouseDown] != nullptr)
            mouse_events[MouseDown](x, y, button, this);
    }
};

void AGuiObject::mouse_up(int x, int y, int button, void *param) {
    if (enabled) {

        if (desing_events[MouseUp] != nullptr)
            desing_events[MouseUp](x, y, button, this);
        if (mouse_events[MouseUp] != nullptr)
            mouse_events[MouseUp](x, y, button, this);

        if (AGuiObject::click_object == this)
        {
            this->mouse_click(button, x, y, param);
        }
        AGuiObject::click_object = nullptr;
    }
};

void AGuiObject::key_press(int keycode, void *param) {
    if (enabled) {
        std::cout << name << " key_pressed" << std::endl;
    }
};

void AGuiObject::set_mouse_event(std::function<void(int x, int y, int button, void *param)> f, GuiMouseEvents event) {
    if (f != nullptr)
        mouse_events[(int)event] = f;
}

void AGuiObject::set_desing_event(std::function<void(int x, int y, int button, void *param)> f, GuiMouseEvents event) {
    if (f != nullptr)
        desing_events[(int)event] = f;
}

bool AGuiObject::is_hidden() const{
    return hidden;
}

bool AGuiObject::is_enabled() const{
    return enabled;
}

void AGuiObject::set_hidden(bool hide) {
    hidden = hide;
}

void AGuiObject::set_enabled(bool enable) {
    enabled = enable;
}

void AGuiObject::set_color(int color) {
    this->color = color;
}

void    AGuiObject::set_x(int x) {
    this->x = x;
    this->x_max = x + width;
}

void    AGuiObject::set_y(int y) {
    this->y = y;
    this->y_max = y + height;
}

void    AGuiObject::set_width(int width) {
    this->width = width;
    this->x_max = x + width;
}
void    AGuiObject::set_height(int height) {
    this->height = height;
    this->y_max = y + height;
}

void    AGuiObject::set_border_color(int color) {
    this->border_color = color;
}

void    AGuiObject::set_border_size(int size) {
    this->border_size = size;
}


std::string const& AGuiObject::get_name() const { return name;}
int AGuiObject::get_x() const { return x;}
int AGuiObject::get_y() const { return y;}
int AGuiObject::get_x_max() const { return x_max;}
int AGuiObject::get_y_max() const { return y_max;}
int AGuiObject::get_width() const {return width;}
int AGuiObject::get_height() const {return height;}
AGuiObject *AGuiObject::get_object_by_position(int x, int y) {
    return this;
}

AGuiObject::~AGuiObject() {
}

#endif
