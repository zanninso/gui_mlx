#include "Gui.hpp"
#include "Objects/GuiImage.hpp"
#include "Objects/GuiButton.hpp"
#include "Objects/GuiCheckBox.hpp"
#include "Objects/GuiView.hpp"
#include <iostream>
typedef std::string const & str;

GuiView select_player_view1() {

    GuiView select_player(480, 35, 1000, 1000, "select_player1");
    select_player.set_color(Color_White);

    GuiLabel select_player_title(320, 20, "title", "SELECT PLAYER 1");
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
    // GuiButton btn_prev(Point(20, 900), 220, 70, "btn_prev", "<< Prev");

    btn_next.set_mouse_event([](int x, int y, int btn, void *param) {
            Gui::get().get_object("select_player1")->set_hidden(true);
            Gui::get().get_object("select_player2")->set_hidden(false);
    }, MouseClick);

    select_player.insert_object(select_player_title);

    select_player.insert_object(player);
    select_player.insert_object(remote_player);
    select_player.insert_object(ai_player);

    select_player.insert_object(cb_player);
    select_player.insert_object(cb_remote_player);
    select_player.insert_object(cb_ai_player);

    select_player.insert_object(btn_next);
    // select_player.insert_object(btn_prev);

    return select_player;
}

GuiView select_player_view2() {

    GuiView select_player(480, 35, 1000, 1000, "select_player2");
    select_player.set_color(Color_White);
    select_player.set_hidden(true);

    GuiLabel select_player_title(320, 20, "title", "SELECT PLAYER 2");
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

    btn_next.set_mouse_event([](int x, int y, int btn, void *param) {
        Gui::get().get_object("select_player2")->set_hidden(true);
        Gui::get().get_object("select_rules")->set_hidden(false);
    }, MouseClick);

    btn_prev.set_mouse_event([](int x, int y, int btn, void *param) {
        Gui::get().get_object("select_player2")->set_hidden(true);
        Gui::get().get_object("select_player1")->set_hidden(false);
    }, MouseClick);

    select_player.insert_object(select_player_title);

    select_player.insert_object(player);
    select_player.insert_object(remote_player);
    select_player.insert_object(ai_player);

    select_player.insert_object(cb_player);
    select_player.insert_object(cb_remote_player);
    select_player.insert_object(cb_ai_player);

    select_player.insert_object(btn_next);
    select_player.insert_object(btn_prev);

    return select_player;
}

GuiView select_rules_view() {

    GuiView select_rules(480, 35, 1000, 1000, "select_rules");
    select_rules.set_color(Color_White);
    select_rules.set_hidden(true);

    GuiLabel select_player_title(320, 20, "title", "SELECT RULES");
    select_player_title.set_size(60);

    GuiCheckBox rule_0(500, 300, "rule_0", "Double Threes", 30);
    rule_0.set_padding(15);
    rule_0.set_label_size(30);

    GuiCheckBox rule_1(50, 300, "rule_1", "Capture", 30);
    rule_1.set_padding(15);
    rule_1.set_label_size(30);

    GuiCheckBox rule_2(50, 350, "rule_2", "Game Ending Capture", 30);
    rule_2.set_padding(15);
    rule_2.set_label_size(30);

    GuiButton btn_next(Point(760, 900), 220, 70, "btn_next", "Start");
    btn_next.set_mouse_event([](int x, int y, int btn, void *param) {
        Gui::get().get_object("select_rules")->set_hidden(true);
        Gui::get().get_object("game")->set_hidden(false);
    }, MouseClick);

    GuiButton btn_prev(Point(20, 900), 220, 70, "btn_prev", "<< Prev");
    btn_prev.set_mouse_event([](int x, int y, int btn, void *param) {
        Gui::get().get_object("select_rules")->set_hidden(true);
        Gui::get().get_object("select_player2")->set_hidden(false);
    }, MouseClick);

    select_rules.insert_object(select_player_title);

    select_rules.insert_object(rule_0);
    select_rules.insert_object(rule_1);
    select_rules.insert_object(rule_2);

    select_rules.insert_object(btn_next);
    select_rules.insert_object(btn_prev);

    return select_rules;
}

GuiView game_view() {
    GuiView game(0, 0, 1920, 1080, "game");
    game.set_color(Color_Transparent);
    game.set_hidden(true);

    game.insert_object(GuiImage(0, 0, "goban", "assets/images/goban.xpm"));

    game.insert_object(GuiImage(300, 200, "white piece", "assets/images/white.xpm"));

    game.insert_object(GuiImage(300, 250, "black piece", "assets/images/black.xpm"));

    // game.insert_object(btn_next);
    // game.insert_object(btn_prev);

    return game;
}

int main() {
    std::cout << "start" << std::endl;
    Gui &gui = Gui::get();
    
    gui.insert_object(select_player_view1());
    gui.insert_object(select_player_view2());
    gui.insert_object(select_rules_view());
    gui.insert_object(game_view());
    
    gui.loop(1920, 1080);
}