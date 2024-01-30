/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ServerGame.hpp
*/

#ifndef SERVERGAME_HPP
#define SERVERGAME_HPP

#include "AGame.hpp"

namespace Game
{
    class ServerGame : public AGame
    {
        public:
            bool isGameOver = false;
            int enemyCoolDown = 0;
            bool spawnEnemy = true;

            ServerGame(): AGame() {};
            ~ServerGame() = default;
            void init(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies);
            void setup();
            GameEngine::Entity spawnBaseEntity(GameEngine::Registry &registry);
            GameEngine::Entity spawnMovableEntity(GameEngine::Registry &registry);
            GameEngine::Entity spawnEnemyEntity(GameEngine::Registry &registry);
            GameEngine::Entity createBackgroundStar(GameEngine::Registry &registry);
            GameEngine::Entity createGroundDown(GameEngine::Registry &registry);
            GameEngine::Entity createGroundUp(GameEngine::Registry &registry);
            GameEngine::Entity createScore(GameEngine::Registry &registry);
            GameEngine::Entity createGameOver(GameEngine::Registry &registry);
            GameEngine::Entity createYouWin(GameEngine::Registry &registry);
    };
} // namespace Game

#endif
