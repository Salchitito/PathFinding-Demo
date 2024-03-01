//
// Created by Gino Daza on 20/02/2024.
//

#include "Menu.h"

Menu* Menu::instance = nullptr;  // Inicialización de la instancia a nullptr

Menu* Menu::getInstance() {
    if (!instance) {
        instance = new Menu();
    }
    return instance;
}

Menu::~Menu() {
    delete instance;
}

void Menu::init(int width, int height, const string& title) {
    font.loadFromFile(R"(../font/arial.ttf)");
    window.create(VideoMode(width,height),title,Style::Close);
}

void Menu::setMaze(Maze _maze){
    Menu::maze = _maze;
}


void Menu::show_menu() {
    window.setFramerateLimit(60);

    texts.emplace_back("Maze Size",font,28, window);
    texts.emplace_back("Rows:",font,18, window);
    texts.emplace_back("Columns:",font,18, window);
    texts.emplace_back("Dijkstra:", "Dijkstra",font,18, window);
    texts.emplace_back("Bfs:", "Bfs",font,18, window);
    texts.emplace_back("Dfs:","Dfs",font,18, window);

    buttons.emplace_back("prev","prev",font,16,window);
    buttons.emplace_back("row++","++",font,20,window);
    buttons.emplace_back("row+","+",font,20,window);
    buttons.emplace_back("row-","-",font,20,window);
    buttons.emplace_back("row--","--",font,20,window);

    buttons.emplace_back("col++","++",font,20,window);
    buttons.emplace_back("col+","+",font,20,window);
    buttons.emplace_back("col-","-",font,20,window);
    buttons.emplace_back("col--","--",font,20,window);

    buttons.emplace_back("One Path", "One Path", font, 18, window);
    buttons.emplace_back("Mul Paths", "Mul Paths", font, 18, window);

    buttons.emplace_back("Dijkstra", "Dijkstra", font, 18, window);
    buttons.emplace_back("Bfs", "Bfs", font, 18, window);
    buttons.emplace_back("Dfs", "Dfs", font, 18, window);

    buttons.emplace_back("Fast","Fast",font,18,window);
    buttons.emplace_back("Normal","Normal",font,18,window);

    while (window.isOpen()) {
        Vector2i mouse_position = Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized) {
                FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down && window.getSize().y < 900) {
                window.setSize({window.getSize().x,window.getSize().y + int(frame_size)});
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up && window.getSize().y > 300) {
                window.setSize({window.getSize().x,window.getSize().y - int(frame_size)});
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::C) {
                window.setSize({1280,720});
            }
            if(event.type == Event::MouseButtonReleased){
                button_mouse_logic_in_maze(event);
                button_mouse_logic_in_menu_maze_size(event);
                button_is_selected_logic(event);
                button_prev(event);
            }

            if(event.type == Event::MouseButtonPressed){

            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter && !(maze.ismodifing)) {
                if(type_maze == "One Path" ) thread([&] { maze.createOnePathMaze(); }).detach();
                if(type_maze == "Mul Paths" ) thread([&] { maze.createMulPathsMaze(); }).detach();
                maze.dijkstra_time = 0;
                maze.bfs_time = 0;
                maze.dfs_time = 0;
                type_algorithm = "Nothing";
                cout << "Tamaño de saves: " << maze.saves.size() << endl;
            }
        }

        for(Button& button:buttons){
            bool mouse_is_over = button.rectangle.getGlobalBounds().contains(Vector2f(mouse_position));
            if(mouse_is_over && !button.is_selected && event.type != Event::MouseButtonReleased){
                button.highlighted_color();
            }
            else {
                button.original_color();
                if(type_maze == "One Path" && button.tag == "One Path") button.selected_color();
                if(type_maze == "Mul Paths" && button.tag == "Mul Paths") button.selected_color();
                if(type_algorithm == "Dijkstra" && button.tag == "Dijkstra") button.selected_color();
                if(type_algorithm == "Bfs" && button.tag == "Bfs") button.selected_color();
                if(type_algorithm == "Dfs" && button.tag == "Dfs") button.selected_color();
                if(maze.velocity == 1000 && button.tag == "Normal") button.selected_color();
                if(maze.velocity == 999 && button.tag == "Fast") button.selected_color();

            }
        }


        window.clear(Color(60,60,60,255));


        draw_mini_menu();

        draw_maze();

        paint_last_frame();


        for(Button button:buttons){
            button.draw_all(window);
        }

        for(OnlyText &text:texts){
            // Lo comparo con su tamaño
            if(text.text.getCharacterSize() == 28) text.text.setString(to_string(maze.rows) + " " + to_string(maze.columns));
            if(text.tag == "Dijkstra") text.text.setString( "Dijkstra:  " + to_string(maze.dijkstra_time) + " milli");
            if(text.tag == "Bfs") text.text.setString( "Bfs:        " + to_string(maze.bfs_time)+ " milli");
            if(text.tag == "Dfs") text.text.setString( "Dfs:        " + to_string(maze.dfs_time) + " milli");
            window.draw(text.text);
        }


        window.display();

    }
}

