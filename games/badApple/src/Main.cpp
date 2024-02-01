/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Main.cpp
*/

#include "Registry.hpp"
#include "Systems.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <fstream>
#include <iostream>

static const sf::Color ColorDarkGray(85, 85, 85);
static const sf::Color ColorLightGray(170, 170, 170);
static const sf::Color ColorWhite(255, 255, 255);

static void systemDrawBadAppleFromAscii(GameEngine::Registry &REGISTRY_DEFAULT_NAME, sf::RenderWindow &window, std::string const &frame)
{
    sf::RectangleShape pixel;
    sf::Vector2f size(WINDOW_WIDTH_FLOAT / 79, WINDOW_HEIGHT_FLOAT / 31);
    sf::Vector2f position(0, 0);
    std::size_t i = 0;
    std::size_t length = frame.size();
    char c;
    bool step = 0;
    bool isShowed;
    std::size_t count = 0;

    pixel.setSize(size);
    for (i = 0; i < length; i++) {
        c = frame[i];
        if (step == 0) {
            step = 1;
            isShowed = true;
            if (c == 'D')
                pixel.setFillColor(ColorWhite);
            else if (c == 'C')
                pixel.setFillColor(ColorLightGray);
            else if (c == 'B')
                pixel.setFillColor(ColorDarkGray);
            else if (c == 'A')
                isShowed = false;
            else
                return;
        } else if (step == 1) {
            step = 0;
            if (c != '!') {
                if ((i + 3) < length) {
                    count = (frame[i] - '0') * 1000 + (frame[i + 1] - '0') * 100 + (frame[i + 2] - '0') * 10 + (frame[i + 3] - '0');
                    i += 3;
                } else {
                    return;
                }
            } else {
                count = 1;
            }
            for (std::size_t _i = 0; _i < count; _i++) {
                if (isShowed) {
                    pixel.setPosition(position.x * size.x, position.y * size.y);
                    window.draw(pixel);
                }
                position.x += 1;
                if (position.x >= 79) {
                    position.x = 0;
                    position.y += 1;
                }
            }
        }
    }
}

int main(void)
{
    // Initialisation
    int nbRegistry = 1024;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bad Apple");
    sf::Music music;
    std::ifstream file("badApple/res/BA.txt");
    std::string frame;
    window.setFramerateLimit(30);
    GameEngine::Registry registry(nbRegistry);
    GameEngine::SystemGroup system;
    // Registering components
    // Music
    if (music.openFromFile("badApple/res/BA.wav"))
        music.play();
    else
        std::cerr << "Coudln't load \"badApple/res/BA.wav\"" << std::endl;
    // Main Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        // Draw
        if (file.is_open()) {
            if (std::getline(file, frame))
                systemDrawBadAppleFromAscii(registry, window, frame);
            else
                file.close();
        }
        // Displaying SFML window, then clearing it
        window.display();
        window.clear();
    }
    if (file.is_open())
        file.close();
    return 0;
}
