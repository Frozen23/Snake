//
// Created by kubam on 05.05.2023.
//

#include "board.h"

void board::ShowSnake(int choose) {
    sf::RenderWindow window(sf::VideoMode(800, 640), "Snake");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    Snake snake(window, static_cast<GameMode>(choose));
    while (window.isOpen())
    {
        snake.Move();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            snake.Update(event);
        }
        window.clear(sf::Color(0,0,0));
        snake.Draw();
        window.display();
    }
    }