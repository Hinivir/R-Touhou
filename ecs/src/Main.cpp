/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Main.cpp
*/

/*
** EPITECH PROJECT, 2024
** L-Type-Game-RTouhou
** File description:
** Main.cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Registry.hpp"
#include "Components/Position.hpp"
#include "Components/Velocity.hpp"
#include "Components/Drawable.hpp"
#include "Components/Controllable.hpp"
#include "Components/Sprite.hpp"
#include "Components/Color.hpp"
#include "Components/ZIndex.hpp"
#include "Components/Life.hpp"
#include "Components/Hitbox.hpp"
#include "Systems.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ECS");
    GameEngine::Registry registry(1024);
    GameEngine::System system;

    window.setFramerateLimit(60);

    registry.registerComponent<GameEngine::Controllable>();
    registry.registerComponent<GameEngine::Drawable>();
    registry.registerComponent<GameEngine::Position>();
    registry.registerComponent<GameEngine::Velocity>();
    registry.registerComponent<GameEngine::Sprite>();
    registry.registerComponent<GameEngine::Color>();
    registry.registerComponent<GameEngine::ZIndex>();
    registry.registerComponent<GameEngine::Life>();
    registry.registerComponent<GameEngine::Hitbox>();

    GameEngine::Entity movableEntity = registry.spawnEntity();
    registry.addComponent<GameEngine::Controllable>(movableEntity, GameEngine::Controllable{true});
    registry.addComponent<GameEngine::Drawable>(movableEntity, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(movableEntity, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(movableEntity, GameEngine::Velocity{10.0f, 10.0f});
    registry.addComponent<GameEngine::Sprite>(movableEntity, GameEngine::Sprite{"../resources/R-Touhou/graphics/Player.png",sf::Sprite(),sf::Texture()});
    //registry.addComponent<GameEngine::Color>(movableEntity, GameEngine::Color{0, 255, 0, 255});
    registry.addComponent<GameEngine::ZIndex>(movableEntity, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});
    registry.addComponent<GameEngine::Life>(movableEntity, GameEngine::Life{3});
    registry.addComponent<GameEngine::Hitbox>(movableEntity, GameEngine::Hitbox{});

    for (int i = 0; i < 5; ++i) {
        GameEngine::Entity staticEntity = registry.spawnEntity();
        registry.addComponent<GameEngine::Drawable>(staticEntity, GameEngine::Drawable{true});
        registry.addComponent<GameEngine::Position>(staticEntity, GameEngine::Position{30.0f, 30.0f});
        registry.addComponent<GameEngine::Velocity>(staticEntity, GameEngine::Velocity{1.5f, 0.0f});
        registry.addComponent<GameEngine::Sprite>(staticEntity, GameEngine::Sprite{"../resources/R-Touhou/graphics/Enemy.png",sf::Sprite(),sf::Texture()});
        //registry.addComponent<GameEngine::Color>(movableEntity, GameEngine::Color{255, 0, 0, 255});
        registry.addComponent<GameEngine::ZIndex>(staticEntity, GameEngine::ZIndex{});
        registry.addComponent<GameEngine::Hitbox>(staticEntity, GameEngine::Hitbox{});
    }

    system.initEnemy(registry);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
            window.close();
        }
        //system.loggingSystem(registry);
        system.enenemyMovementSystem(registry);
        system.controlSystem(registry);
        system.spriteSystem(registry);

        system.attackSystem(registry);
        system.drawSystem(registry, window);
        system.collisionSystem(registry);
        window.display();
        window.clear();
    }

    return 0;
}
