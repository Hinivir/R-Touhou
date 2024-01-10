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

GameEngine::Entity spawnBaseEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});
    //registry.addComponent<GameEngine::Color>(entity, GameEngine::Color{0, 255, 0, 255});
    return entity;
}

GameEngine::Entity spawnMovableEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);

    registry.addComponent<GameEngine::Controllable>(entity, GameEngine::Controllable{true});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{10.0f, 10.0f});
    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{150.0f, 150.0f});
    registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{"../resources/R-Touhou/graphics/Player.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::Life>(entity, GameEngine::Life{3});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    return entity;
}

GameEngine::Entity spawnEnemyEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);

    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{25.0f, 25.0f});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{30.0f, 30.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{1.5f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{"../resources/R-Touhou/graphics/Enemy.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    return entity;
}

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

    GameEngine::Entity movableEntity = spawnMovableEntity(registry);

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

    for (int i = 0; i < 5; ++i)
        GameEngine::Entity staticEntity = spawnEnemyEntity(registry);

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
