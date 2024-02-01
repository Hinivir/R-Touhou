/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Main.cpp
*/

#include "Registry.hpp"
#include "Systems.hpp"
#include "Systems/Draw.hpp"
#include "Systems/Sprite.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace MyGame
{
    struct Gravity
    {
        bool isAffectedByGravity = false;
        float weigth = 0;
    };
} // namespace MyGame

void systemGravity(GameEngine::Registry &r)
{
    EXTRACT_COMPONENT(GameEngine::Position, positions);
    EXTRACT_COMPONENT_CONST(MyGame::Gravity, gravities);
    for (std::size_t i = 0; i < positions.size(); ++i) {
        FROM_COMPONENT_TO_VARIABLE(positions, i, position, hasPosition);
        FROM_COMPONENT_TO_VARIABLE_CONST(gravities, i, gravity, hasGravity);
        if (hasPosition && hasGravity && gravity.value().isAffectedByGravity)
            position.value().y += gravity.value().weigth;
    }
}

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
    registry.registerComponent<GameEngine::Color>();
    registry.registerComponent<GameEngine::Controllable>();
    registry.registerComponent<GameEngine::Drawable>();
    registry.registerComponent<GameEngine::Outline>();
    registry.registerComponent<GameEngine::Position>();
    registry.registerComponent<GameEngine::Size>();
    registry.registerComponent<GameEngine::Sprite>();
    registry.registerComponent<GameEngine::SpriteTextureAnimation>();
    registry.registerComponent<GameEngine::SpriteTextureRect>();
    registry.registerComponent<GameEngine::Text>();
    registry.registerComponent<GameEngine::ZIndex>();
    registry.registerComponent<MyGame::Gravity>();
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
        // Initializing sprite textures
        GameEngine::System::sprite(registry);
        // Our gravity system
        systemGravity(registry);
        // Drawing entities on screen
        GameEngine::System::draw(registry, window);
        // Displaying SFML window, then clearing it
        window.display();
        window.clear();
    }
    return 0;
}
