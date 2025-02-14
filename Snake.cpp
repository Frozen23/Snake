//
// Created by kubam on 04.05.2023.
//

#include "Snake.h"
#include <fstream>
#include "Menu.h"

using namespace std;
using namespace sf;

Snake::Snake(RenderWindow &window, GameMode mode) : mWindow(window)
{
    switch (mode) {
        case EASY:
            mTimeToUpdate = 250;
            break;
        case NORMAL:
            mTimeToUpdate = 100;
            break;
        case HARD:
            mTimeToUpdate = 50;
            break;
    }
    mSize=32;
    mCurrentTime = 0.0f;
    left = up = down = false;
    right = true;
    AddCase();
    AddCase();
    food.setRadius(mSize / 2);
    food.setFillColor(sf::Color::Red);
    AddFood();
    if (!font.loadFromFile("Font2.ttf")) {
        return;
    }

}

void Snake::AddFood()
{
    int randomX = rand() % (mWindow.getSize().x / mSize);
    int randomY = rand() % (mWindow.getSize().y / mSize);

    for(unsigned int i = 0; i < Snakes.size(); i++)
    {
        if((Snakes[0].getPosition().x != randomX * mSize) && (Snakes[0].getPosition().y != randomY))
        {
            food.setPosition(randomX * mSize, randomY * mSize);
        }
    }
}

void Snake::AddCase()
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(32, 32));
    rect.setOutlineColor(sf::Color::Red);
    if (Snakes.empty())
    {
        rect.setFillColor(sf::Color(0,130,0));
        rect.setPosition(320, 256);

    }
    else
    {
        rect.setFillColor(sf::Color(0,130,0));
        rect.setPosition(Snakes[Snakes.size() - 1].getPosition().x - rect.getSize().x, Snakes[Snakes.size() - 1].getPosition().y);
    }

    Snakes.push_back(rect);
}

void Snake::Move()
{
    if(getState()==true) {
        if (mCurrentTime < mTimeToUpdate) {
            mCurrentTime += mClock.restart().asMilliseconds();
        } else {
            mCurrentTime = 0.0f;
            if (Snakes.size() > 1) {
                for (int i = Snakes.size() - 1; i > 0; i--) {
                    Snakes[i].setPosition(
                            sf::Vector2f(Snakes[i - 1].getPosition().x, Snakes[i - 1].getPosition().y));
                }
            }

            if (left) {
                Snakes[0].move(-mSize, 0);
            }

            if (right) {
                Snakes[0].move(mSize, 0);
            }

            if (up) {
                Snakes[0].move(0, -mSize);
            }

            if (down) {
                Snakes[0].move(0, mSize);
            }
            CheckCollision();
        }
    }
}

void Snake::CheckCollision()
{
    for ( int i = 2; i < Snakes.size(); i++) // Snake's boxes
    {
        if (Snakes[0].getPosition().x == Snakes[i].getPosition().x
            && Snakes[0].getPosition().y == Snakes[i].getPosition().y)
        {
            getScore();
            writeScore();
            GameEnd=false;
        }
    }

    if (Snakes[0].getPosition().x < 0 || Snakes[0].getPosition().x + Snakes[0].getSize().x > mWindow.getSize().x // Window collision
        || Snakes[0].getPosition().y < 0 || Snakes[0].getPosition().y + Snakes[0].getSize().y > mWindow.getSize().y)
    {
        getScore();
        writeScore();
        GameEnd=false;
    }

    if (Snakes[0].getPosition().x == food.getPosition().x // Food collision
        && Snakes[0].getPosition().y == food.getPosition().y)
    {
        score+=1;
        AddCase();
        AddFood();
        AddFood();

    }
}

void Snake::Update(Event &event) // Check key input
{
        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Left) {
                if (getState() == true) {
                    if (Snakes[0].getPosition().x - Snakes[0].getSize().x != Snakes[1].getPosition().x) {
                        if (!left && !right)//jesli nie ma lewej i prawej to lewa lub prawa
                        {
                            left = true;
                            right = false;
                            up = false;
                            down = false;
                        }
                    }
                }
            }
            if (event.key.code == sf::Keyboard::Right) {
                if (getState() == true) {
                    if (Snakes[0].getPosition().x + Snakes[0].getSize().x != Snakes[1].getPosition().x) {
                        if (!right && !left) {
                            left = false;
                            right = true;
                            up = false;
                            down = false;
                        }
                    }
                }
            }

            if (event.key.code == sf::Keyboard::Up) {
                if (getState() == true) {
                    if (Snakes[0].getPosition().y - Snakes[0].getSize().x != Snakes[1].getPosition().y) {
                        if (!up && !down)//jesli nie gora i dol to gora lub dol
                        {
                            left = false;
                            right = false;
                            up = true;
                            down = false;
                        }
                    }
                }
            }
            if (event.key.code == sf::Keyboard::Down) {
                if (getState() == true) {
                    if (Snakes[0].getPosition().y + Snakes[0].getSize().x != Snakes[1].getPosition().y) {
                        if (!up && !down) {
                            left = false;
                            right = false;
                            up = false;
                            down = true;
                        }
                    }
                }
            }
        }
        if (getState() == false) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (textend.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    mWindow.close();
                    Menu menu;
                    menu.ShowMenu();
                }
            }
        }
    }


void Snake::Draw()
{
    sf::Texture jungle;
    sf::Texture skin;
    if (!jungle.loadFromFile("jungle.jpg")) {
        return;
    };
    if (!skin.loadFromFile("Skin.jpg")) {
        return;
    };

    sf::Sprite Jungle;
    Jungle.setTexture(jungle);
    mWindow.draw(Jungle);
    mWindow.draw(food);
    for ( int i = 0; i < Snakes.size(); i++) {
        Snakes[i].setTexture(&skin);
        mWindow.draw(Snakes[i]);
    }
    string str=to_string(score);
    sf::Text text("Score" + str,font, 20);
    text.setPosition(700,5);
    text.setFillColor(sf::Color::Black);
    mWindow.draw(text);
    //textury

    if(getState()==false){
        sf::RectangleShape rect(sf::Vector2f(text.getGlobalBounds().width+10, text.getGlobalBounds().height+10));
        rect.setPosition(text.getPosition());
        rect.setFillColor(sf::Color::Transparent);
        mWindow.draw(rect);
        sf::Text text2("You Lost" ,font, 60);
        sf::Text text3("Your Score "+str ,font, 60);
        sf::Text text4("Back to main menu" ,font, 60);
        text2.setPosition(200,30);
        text3.setPosition(130,100);
        text4.setPosition(40,500);
        textend=text4;
        text2.setFillColor(sf::Color::Black);
        text3.setFillColor(sf::Color::Black);
        text4.setFillColor(sf::Color::Black);
        mWindow.draw(text);
        mWindow.draw(text2);
        mWindow.draw(text3);
        mWindow.draw(text4);
    }

}
int Snake::getScore() {
    return score;
}
void Snake::writeScore() {
    std::ofstream file("score.txt", std::ios_base::app);
    if (file.is_open())
    {
        file <<getScore() << std::endl;
        file.close();
    }
    else
    {
        std::cout << "Error opening file" << std::endl;
    }
}
int Snake::getState() {
    return GameEnd;
}

