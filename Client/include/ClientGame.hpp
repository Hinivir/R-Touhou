/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ClientGame.hpp
*/

#ifndef CLIENTGAME_HPP
#define CLIENTGAME_HPP

#include "AGame.hpp"

namespace Game
{
    class ClientGame : public AGame
    {
        public:
            int shootCoolDown = 0;

            ClientGame() : AGame(){};
            ~ClientGame() = default;
            void init(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies);
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
