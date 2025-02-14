//
// Created by kubam on 07.05.2023.
//

#ifndef NEWSNAKE_SCOREMENU_H
#define NEWSNAKE_SCOREMENU_H
#include "Menu.h"
#include "SFML/Graphics.hpp"

class ScoreMenu {
public:
    ScoreMenu(sf::RenderWindow &window);
    Menu menu;
    void ShowHighScores();
private:
    sf::RenderWindow &menuWindow;

};


#endif //NEWSNAKE_SCOREMENU_H
