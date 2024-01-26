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
            ClientGame(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies)
                : AGame(nbPlayer, nbEntities, defaultNbEnemies)
            {
                registry.registerComponent<GameEngine::Color>();                  // c
                registry.registerComponent<GameEngine::ZIndex>();                 // c
                registry.registerComponent<GameEngine::Outline>();                // c
                registry.registerComponent<GameEngine::Sprite>();                 // c
                registry.registerComponent<GameEngine::SpriteTextureAnimation>(); // c
                registry.registerComponent<GameEngine::SpriteTextureRect>();      // c
            };
            ~ClientGame() = default;
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
