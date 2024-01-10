/*
** EPITECH PROJECT, 2024
** R-Touhou_Bootstrap
** File description:
** Main.cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Registry.hpp"
#include "Systems.hpp"
#include "Macros/ForEach.hpp"

#define REGISTER_COMPONENT(COMPONENT) registry.registerComponent<COMPONENT>();

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "ECS");
    GameEngine::Registry registry(1024);
    GameEngine::System system;

    window.setFramerateLimit(60);

    GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT
        ,GameEngine::Color
        ,GameEngine::Controllable
        ,GameEngine::Drawable
        ,GameEngine::Hitbox
        ,GameEngine::Life
        ,GameEngine::Position
        ,GameEngine::Size
        ,GameEngine::Sprite
        ,GameEngine::SpriteTextureAnimation
        ,GameEngine::SpriteTextureRect
        ,GameEngine::Velocity
        ,GameEngine::ZIndex
    )

    GameEngine::Entity movableEntity = registry.spawnEntity();
    registry.addComponent<GameEngine::Controllable>(movableEntity, GameEngine::Controllable{true});
    registry.addComponent<GameEngine::Drawable>(movableEntity, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(movableEntity, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(movableEntity, GameEngine::Velocity{10.0f, 10.0f});
    registry.addComponent<GameEngine::Size>(movableEntity, GameEngine::Size{150.0f, 150.0f});
    registry.addComponent<GameEngine::Sprite>(movableEntity, GameEngine::Sprite{"../resources/R-Touhou/graphics/Player.png",sf::Sprite(),sf::Texture()});
    //registry.addComponent<GameEngine::Color>(movableEntity, GameEngine::Color{0, 255, 0, 255});
    registry.addComponent<GameEngine::ZIndex>(movableEntity, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});
    registry.addComponent<GameEngine::Life>(movableEntity, GameEngine::Life{3});
    registry.addComponent<GameEngine::Hitbox>(movableEntity, GameEngine::Hitbox{});

    GameEngine::Entity background = registry.spawnEntity();
    registry.addComponent<GameEngine::Drawable>(background, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(background, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(background, GameEngine::Velocity{10.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(background, GameEngine::Sprite{"../resources/R-Touhou/graphics/Background.jpg",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(background, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE});

    GameEngine::Entity score = registry.spawnEntity();
    registry.addComponent<GameEngine::Drawable>(score, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(score, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::ZIndex>(score, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});

    std::string score_0 = "Score: 0";
    //registry.addComponent<GameEngine::Text>(score, GameEngine::Text{"../resources/R-Touhou/font/font.ttf", score_0, 24, sf::Color::Black});

    for (int i = 0; i < 5; ++i) {
        GameEngine::Entity staticEntity = registry.spawnEntity();
        registry.addComponent<GameEngine::Drawable>(staticEntity, GameEngine::Drawable{true});
        registry.addComponent<GameEngine::Size>(staticEntity, GameEngine::Size{25.0f, 25.0f});
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
        system.enemyMovementSystem(registry);
        system.backgroundParallax(registry);
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
