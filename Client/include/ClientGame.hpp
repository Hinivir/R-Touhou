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
      private:
        GameEngine::Registry localRegistry;

      public:
        ClientGame(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies)
            : AGame(nbPlayer, nbEntities, defaultNbEnemies), localRegistry(7) {
            localRegistry.registerComponent<GameEngine::Color>();
            localRegistry.registerComponent<GameEngine::ZIndex>();
            localRegistry.registerComponent<GameEngine::Outline>();
            localRegistry.registerComponent<GameEngine::Sprite>();
            localRegistry.registerComponent<GameEngine::SpriteTextureAnimation>();
            localRegistry.registerComponent<GameEngine::SpriteTextureRect>();

            localRegistry.registerComponent<GameEngine::Hitbox>();
            localRegistry.registerComponent<GameEngine::Life>();
            localRegistry.registerComponent<GameEngine::Path>();

            localRegistry.registerComponent<GameEngine::Controllable>();
            localRegistry.registerComponent<GameEngine::Drawable>();
            localRegistry.registerComponent<GameEngine::Position>();
            localRegistry.registerComponent<GameEngine::Projectile>();
            localRegistry.registerComponent<GameEngine::Size>();
            localRegistry.registerComponent<GameEngine::Text>();
            localRegistry.registerComponent<GameEngine::Velocity>();
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

        GameEngine::Registry &getLocalRegistry(){ return localRegistry; };
    };
} // namespace Game

#endif
