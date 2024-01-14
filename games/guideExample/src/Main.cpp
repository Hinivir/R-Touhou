/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Main.cpp
*/

#include "Registry.hpp"
#include "Systems.hpp"
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
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ECS");
    window.setFramerateLimit(60);
    GameEngine::Registry registry(nbRegistry);
    GameEngine::System system;
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
    // Test Entity
    GameEngine::Entity entity = registry.spawnEntity();
    registry.addComponent<MyGame::Gravity>(entity, MyGame::Gravity{true, 2});
    registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{100.0f, 100.0f});
    registry.addComponent<GameEngine::Sprite>(
        entity, GameEngine::Sprite{"./resources/R-Touhou/graphics/Fish.png", sf::Sprite(), sf::Texture()});
    // Main Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        // Initializing sprite textures
        system.spriteSystem(registry);
        // Our gravity system
        systemGravity(registry);
        // Drawing entities on screen
        system.drawSystem(registry, window);
        // Displaying SFML window, then clearing it
        window.display();
        window.clear();
    }
    return 0;
}