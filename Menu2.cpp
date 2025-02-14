//
// Created by kubam on 06.05.2023.
//
#include "SFML/Graphics.hpp"
#include "Menu2.h"
#include "board.h"
using namespace sf;
Menu2::Menu2(RenderWindow &window) : menuWindow(window){}
void Menu2::ShowMenu2() {
//    sf::RenderWindow menuWindow(sf::VideoMode(800, 640), "Snake Main Menu");
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(800,640));
    background.setPosition(0,0);
    background.setFillColor(sf::Color(0,130,0));
    sf::Font font;
    font.loadFromFile("Font2.ttf");
    sf::Text Gamemode("Choose gamemode", font, 50);
    Gamemode.setPosition(120, 80);
    sf::Text Easy("Easy", font, 50);
    Easy.setPosition(300, 200);
    sf::Text Normal("Normal", font, 50);
    Normal.setPosition(270, 300);
    sf::Text Hard("Hard", font, 50);
    Hard.setPosition(300, 400);

    menuWindow.clear();
    menuWindow.draw(background);
    menuWindow.draw(Gamemode);
    menuWindow.draw(Easy);
    menuWindow.draw(Normal);
    menuWindow.draw(Hard);
    menuWindow.display();


    bool isMenuOpen = true;
    while (isMenuOpen) {
        sf::Event event;
        while (menuWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                menuWindow.close();
                isMenuOpen = false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (Easy.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    menuWindow.close();
                    isMenuOpen = false;
                    board Board;
                    Board.ShowSnake(0);


                }
                if (Normal.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    menuWindow.close();
                    isMenuOpen = false;
                    board Board;
                    Board.ShowSnake(1);

                }
                if (Hard.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    menuWindow.close();
                    isMenuOpen = false;
                    board Board;
                    Board.ShowSnake(2);

                }
            }
        }
    }

}

