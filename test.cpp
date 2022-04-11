#include "Gui.hpp"
#include "Objects/GuiImage.hpp"
#include "Objects/GuiButton.hpp"
#include "Objects/GuiCheckBox.hpp"
#include "Objects/GuiView.hpp"
#include <iostream>

int main() {
    std::cout << "start" << std::endl;
    Gui &gui = Gui::get();

    // gui.insert_object(GuiImage(0, 0, "goban", "assets/images/goban.xpm"));

    // gui.insert_object(GuiImage(300, 200, "white piece", "assets/images/white.xpm"));

    // gui.insert_object(GuiImage(300, 250, "black piece", "assets/images/black.xpm"));

    GuiView select_player(480, 35, 1000, 1000, "");
    select_player.set_color(0xffffff);

    GuiLabel select_player_title(320, 20, "title", "Select Player 1");
    select_player_title.set_size(60);

    GuiImage player(50, 350, "player", "assets/images/player.xpm");
    GuiImage remote_player(350, 350, "remote_player", "assets/images/remote_player.xpm");
    GuiImage ai_player(650, 350, "ai_player", "assets/images/ai_player.xpm");
    player.set_border_size(3);
    remote_player.set_border_size(3);
    ai_player.set_border_size(3);

    int cb_size = 30;
    int cb_off = (250 - cb_size) / 2;
    GuiCheckBox cb_player(50 + cb_off, 610, "cb_player", "", cb_size);
    GuiCheckBox cb_remote_player(350 + cb_off, 610, "cb_remote_player", "", cb_size);
    GuiCheckBox cb_ai_player(650 + cb_off, 610, "cb_ai_player", "", cb_size);

    GuiButton btn_next(Point(760, 900), 220, 70, "btn_next", "Next >>");
    GuiButton btn_prev(Point(20, 900), 220, 70, "btn_prev", "<< Prev");


    select_player.insert_object(select_player_title);

    select_player.insert_object(player);
    select_player.insert_object(remote_player);
    select_player.insert_object(ai_player);

    select_player.insert_object(cb_player);
    select_player.insert_object(cb_remote_player);
    select_player.insert_object(cb_ai_player);

    select_player.insert_object(btn_next);
    select_player.insert_object(btn_prev);


   

    // GuiButton btn1(Point(110, 40), 220, 70, "botona1", "mohamed");
    // btn1.set_color(0);
    // btn1.set_label_color(0xffffff);
    // btn1.set_mouse_event([](int x,int y, int btn, void *param) {
    //     std::cout << "ha lclick\n";
    // }, MouseClick);

    // test_view.insert_object(btn1);
    
    gui.insert_object(select_player);
    
    // gui.set_object(GuiButton(Point(110, 40), 200, 70, "botona1", "mohamed"));

    // gui.set_object(GuiButton(Point(700, 40), 100, 100, "botona2", "botton2"));
    
    // gui.set_object(GuiCheckBox(600, 40, "check_box_1", "check box1", 20));

    gui.loop(1920, 1080);
}