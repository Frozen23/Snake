//
// Created by kubam on 06.05.2023.
//
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Menu2.h"
#include <fstream>
#include <algorithm>
#include "ScoreMenu.h"
using namespace sf;
void Menu::ShowMenu() {
    sf::RenderWindow menuWindow(sf::VideoMode(800, 640), "Snake Main Menu");
    menuWindow.setFramerateLimit(120);
    sf::Font font;
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(800,640));
    background.setPosition(0,0);
    background.setFillColor(sf::Color(0,130,0));
    font.loadFromFile("Font2.ttf");
    sf::Text title("Snake the game",font,60);
    title.setPosition(90,30);
    title.setFillColor(sf::Color::White);
    sf::Text playOption("Play", font, 50);
    playOption.setPosition(150,180);
    sf::Text bestScores("Best scores", font, 50);
    bestScores.setPosition(40, 280);
    sf::Text quitOption("Quit", font, 50);
    quitOption.setPosition(150, 380);

    sf::Texture Snake;
    if (!Snake.loadFromFile("Snake.png")) {
        return;
    };
    sf::Sprite snake;
    snake.setTexture(Snake);
    snake.setScale(0.6,0.6);
    snake.setPosition(500,200);



    menuWindow.clear();
    menuWindow.draw(background);
    menuWindow.draw(snake);
    menuWindow.draw(title);
    menuWindow.draw(playOption);
    menuWindow.draw(bestScores);
    menuWindow.draw(quitOption);
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
                if (playOption.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//                    menuWindow.close();
//                    isMenuOpen = false;
                    Menu2 menu2(menuWindow);//referencja do okna nowa
                    menu2.ShowMenu2();
                    isMenuOpen= false;
                }
                if (bestScores.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
//                    menuWindow.close();
//                    isMenuOpen = false;
                    ScoreMenu scoreMenu(menuWindow);
                    scoreMenu.ShowHighScores();
                    isMenuOpen=false;
                }
                if (quitOption.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    menuWindow.close();
                    isMenuOpen = false;
                }

            }
        }
    }
}
std::vector<int> Menu::ShowScores() {
    std::ifstream file("Score.txt");
    int z;
    while (!file.eof()){
        while(file>>z) {
            scores.push_back(z);
        }
    }
        file.close();
    std::sort(scores.begin(), scores.end(),std::greater<int>());
    return scores;
    }


