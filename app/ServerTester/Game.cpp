/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

//compilation => g++ Game.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML Game");

    sf::RectangleShape square1(sf::Vector2f(50, 50));
    sf::RectangleShape square2(sf::Vector2f(50, 50));
    square1.setFillColor(sf::Color::Red);
    square2.setFillColor(sf::Color::Red);
    square1.setPosition(100, 100);
    square2.setPosition(100, 300);

    float speed = 0.5f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            square1.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            square1.move(speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            square1.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            square1.move(0, speed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            square2.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            square2.move(speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            square2.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            square2.move(0, speed);
        }

        window.clear();
        window.draw(square1);
        window.draw(square2);
        window.display();
    }

    return 0;
}
