#ifndef GUI_HPP
# define GUI_HPP
#include <map>
#include <vector>
#include <string>
#include <thread>
#include <unistd.h>
#include "Objects/AGuiObject.hpp"
#include <unordered_map>
extern "C"
{
    #include <mlx.h>
}

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};


int mouse_up_event(int button, int x, int y, void* param);
int mouse_down_event(int button, int x, int y, void* param);
int mouse_move_event(int x, int y, void* param);
int key_press_event(int key_code, void* param);
static int draw_loop();


class Gui
{
public:

    static Gui &get()
    {
        // if (gui == nullptr)
        //     gui = new Gui();
        return gui;
    }
    void loop(int width, int height, std::string const &win_name = "Window");
    void draw_objs();
    AGuiObject *get_object_by_position(int x, int y);
    AGuiObject *get_object(std::string const& name);
    void *get_mlx_instance();
    bool insert_object(AGuiObject const &obj);

private:
    static Gui gui;
    struct interface{
	    void	*instance;
	    void	*window;
    };

    Gui ()
    {
        mlx.instance = mlx_init();
    }
    interface mlx;
    Image win_image;
    std::vector<AGuiObject *> objects;
    std::unordered_map<std::string, AGuiObject *> objects_map;
};

Gui Gui::gui;


AGuiObject *Gui::get_object_by_position(int x, int y)
{
    auto end = objects.rend();
    for (auto it = objects.rbegin(); it != end; it++) {
        if (between(x, (*it)->get_x(), (*it)->get_x_max()) && between(y, (*it)->get_y(), (*it)->get_y_max()))
        {
            if (!(*it)->is_hidden())
                return (*it)->get_object_by_position(x, y);
        }
    }
    return nullptr;
}

AGuiObject *Gui::get_object(std::string const& name) {
    auto it = objects_map.find(name); 
    if (it == objects_map.end())
        return nullptr;
    return it->second;
}

void * Gui::get_mlx_instance() {
    return mlx.instance;
}

bool Gui::insert_object(AGuiObject const &obj) {
    AGuiObject *co = obj.clone();
    std::pair<std::string, AGuiObject *> item(co->get_name(), co);
    if (objects_map.insert(item).second == false)
    {
        delete co;
        return false;
    }
    objects.push_back(co);
    return true;
}

void Gui::draw_objs() {
    auto end = objects.end();
    for (auto it = objects.begin(); it != end; it++)
        (*it)->draw(win_image);
    mlx_put_image_to_window(mlx.instance, mlx.window, win_image.img, 0, 0);
    usleep(100);
}

void Gui::loop(int width, int height, std::string const &win_name)
{
    win_image.width = width;
    win_image.height = height;
    mlx.window = mlx_new_window(mlx.instance, width, height, (char *)win_name.c_str());
    win_image.img = mlx_new_image(mlx.instance, win_image.width, win_image.height);
    win_image.data = mlx_get_data_addr(win_image.img,
                                            &win_image.bits_per_pixel,
                                            &win_image.line_length,
                                            &win_image.endian);

    mlx_hook(mlx.window, ON_MOUSEDOWN, 0, (int(*)())mouse_down_event, this);
    mlx_hook(mlx.window, ON_MOUSEUP, 0, (int(*)())mouse_up_event, this);
    mlx_hook(mlx.window, ON_MOUSEMOVE, 0, (int(*)())mouse_move_event, this);
    mlx_hook(mlx.window, ON_KEYUP, 0, (int(*)())key_press_event, this);
    mlx_loop_hook(mlx.instance, draw_loop, NULL);

    draw_objs();
    mlx_loop(mlx.instance);
}

// ############################################################################

int mouse_down_event(int button, int x, int y, void* param)
{
    std::cout << "mouse_down event listner" << std::endl;
    AGuiObject *obj = Gui::get().get_object_by_position(x, y);
    if (obj != nullptr) {
        obj->mouse_down(button, x, y, param);
    }
    return 0;
}

int mouse_up_event(int button, int x, int y, void* param)
{
    std::cout << "mouse_up event listner" << std::endl;
    AGuiObject *obj = Gui::get().get_object_by_position(x, y);
    if (obj != nullptr) {
        obj->mouse_up(button, x, y, param);
    }
    return 0;
}

int mouse_move_event(int x, int y, void* param)
{
    AGuiObject *obj = Gui::get().get_object_by_position(x, y);
    if (obj != nullptr) {
        obj->mouse_move(x, y, param);
    }
    return 0;
}

int key_press_event(int key_code, void* param)
{
    AGuiObject::key_press_event(key_code, param);
    return 0;
}

static int draw_loop()
{
    Gui::get().draw_objs();
    return 0;
}

#endif