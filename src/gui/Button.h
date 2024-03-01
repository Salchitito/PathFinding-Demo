//
// Created by Gino Daza on 21/02/2024.
//

#ifndef PATHFINDING_DEMO_BUTTON_H
#define PATHFINDING_DEMO_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Button{
    friend class Menu;
private:
    string tag;
    RectangleShape rectangle;
    Text text;
    bool is_selected;
    Button() = default;
public:
    Button(const string &_tag,const string& _text, const Font& font, int characterSize, const RenderWindow& window){
        tag = _tag;
        rectangle.setFillColor(Color(220,210,190,255));
        rectangle.setOutlineThickness(1);
        rectangle.setOutlineColor(Color::Black);

        buttons_maze_size_aux(_text,window);
        type_maze_aux(_text,window);
        velocity_buttons_aux(_text,window);
        type_algorithm_aux(_text, window);
        buttons_prev_next(_text,window);

        text.setString(_text);
        text.setFont(font);
        text.setCharacterSize(characterSize);
        text.setFillColor(Color::Black);
    }

    // Crea los botones para cambiar filas y columnas

    void buttons_prev_next(const string& _text, const RenderWindow& window){
        if(_text == "prev"){
            rectangle.setSize({window.getSize().x / 25.0f,window.getSize().x / 50.0f});
            rectangle.setPosition(window.getSize().x * 8.0f/10, window.getSize().y * 0.35f/10);

            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 6.0f, rectangle.getPosition().y);

        }
    }

    void buttons_maze_size_aux(const string& _text, const RenderWindow& window){
        if(_text == "+" || _text == "-" || _text == "++" || _text == "--"){
            rectangle.setSize({window.getSize().x / 50.0f,window.getSize().x / 50.0f});
            if(tag == "row++") rectangle.setPosition(window.getSize().x * 9.5f/10, window.getSize().y * 1.0f/10);
            if(tag == "row+") rectangle.setPosition(window.getSize().x * 9.25f/10, window.getSize().y * 1.0f/10);
            if(tag == "row-") rectangle.setPosition(window.getSize().x * 9.0f/10, window.getSize().y * 1.0f/10);
            if(tag == "row--") rectangle.setPosition(window.getSize().x * 8.75f/10, window.getSize().y * 1.0f/10);
            if(tag == "col++") rectangle.setPosition(window.getSize().x * 9.5f/10, window.getSize().y * 1.5f/10);
            if(tag == "col+") rectangle.setPosition(window.getSize().x * 9.25f/10, window.getSize().y * 1.5f/10);
            if(tag == "col-") rectangle.setPosition(window.getSize().x * 9.0f/10, window.getSize().y * 1.5f/10);
            if(tag == "col--") rectangle.setPosition(window.getSize().x * 8.75f/10, window.getSize().y * 1.5f/10);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 3.75f, rectangle.getPosition().y);
            if(_text == "++") text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 10.0f, rectangle.getPosition().y);
            if(_text == "-") text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.5f, rectangle.getPosition().y);
            if(_text == "--") text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 4.25f, rectangle.getPosition().y);
        }
    }

    // Crea los botones de cambio de velocidad

    void type_maze_aux(const string& _text, const RenderWindow& window){
        if(_text == "One Path"){
            rectangle.setSize({window.getSize().x / 12.5f, window.getSize().y / 16.0f});
            rectangle.setPosition(window.getSize().x * 8.0f/10, window.getSize().y * 2.25f/10);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 7.5f, rectangle.getPosition().y + rectangle.getSize().y / 5.0f);
        }
        if(_text == "Mul Paths"){
            rectangle.setSize({window.getSize().x / 12.5f, window.getSize().y / 16.0f});
            rectangle.setPosition(window.getSize().x * 8.9f/10, window.getSize().y * 2.25f/10);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 7.75f, rectangle.getPosition().y + rectangle.getSize().y / 5.0f);
        }

    }

    void type_algorithm_aux(const string& _text, const RenderWindow& window){
        if(_text == "Dijkstra"){
            rectangle.setSize({window.getSize().x / 16.0f, window.getSize().y / 16.0f});
            rectangle.setPosition(window.getSize().x * 7.9f/10, window.getSize().y * 3.1f/10);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 8.0f, rectangle.getPosition().y + rectangle.getSize().y / 5.0f);
        }
        if(_text == "Bfs"){
            rectangle.setSize({window.getSize().x / 16.0f, window.getSize().y / 16.0f});
            rectangle.setPosition(window.getSize().x * 8.60f/10, window.getSize().y * 3.1f/10);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 3.24f, rectangle.getPosition().y + rectangle.getSize().y / 5.0f);
        }
        if(_text == "Dfs"){
            rectangle.setSize({window.getSize().x / 16.0f, window.getSize().y / 16.0f});
            rectangle.setPosition(window.getSize().x * 9.30f/10, window.getSize().y * 3.1f/10);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 3.24f, rectangle.getPosition().y + rectangle.getSize().y / 5.0f);
        }
    }

    void velocity_buttons_aux(const string& _text, const RenderWindow& window){
        if(_text == "Fast"){
            rectangle.setSize({window.getSize().x / 12.5f, window.getSize().y / 16.0f});
            rectangle.setPosition(window.getSize().x * 9.0f/10, window.getSize().y * 8.5f/10);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 3.25f, rectangle.getPosition().y + rectangle.getSize().y / 5.0f);
        }
        if(_text == "Normal"){
            rectangle.setSize({window.getSize().x / 12.5f, window.getSize().y / 16.0f});
            rectangle.setPosition(window.getSize().x * 8.0f/10, window.getSize().y * 8.5f/10);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 4.5f, rectangle.getPosition().y + rectangle.getSize().y / 5.0f);
        }
    }

    // Resalta el boton

    void highlighted_color(){
        rectangle.setFillColor(Color(235,225,205,255));
        text.setFillColor(Color(20,20,20,255));
    }

    // Color original

    void original_color(){
        is_selected = false;
        rectangle.setFillColor(Color(220,210,190,255));
        text.setFillColor(Color::Black);
    }

    // Color cuando el boton esta seleccionado

    void selected_color(){
        is_selected = true;
        rectangle.setFillColor(Color::Black);
        text.setFillColor(Color::White);
    }


    // Dibuja todo el contenido del boton

    void draw_all(RenderWindow &window){
        window.draw(rectangle);
        window.draw(text);
    }
};

#endif //PATHFINDING_DEMO_BUTTON_H
