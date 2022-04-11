#include "Gui.hpp"
#include "Objects/GuiImage.hpp"
#include "Objects/GuiButton.hpp"
#include "Objects/GuiCheckBox.hpp"
#include "Objects/GuiView.hpp"
#include <iostream>

int main() {
    std::cout << "start" << std::endl;
    Gui &gui = Gui::get();
    // std::cout << "gui" << std::endl;
    gui.insert_object(GuiImage(0, 0, "goban", "assets/images/goban.xpm"));
    // std::cout << "obj1" << std::endl;
    gui.insert_object(GuiImage(300, 200, "white piece", "assets/images/white.xpm"));
    // std::cout << "obj2" << std::endl;
    gui.insert_object(GuiImage(300, 250, "black piece", "assets/images/black.xpm"));

    GuiView test_view(100, 100, 500, 500, "view0");

    test_view.set_color(0xffffff);

    GuiButton btn1(Point(110, 40), 220, 70, "botona1", "mohamed");
    btn1.set_color(0);
    btn1.set_label_color(0xffffff);
    btn1.set_mouse_event([](int x,int y, int btn, void *param) {
        std::cout << "ha lclick\n";
    }, MouseClick);

    test_view.insert_object(btn1);
    
    gui.insert_object(test_view);
    
    // gui.set_object(GuiButton(Point(110, 40), 200, 70, "botona1", "mohamed"));

    // gui.set_object(GuiButton(Point(700, 40), 100, 100, "botona2", "botton2"));
    
    // gui.set_object(GuiCheckBox(600, 40, "check_box_1", "check box1", 20));

    gui.loop(1920, 1080);
}