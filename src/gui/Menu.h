//
// Created by Gino Daza on 20/02/2024.
//

#ifndef PATHFINDING_DEMO_MENU_H
#define PATHFINDING_DEMO_MENU_H

#include "../maze/Maze.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "OnlyText.h"

using namespace sf;
using namespace std;

class Menu {
    friend class Maze;

private:
    // Patron de diseño 1: Singleton
    static Menu *instance;

    Maze maze;
    Font font;
    RenderWindow window;
    float frame_size;

    RectangleShape minimenu;
    vector<Button> buttons;
    vector<OnlyText> texts;

    // Estas variables le diran al menu que tipo
    // de laberinto crear al pulsar espacio

    string type_maze = "One Path";
    string type_algorithm = "Nothing";

    Menu() = default;

    void draw_maze();

    void draw_mini_menu();

    void paint_last_frame();

    void button_mouse_logic_in_maze(Event &event);

    void button_mouse_logic_in_menu_maze_size(Event &event);

    void button_is_selected_logic(Event &event);

    void button_prev(Event &event);

public:

    // Patron de diseño 1: Singleton

    static Menu* getInstance();

    void init(int width, int height, const string &title);

    ~Menu();

    // Evita copia y asignacion
    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;


    void setMaze(Maze maze);

    void show_menu();



};


#endif //PATHFINDING_DEMO_MENU_H
