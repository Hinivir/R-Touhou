/*
** EPITECH PROJECT, 2024
** R-Touhou
** File description:
** AGame
*/

#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "Registry.hpp"
#include "Components/Components.hpp"
// #include "Init.hpp"
#include <iostream>

namespace Game
{
    /**
     * @class AGame
     * @brief Represents a game object.
     */
    class AGame
    {
      protected:
        std::size_t nbEntities = 2048;                /**< The number of entities in the game. */
        std::size_t nbPlayer = 1;                     /**< The number of players in the game. */
        std::size_t defaultNbEnemies = 20;            /**< The default number of enemies in the game. */
        GameEngine::Registry registry;                /**< The game's entity registry. */
        std::vector<GameEngine::Entity> entityVector; /**< Vector to store game entities. */

      public:
        /**
         * @brief Constructor for AGame.
         * @param nbPlayer The number of players in the game.
         * @param nbEntities The number of entities in the game.
         * @param defaultNbEnemies The default number of enemies in the game.
         */
        AGame(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies)
            : nbPlayer(nbPlayer), nbEntities(nbEntities), registry(nbEntities), defaultNbEnemies(defaultNbEnemies)
        {
            registry.registerComponent<GameEngine::Controllable>();
            registry.registerComponent<GameEngine::Drawable>();
            registry.registerComponent<GameEngine::Position>();
            registry.registerComponent<GameEngine::Projectile>();
            registry.registerComponent<GameEngine::Size>();
            registry.registerComponent<GameEngine::Text>();
            registry.registerComponent<GameEngine::Velocity>();
        };

        void justATest() { std::cout << "just a test" << std::endl; }
        /**
         * @brief Destructor for AGame.
         */
        ~AGame() = default;

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
#endif /* !AGAME_HPP_ */
