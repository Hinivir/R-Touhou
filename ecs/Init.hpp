/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Init.hpp
*/

#include <iostream>

#include "Components/Components.hpp"
#include "Entity.hpp"
#include "Registry.hpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

GameEngine::Entity spawnBaseEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Outline>(entity, GameEngine::Outline{5});
    return entity;
}

GameEngine::Entity spawnMovableEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);
    float entityColor[3] = {0.0, 1.0, 0.0};

    registry.addComponent<GameEngine::Controllable>(entity, GameEngine::Controllable{true});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{0.0f, 500.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{10.0f, 10.0f});
    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Sprite>(
        entity, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/Player.png", sf::Sprite(), sf::Texture()});
    registry.addComponent<GameEngine::Life>(entity, GameEngine::Life{3});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    registry.addComponent<GameEngine::Color>(
        entity, GameEngine::Color{static_cast<GameEngine::ColorValue>(205 * entityColor[0] + 50),
                    static_cast<GameEngine::ColorValue>(205 * entityColor[1] + 50),
                    static_cast<GameEngine::ColorValue>(205 * entityColor[2] + 50)});
    registry.addComponent<GameEngine::Outline>(
        entity, GameEngine::Outline{5, {static_cast<GameEngine::ColorValue>(100 * entityColor[0]),
                                           static_cast<GameEngine::ColorValue>(100 * entityColor[1]),
                                           static_cast<GameEngine::ColorValue>(100 * entityColor[2])}});
    return entity;
}

GameEngine::Entity spawnEnemyEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);

    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{30.0f, 30.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{15.5f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(
        entity, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/Enemy.png", sf::Sprite(), sf::Texture()});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
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
    registry.addComponent<GameEngine::Velocity>(backgroundStar, GameEngine::Velocity{2.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(backgroundStar,
        GameEngine::Sprite{"../games/resources/R-Touhou/graphics/BackgroundStar.jpg", sf::Sprite(), sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(
        backgroundStar, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE});
    registry.addComponent<GameEngine::Color>(backgroundStar, GameEngine::Color{50, 50, 50});

    return backgroundStar;
}

GameEngine::Entity createGroundDown(GameEngine::Registry &registry)
{
    GameEngine::Entity groundDown = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(groundDown, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(groundDown, GameEngine::Size{1920.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(groundDown, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Sprite>(
        groundDown, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/Ground.png", sf::Sprite(), sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(
        groundDown, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE + 1});
    registry.addComponent<GameEngine::Controllable>(groundDown, GameEngine::Controllable{false});

    return groundDown;
}

GameEngine::Entity createGroundUp(GameEngine::Registry &registry)
{
    GameEngine::Entity groundUp = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(groundUp, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(groundUp, GameEngine::Size{1920.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(groundUp, GameEngine::Position{0.0f, 1030.0f});
    registry.addComponent<GameEngine::Sprite>(
        groundUp, GameEngine::Sprite{"../games/resources/R-Touhou/graphics/Ground.png", sf::Sprite(), sf::Texture()});
    registry.addComponent<GameEngine::ZIndex>(groundUp, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE + 2});
    registry.addComponent<GameEngine::Controllable>(groundUp, GameEngine::Controllable{false});

    return groundUp;
}

GameEngine::Entity createScore(GameEngine::Registry &registry)
{
    GameEngine::Entity score = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(score, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(score, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::ZIndex>(score, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(score, GameEngine::Color{255, 255, 255, 255});
    std::string scoreText = "Score: 0";
    registry.addComponent<GameEngine::Text>(
        score, GameEngine::Text{sf::Text(), sf::Font(), scoreText, "../games/resources/R-Touhou/font/arial.ttf", 40});

    return score;
}

GameEngine::Entity createGameOver(GameEngine::Registry &registry)
{
    GameEngine::Entity gameOver = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(gameOver, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(
        gameOver, GameEngine::Position{WINDOW_WIDTH / 2 - 220, WINDOW_HEIGHT / 2 - 120});
    registry.addComponent<GameEngine::ZIndex>(gameOver, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(gameOver, GameEngine::Color{255, 255, 255, 255});
    std::string gameOverText = "Game Over";
    registry.addComponent<GameEngine::Text>(gameOver,
        GameEngine::Text{sf::Text(), sf::Font(), gameOverText, "../games/resources/R-Touhou/font/arial.ttf", 80});

    return gameOver;
}

GameEngine::Entity createYouWin(GameEngine::Registry &registry)
{
    GameEngine::Entity youWin = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(youWin, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(
        youWin, GameEngine::Position{WINDOW_WIDTH / 2 - 220, WINDOW_HEIGHT / 2 - 120});
    registry.addComponent<GameEngine::ZIndex>(youWin, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE});
    registry.addComponent<GameEngine::Color>(youWin, GameEngine::Color{255, 255, 255, 255});
    std::string youWinText = "You Win !";
    registry.addComponent<GameEngine::Text>(
        youWin, GameEngine::Text{sf::Text(), sf::Font(), youWinText, "../games/resources/R-Touhou/font/arial.ttf", 80});

    return youWin;
}
