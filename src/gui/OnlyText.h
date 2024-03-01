//
// Created by Gino Daza on 21/02/2024.
//

#ifndef PATHFINDING_DEMO_ONLYTEXT_H
#define PATHFINDING_DEMO_ONLYTEXT_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// Esta clase es personalizada, esta hecha especificamente para el menu
// Me refiero a los if

class OnlyText{
    friend class Menu;
private:
    Text text;
    string tag;
    OnlyText() = default;
public:
    OnlyText(const string& _text, const Font& font, int characterSize,const RenderWindow &window){
        text.setString(_text);
        text.setFont(font);
        text.setCharacterSize(characterSize);
        text.setColor(Color::Black);
        if(_text == "Maze Size") text.setPosition(window.getSize().x * 8.60f/10,window.getSize().y * 0.25f/10);
        if(_text == "Rows:") text.setPosition(window.getSize().x * 8.0f/10,window.getSize().y * 1.0f/10);
        if(_text == "Columns:") text.setPosition(window.getSize().x * 8.0f/10,window.getSize().y * 1.5f/10);
    }

    OnlyText(const string& _text, const string &_tag, const Font& font, int characterSize,const RenderWindow &window){
        tag = _tag;
        text.setString(_text);
        text.setFont(font);
        text.setCharacterSize(characterSize);
        text.setColor(Color::Black);
        if(_text == "Dijkstra:") text.setPosition(window.getSize().x * 8.0f/10,window.getSize().y * 4.0f/10);
        if(_text == "Bfs:") text.setPosition(window.getSize().x * 8.0f/10,window.getSize().y * 4.5f/10);
        if(_text == "Dfs:") text.setPosition(window.getSize().x * 8.0f/10,window.getSize().y * 5.0f/10);
    }

};

#endif //PATHFINDING_DEMO_ONLYTEXT_H
