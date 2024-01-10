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
#include "Components/Window.hpp"

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
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{0.0f, 500.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{10.0f, 10.0f});
    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{"./resources/R-Touhou/graphics/Player.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::Life>(entity, GameEngine::Life{3});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    registry.addComponent<GameEngine::Projectile>(entity, GameEngine::Projectile{false});
    return entity;
}

GameEngine::Entity spawnEnemyEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);

    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{30.0f, 30.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{15.5f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(entity, GameEngine::Sprite{"./resources/R-Touhou/graphics/Enemy.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    registry.addComponent<GameEngine::Projectile>(entity, GameEngine::Projectile{false});
    registry.addComponent<GameEngine::Path>(entity, GameEngine::Path{30.0f, 30.0f, 0.0f, 0.0f});
    registry.addComponent<GameEngine::Life>(entity, GameEngine::Life{2});
    registry.addComponent<GameEngine::Controllable>(entity, GameEngine::Controllable{false});
    return entity;
}

GameEngine::Entity createBackgroundStar(GameEngine::Registry &registry)
{
    GameEngine::Entity backgroundStar = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(backgroundStar, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(backgroundStar, GameEngine::Size{WINDOW_WIDTH, WINDOW_HEIGHT});
    registry.addComponent<GameEngine::Position>(backgroundStar, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(backgroundStar, GameEngine::Velocity{10.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(backgroundStar, GameEngine::Sprite{"./resources/R-Touhou/graphics/BackgroundStar.jpg",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(backgroundStar, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE});
    // registry.addComponent<GameEngine::Controllable>(backgroundStar, GameEngine::Controllable{false});
    // registry.addComponent<GameEngine::Projectile>(backgroundStar, GameEngine::Projectile{false});

    return backgroundStar;
}

GameEngine::Entity createGroundDown(GameEngine::Registry &registry)
{
    GameEngine::Entity groundDown = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(groundDown, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(groundDown, GameEngine::Size{1920.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(groundDown, GameEngine::Position{0.0f, 0.0f});
    // registry.addComponent<GameEngine::Velocity>(groundDown, GameEngine::Velocity{10.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(groundDown, GameEngine::Sprite{"./resources/R-Touhou/graphics/Ground.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(groundDown, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE + 1});
    registry.addComponent<GameEngine::Projectile>(groundDown, GameEngine::Projectile{false});
    registry.addComponent<GameEngine::Controllable>(groundDown, GameEngine::Controllable{false});

    return groundDown;
}

GameEngine::Entity createGroundUp(GameEngine::Registry &registry)
{
    GameEngine::Entity groundUp = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(groundUp, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(groundUp, GameEngine::Size{1920.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(groundUp, GameEngine::Position{0.0f, 1030.0f});
    // registry.addComponent<GameEngine::Velocity>(groundUp, GameEngine::Velocity{10.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(groundUp, GameEngine::Sprite{"./resources/R-Touhou/graphics/Ground.png",sf::Sprite(),sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(groundUp, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE + 2});
    registry.addComponent<GameEngine::Projectile>(groundUp, GameEngine::Projectile{false});
    registry.addComponent<GameEngine::Controllable>(groundUp, GameEngine::Controllable{false});

    return groundUp;
}

GameEngine::Entity createScore(GameEngine::Registry &registry)
{
    GameEngine::Entity score = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(score, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(score, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::ZIndex>(score, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Projectile>(score, GameEngine::Projectile{false});
    registry.addComponent<GameEngine::Color>(score, GameEngine::Color{255, 255, 255, 255});
    std::string score_0 = "Score: 0";
    registry.addComponent<GameEngine::Text>(score, GameEngine::Text{sf::Text(), sf::Font(), score_0, "./resources/R-Touhou/font/arial.ttf", 40});
    registry.addComponent<GameEngine::Projectile>(score, GameEngine::Projectile{false});


    return score;
}

GameEngine::Entity createGameOver(GameEngine::Registry &registry)
{
    GameEngine::Entity gameOver = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(gameOver, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(gameOver, GameEngine::Position{1920 / 2 - 220, 1080 / 2 - 120});
    registry.addComponent<GameEngine::ZIndex>(gameOver, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Projectile>(gameOver, GameEngine::Projectile{false});
    registry.addComponent<GameEngine::Color>(gameOver, GameEngine::Color{255, 255, 255, 255});
    std::string gameover_0 = "Game Over";
    registry.addComponent<GameEngine::Text>(gameOver, GameEngine::Text{sf::Text(), sf::Font(), gameover_0, "./resources/R-Touhou/font/arial.ttf", 80});
    registry.addComponent<GameEngine::Projectile>(gameOver, GameEngine::Projectile{false});

    return gameOver;
}

int main(void)
{
    int nbRegistry = 1024;
    bool isGameOver = false;

    //client
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ECS");
    GameEngine::Registry registry(nbRegistry);
    GameEngine::System system;

    window.setFramerateLimit(60);

    //both
    GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT
        ,GameEngine::Color
        ,GameEngine::Controllable
        ,GameEngine::Drawable
        ,GameEngine::Hitbox
        ,GameEngine::Life
        ,GameEngine::Path
        ,GameEngine::Position
        ,GameEngine::Projectile
        ,GameEngine::Size
        ,GameEngine::Sprite
        ,GameEngine::SpriteTextureAnimation
        ,GameEngine::SpriteTextureRect
        ,GameEngine::Text
        ,GameEngine::Velocity
        ,GameEngine::ZIndex
    )

    GameEngine::Entity movableEntity = spawnMovableEntity(registry);
    GameEngine::Entity backgroundStar = createBackgroundStar(registry);
    GameEngine::Entity groundDown = createGroundDown(registry);
    GameEngine::Entity groundUp = createGroundUp(registry);
    GameEngine::Entity score = createScore(registry);
    GameEngine::Entity gameOver = createGameOver(registry);

    for (int i = 0; i < 5; ++i)
        GameEngine::Entity staticEntity = spawnEnemyEntity(registry);

    system.initEnemy(registry);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            window.close();
        // system.loggingSystem(registry);
        // system.backgroundParallax(registry);
        system.controlSystem(registry);
        system.spriteSystem(registry);

        system.attackSystem(registry);
        system.drawSystem(registry, window);
        system.movementSystem(registry);
        system.collisionSystem(registry);
        system.deleteEntitiesSystem(registry);
        window.display();
        window.clear();
        if (!isGameOver && registry.getComponent<GameEngine::Life>()[movableEntity].value().life <= 0) {
            registry.getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            isGameOver = true;
        }
    }
    return 0;
}