void Menu::draw_maze() {
    window.draw(Text("No hay matriz", font, 20));

    if (maze.rows < maze.columns - 4) frame_size = (window.getSize().x / (maze.columns + 0.0)) * 7.75f / 10;
    else frame_size = (window.getSize().y / (maze.rows + 0.0f));

    RectangleShape frame({frame_size,frame_size});

    for (int i = 0; i < maze.rows; ++i) {
        for (int j = 0; j < maze.columns; ++j) {
            RectangleShape frame({frame_size, frame_size});
            frame.setPosition(j * frame_size, i * frame_size);
            if (maze.matrix[i][j] == 0) frame.setFillColor(Color::White);
            if (maze.matrix[i][j] == 1) frame.setFillColor(Color::Blue);
            if (maze.matrix[i][j] == 2) frame.setFillColor(Color::Yellow);
            if (maze.matrix[i][j] == 3) frame.setFillColor(Color::Green);
            if (maze.matrix[i][j] == 4) frame.setFillColor(Color::Red);
            frame.setOutlineThickness(1);
            frame.setOutlineColor(Color::Black);
            window.draw(frame);
        }
    }
}

void Menu::draw_mini_menu() {
    minimenu.setSize(Vector2f(window.getSize().x * 2.25f/10.0, window.getSize().y));
    minimenu.setPosition(Vector2f(window.getSize().x * 7.75f/10.0,0));
    minimenu.setFillColor(Color(205,195,175,255));
    minimenu.setOutlineThickness(1);
    minimenu.setOutlineColor(Color::Black);
    window.draw(minimenu);
}

void Menu::paint_last_frame() {
    RectangleShape frame({frame_size, frame_size});
    frame.setPosition((maze.columns - 1) * frame_size, (maze.rows - 1) * frame_size);
    frame.setFillColor(Color::Transparent);
    frame.setOutlineColor(Color::Magenta);
    frame.setOutlineThickness(2.5f);
    window.draw(frame);
}

void Menu::button_mouse_logic_in_maze(Event &event) {
    int maze_width = frame_size * maze.columns;
    int maze_height = frame_size * maze.rows;
    if(Mouse::getPosition(window).x < maze_width && Mouse::getPosition(window).y < maze_height){
        int mouse_maze_position_row = Mouse::getPosition(window).y / frame_size;
        int mouse_maze_position_col = Mouse::getPosition(window).x / frame_size;
        for (int i = 0; i < maze.rows; ++i) {
            for (int j = 0; j < maze.columns; ++j) {
                if(event.mouseButton.button == Mouse::Left){
                    if(maze.matrix[i][j] == 3) maze.matrix[i][j] = 0;
                    maze.matrix[mouse_maze_position_row][mouse_maze_position_col] = 3;
                    maze.entrance = {mouse_maze_position_row,mouse_maze_position_col};
                }
                if(event.mouseButton.button == Mouse::Right){
                    if(maze.matrix[i][j] == 4) maze.matrix[i][j] = 0;
                    maze.matrix[mouse_maze_position_row][mouse_maze_position_col] = 4;
                    maze.exit = {mouse_maze_position_row,mouse_maze_position_col};
                }
            }
        }
        if(event.mouseButton.button == Mouse::Middle){
            maze.matrix[mouse_maze_position_row][mouse_maze_position_col] = 1;
        }
    }
}

