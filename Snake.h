//
// Created by kubam on 04.05.2023.
//

#ifndef NEWSNAKE_SNAKE_H
#define NEWSNAKE_SNAKE_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
enum GameMode {EASY, NORMAL, HARD };
class Snake
{
public:
    Snake(sf::RenderWindow &window, GameMode mode);
    void Move();
    void Update(sf::Event &event);
    void Draw();
    int getScore();
    void writeScore();
    int getState();
    sf::Font font;
    int score=0;
    sf::RectangleShape shp;
    bool GameEnd=true;
    sf::Text textend;
private:
    sf::RenderWindow &mWindow;
    sf::Clock mClock;
    sf::CircleShape food;
    int mTimeToUpdate;
    int mSize;
    bool left, right, up, down;
    float mCurrentTime;
    std::vector<sf::RectangleShape> Snakes;
    void CheckCollision();
    void AddCase();
    void AddFood();
};



#endif //NEWSNAKE_SNAKE_H
