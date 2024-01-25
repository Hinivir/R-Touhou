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
//#include "Init.hpp"
#include <iostream>

namespace Game {
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
                : nbPlayer(nbPlayer),
                  nbEntities(nbEntities),
                  registry(nbEntities),
                  defaultNbEnemies(defaultNbEnemies)
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

            /**
             * @brief Initializes the game.
             */
            // TODO: Need to init enemies
            /*void initGame()
            {
                // Create background star entity
                GameEngine::Entity background = createBackgroundStar(registry);
                entityVector.push_back(background);

                // Create player entities
                for (int i = 1; i <= this->nbPlayer; i++) {
                    GameEngine::Entity player = spawnMovableEntity(registry);
                    registry.getComponent<GameEngine::Position>()[player].value().y = 100 + i * 100;
                    entityVector.push_back(player);
                }

                // Create default number of enemy entities
                for (int i = 0; i < defaultNbEnemies; ++i) {
                    GameEngine::Entity staticEntity = spawnEnemyEntity(registry);
                    entityVector.push_back(staticEntity);
                }

                // Create ground entities
                GameEngine::Entity groundDown = createGroundDown(registry);
                entityVector.push_back(groundDown);
                GameEngine::Entity groundUp = createGroundUp(registry);
                entityVector.push_back(groundUp);

                // Create score entity
                GameEngine::Entity score = createScore(registry);
                entityVector.push_back(score);

                // Create game over entity
                GameEngine::Entity gameOver = createGameOver(registry);
                entityVector.push_back(gameOver);

                // Create you win entity
                GameEngine::Entity youWin = createYouWin(registry);
                entityVector.push_back(youWin);
            }
            */
    };
}
#endif /* !AGAME_HPP_ */