void Menu::button_mouse_logic_in_menu_maze_size(sf::Event &event) {
    Vector2i mouse_position = Mouse::getPosition(window);
    for (const Button &button:buttons) {
        if(button.rectangle.getGlobalBounds().contains(Vector2f(mouse_position))){
            if(button.tag == "row+" && maze.rows < 1000) {
                maze.rows++;
                maze.addRows(1);
            }
            if(button.tag == "row-" && maze.rows > 1) {
                maze.rows--;
                maze.removeRows(1);
            }
            if(button.tag == "col+" && maze.columns < 1000) {
                maze.columns++;
                maze.addColums(1);
            }
            if(button.tag == "col-" && maze.columns > 1) {
                maze.columns--;
                maze.removeColumns(1);
            }

            if(button.tag == "row++" && maze.rows < 1000) {
                maze.rows += 5;
                maze.addRows(5);
            }
            if(button.tag == "row--" && maze.rows > 1 + 5) {
                maze.rows -= 5;
                maze.removeRows(5);
            }
            if(button.tag == "col++" && maze.columns < 1000) {
                maze.columns += 5;
                maze.addColums(5);
            }
            if(button.tag == "col--" && maze.columns > 1 + 5) {
                maze.columns -= 5;
                maze.removeColumns(5);
            }
        }
    }
}

void Menu::button_is_selected_logic(sf::Event &event) {
    Vector2i mouse_position = Mouse::getPosition(window);
    for (Button& button:buttons) {
        if(button.rectangle.getGlobalBounds().contains(Vector2f(mouse_position))){
            if(button.text.getString() == "One Path"){
                type_maze = "One Path";
            }
            if(button.text.getString() == "Mul Paths"){
                type_maze = "Mul Paths";
            }
            if(button.text.getString() == "Normal"){
                maze.velocity = 1000;
            }
            if(button.text.getString() == "Fast"){
                maze.velocity = 999;
            }
            if((button.text.getString() == "Dijkstra" || button.text.getString() == "Bfs" || button.text.getString() == "Dfs") && !maze.ismodifing){
                for (int i = 0; i < maze.rows; ++i) {
                    for (int j = 0; j < maze.columns; ++j) {
                        if(maze.matrix[i][j] == 2) maze.matrix[i][j] = 0;
                    }
                }
                for(OnlyText &text:texts){
                    if(button.text.getString() == "Dijkstra" ){
                        type_algorithm = "Dijkstra";
                        thread([&] { maze.apply_dijkstra(); }).detach();

                    }
                    if(button.text.getString() == "Bfs"){
                        type_algorithm = "Bfs";
                        thread([&] { maze.apply_bfs(); }).detach();

                    }
                    if(button.text.getString() == "Dfs"){
                        type_algorithm = "Dfs";
                        thread([&] { maze.apply_dfs(); }).detach();

                    }
                }
            }
        }
    }
}

void Menu::button_prev(sf::Event &event) {
    Vector2i mouse_position = Mouse::getPosition(window);
    for (Button& button:buttons) {
        if(button.rectangle.getGlobalBounds().contains(Vector2f(mouse_position))){
            if(button.text.getString() == "prev") {
                maze.load_maze();
            }
        }
    }
}
