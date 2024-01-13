/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** gameExampleParallax.cpp
*/

#include <SFML/Graphics.hpp>

int main(void) {

    float widthWindow = 1920;
    float heightWindow = 1080;

    sf::RenderWindow window(sf::VideoMode(widthWindow, heightWindow), "Parallax Background");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("TestParallaxExample/Star.jpg")) {
        return -1;
    }

    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("TestParallaxExample/Ground.png")) {
        return -1;
    }

    sf::Sprite backgroundStatic1(backgroundTexture);
    sf::Sprite backgroundStatic2(backgroundTexture);

    sf::Sprite ground_low(groundTexture);
    sf::Sprite ground_up(groundTexture);

    backgroundStatic1.setPosition(0, 0);
    backgroundStatic2.setPosition(-widthWindow, 0);

    ground_low.setPosition(0, 0);
    ground_up.setPosition(0, heightWindow - 50);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        backgroundStatic1.move(-1.0f, 0);
        backgroundStatic2.move(-1.0f, 0);

        if (backgroundStatic1.getPosition().x < -widthWindow) {
            backgroundStatic1.setPosition(widthWindow, 0);
        }

        if (backgroundStatic2.getPosition().x < -widthWindow) {
            backgroundStatic2.setPosition(widthWindow, 0);
        }

        window.clear();

        window.draw(backgroundStatic1);
        window.draw(backgroundStatic2);
        window.draw(ground_low);
        window.draw(ground_up);

        window.display();
    }

    return 0;
}
