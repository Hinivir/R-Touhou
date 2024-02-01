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
#include <iostream>

int main(void)
{
    // Initialisation
    int nbRegistry = 1024;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bad Apple");
    sf::Music music;
    window.setFramerateLimit(30);
    GameEngine::Registry registry(nbRegistry);
    GameEngine::SystemGroup system;
    // Registering components for system.spriteSystem and system.drawSystem
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
        // Displaying SFML window, then clearing it
        window.display();
        window.clear();
    }
    return 0;
}
