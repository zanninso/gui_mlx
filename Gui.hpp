#ifndef GUI_HPP
# define GUI_HPP

# include <map>
# include <vector>
# include <string>
# include <thread>
# include <unistd.h>
# include "Objects/AGuiObject.hpp"
# include <unordered_map>
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

#endif