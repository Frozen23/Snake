//
// Created by kubam on 06.05.2023.
//
#include <vector>
#include "string"
#include "SFML/Graphics.hpp"
#ifndef NEWSNAKE_MENU_H
#define NEWSNAKE_MENU_H


class Menu {
public:
    void ShowMenu();
    std::vector<int> ShowScores();
    std::vector<int>scores;
};


#endif //NEWSNAKE_MENU_H
