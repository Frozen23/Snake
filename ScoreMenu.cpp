//
// Created by kubam on 07.05.2023.
//
#include "SFML/Graphics.hpp"
#include "ScoreMenu.h"
#include <iostream>
using namespace std;
ScoreMenu::ScoreMenu(sf::RenderWindow &window) : menuWindow(window){}
void ScoreMenu::ShowHighScores() {
    menu.ShowScores();
    sf::Font font;
    font.loadFromFile("Font2.ttf");
    sf::Text playOption("Best Scores", font, 50);
    playOption.setFillColor(sf::Color::Red);
    playOption.setPosition(0, 0);
    sf::Text Back("Back to menu", font, 50);
    Back.setFillColor(sf::Color::Red);
    Back.setPosition(350, 500);


    menuWindow.clear();
    menuWindow.draw(playOption);
    menuWindow.draw(Back);

    for(int i=1;i<11;i++){
        string a= to_string(menu.scores[i-1]);
        string b= to_string(i);
        sf::Text score2(b+".",font,50);
        score2.setPosition(20,40+(50*i));
        score2.setFillColor(sf::Color::Red);
        menuWindow.draw(score2);
        if(i==10){
            sf::Text score1(a,font,50);
            score1.setPosition(115,40+(50*i));
            menuWindow.draw(score1);

        }else{
            sf::Text score1(a,font,50);
            score1.setPosition(100,40+(50*i));
            menuWindow.draw(score1);
        }
    }

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
                    menuWindow.close();
                    isMenuOpen = false;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (Back.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    menuWindow.close();
                    Menu menu1;
                    menu1.ShowMenu();
                    isMenuOpen =false;
                }
            }
        }
    }
}
