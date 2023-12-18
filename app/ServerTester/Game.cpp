/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Game");

    sf::RectangleShape square1(sf::Vector2f(50, 50));
    sf::RectangleShape square2(sf::Vector2f(50, 50));

    square1.setFillColor(sf::Color::Red);
    square2.setFillColor(sf::Color::Red);

    square1.setPosition(100, 100);
    square2.setPosition(300, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(square1);
        window.draw(square2);
        window.display();
    }

    return 0;
}
