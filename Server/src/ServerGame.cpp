/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ServerGame.cpp
*/

#include "ServerGame.hpp"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

GameEngine::Entity Game::ServerGame::spawnBaseEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(entity, GameEngine::Drawable{true});
    return entity;
}

GameEngine::Entity Game::ServerGame::spawnMovableEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);

    registry.addComponent<GameEngine::Controllable>(entity, GameEngine::Controllable{true});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{0.0f, 500.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{10.0f, 10.0f});
    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Life>(entity, GameEngine::Life{3});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    return entity;
}

GameEngine::Entity Game::ServerGame::spawnEnemyEntity(GameEngine::Registry &registry)
{
    GameEngine::Entity entity = spawnBaseEntity(registry);

    registry.addComponent<GameEngine::Size>(entity, GameEngine::Size{50.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(entity, GameEngine::Position{30.0f, 30.0f});
    registry.addComponent<GameEngine::Velocity>(entity, GameEngine::Velocity{15.5f, 0.0f});
    registry.addComponent<GameEngine::Hitbox>(entity, GameEngine::Hitbox{});
    registry.addComponent<GameEngine::Path>(entity, GameEngine::Path{30.0f, 30.0f, 0.0f, 0.0f});
    registry.addComponent<GameEngine::Life>(entity, GameEngine::Life{2});
    registry.addComponent<GameEngine::Controllable>(entity, GameEngine::Controllable{false});
    return entity;
}

GameEngine::Entity Game::ServerGame::createBackgroundStar(GameEngine::Registry &registry)
{
    GameEngine::Entity backgroundStar = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(backgroundStar, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(backgroundStar, GameEngine::Size{WINDOW_WIDTH, WINDOW_HEIGHT});
    registry.addComponent<GameEngine::Position>(backgroundStar, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Velocity>(backgroundStar, GameEngine::Velocity{2.0f, 0.0f});

    return backgroundStar;
}

GameEngine::Entity Game::ServerGame::createGroundDown(GameEngine::Registry &registry)
{
    GameEngine::Entity groundDown = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(groundDown, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(groundDown, GameEngine::Size{1920.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(groundDown, GameEngine::Position{0.0f, 0.0f});
    registry.addComponent<GameEngine::Controllable>(groundDown, GameEngine::Controllable{false});

    return groundDown;
}

GameEngine::Entity Game::ServerGame::createGroundUp(GameEngine::Registry &registry)
{
    GameEngine::Entity groundUp = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(groundUp, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Size>(groundUp, GameEngine::Size{1920.0f, 50.0f});
    registry.addComponent<GameEngine::Position>(groundUp, GameEngine::Position{0.0f, 1030.0f});
    registry.addComponent<GameEngine::Controllable>(groundUp, GameEngine::Controllable{false});

    return groundUp;
}

GameEngine::Entity Game::ServerGame::createScore(GameEngine::Registry &registry)
{
    GameEngine::Entity score = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(score, GameEngine::Drawable{true});
    registry.addComponent<GameEngine::Position>(score, GameEngine::Position{0.0f, 0.0f});
    std::string scoreText = "Score: 0";
    registry.addComponent<GameEngine::Text>(
        score, GameEngine::Text{sf::Text(), sf::Font(), scoreText, "../games/resources/R-Touhou/font/arial.ttf", 40});

    return score;
}

GameEngine::Entity Game::ServerGame::createGameOver(GameEngine::Registry &registry)
{
    GameEngine::Entity gameOver = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(gameOver, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(
        gameOver, GameEngine::Position{WINDOW_WIDTH / 2 - 220, WINDOW_HEIGHT / 2 - 120});
    std::string gameOverText = "Game Over";
    registry.addComponent<GameEngine::Text>(gameOver,
        GameEngine::Text{sf::Text(), sf::Font(), gameOverText, "../games/resources/R-Touhou/font/arial.ttf", 80});

    return gameOver;
}

GameEngine::Entity Game::ServerGame::createYouWin(GameEngine::Registry &registry)
{
    GameEngine::Entity youWin = registry.spawnEntity();

    registry.addComponent<GameEngine::Drawable>(youWin, GameEngine::Drawable{false});
    registry.addComponent<GameEngine::Position>(
        youWin, GameEngine::Position{WINDOW_WIDTH / 2 - 220, WINDOW_HEIGHT / 2 - 120});
    std::string youWinText = "You Win !";
    registry.addComponent<GameEngine::Text>(
        youWin, GameEngine::Text{sf::Text(), sf::Font(), youWinText, "../games/resources/R-Touhou/font/arial.ttf", 80});

    return youWin;
}
