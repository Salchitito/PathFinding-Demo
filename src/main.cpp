
#include "gui/Menu.h"

using namespace std;
using namespace sf;

int main() {
    int rows = 27;
    int columns = 30;

    srand(time(NULL));

    Maze maze(rows,columns);
    maze.setVelocity(1000);

    Menu* menu = Menu::getInstance();
    menu->init(1280,720,"PathFinding Demo");
    menu->setMaze(maze);
    menu->show_menu();

    return 0;
}
