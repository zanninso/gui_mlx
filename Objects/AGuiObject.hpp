#ifndef A_GUI_OBJECT_HPP
#define A_GUI_OBJECT_HPP

# include <functional>
# include <iostream>
# include <string>
# include "color.hpp"
// # include "../Gui.hpp"
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

# endif
