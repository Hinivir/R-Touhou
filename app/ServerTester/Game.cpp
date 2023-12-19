/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

//compilation => g++ Game.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/Graphics.hpp>
#include <iostream>

void handleCollisions(sf::RectangleShape& movingSquare, const sf::RectangleShape& stationarySquare, float speed) {
    sf::FloatRect movingRect = movingSquare.getGlobalBounds();
    sf::FloatRect stationaryRect = stationarySquare.getGlobalBounds();

    if (movingRect.intersects(stationaryRect)) {
        if (speed > 0) {
            movingSquare.setPosition(stationaryRect.left - movingRect.width, movingRect.top);
        } else {
            movingSquare.setPosition(stationaryRect.left + stationaryRect.width, movingRect.top);
        }
    }
}

void drawBlinkingZone(sf::RenderWindow& window, sf::RectangleShape& blinkingZone, bool& isVisible) {
    if (isVisible) {
        window.draw(blinkingZone);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML Game");

    sf::RectangleShape square1(sf::Vector2f(50, 50));
    sf::RectangleShape square2(sf::Vector2f(50, 50));
    sf::RectangleShape blinkingZone(sf::Vector2f(200, 200));
    blinkingZone.setFillColor(sf::Color(128, 0, 128));
    blinkingZone.setPosition(500, 300);

    square1.setFillColor(sf::Color::Red);
    square2.setFillColor(sf::Color::Green);
    square1.setPosition(100, 100);
    square2.setPosition(100, 300);

    float speed = 0.5f;
    bool isVisible = true;

    sf::Clock clock;
    sf::Time elapsed;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() > 500) {
            isVisible = !isVisible;
            clock.restart();
        }

        handleCollisions(square1, square2, speed);

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

        handleCollisions(square2, square1, speed);

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

//        if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Z)
            std::cout << "UP" << std::endl;
        else if (event.key.code == sf::Keyboard::S)
            std::cout << "DOWN" << std::endl;
        else if (event.key.code == sf::Keyboard::Q)
            std::cout << "LEFT" << std::endl;
        else if (event.key.code == sf::Keyboard::D)
            std::cout << "RIGHT" << std::endl;
        else if (event.key.code == sf::Keyboard::Space)
            std::cout << "ACTION" << std::endl;
        else if (event.key.code == sf::Keyboard::Escape)
            std::cout << "QUIT" << std::endl;
            window.close();
//        }

        window.clear();

        // Dessiner la zone violette clignotante
        drawBlinkingZone(window, blinkingZone, isVisible);

        window.draw(square1);
        window.draw(square2);
        window.display();
    }
    return 0;
}
