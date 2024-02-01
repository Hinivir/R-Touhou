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

static void systemDrawBadAppleFromAscii(GameEngine::Registry &REGISTRY_DEFAULT_NAME, sf::RenderWindow &window, std::size_t const frame)
{
    std::string str;
    std::ifstream file("badApple/res/BA" + std::to_string(frame) + ".txt");
    sf::RectangleShape pixel;
    sf::Vector2f size(WINDOW_WIDTH_FLOAT / 79, WINDOW_HEIGHT_FLOAT / 31);
    sf::Vector2f position(0, 0);

    pixel.setSize(size);
    pixel.setFillColor(sf::Color::White);
    if (file.is_open()) {
        while (std::getline(file, str)) {
            position.x = -1;
            for (auto const c: str) {
                position.x += 1;
                if (!('0' <= c && c <= '9') && !('A' <= c && c <= 'Z') && c != '@')
                    continue;
                pixel.setPosition(position.x * size.x, position.y * size.y);
                window.draw(pixel);
            }
            position.y += 1;
        }
        file.close();
    }
}

int main(void)
{
    // Initialisation
    int nbRegistry = 1024;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bad Apple");
    sf::Music music;
    std::size_t frame = 0;
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
        systemDrawBadAppleFromAscii(registry, window, frame);
        frame++;
        // Displaying SFML window, then clearing it
        window.display();
        window.clear();
    }
    return 0;
}
