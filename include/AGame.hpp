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
#include "Systems.hpp"
#include <iostream>

namespace Game
{
    class AGame
    {
        protected:
            std::size_t nbEntities = 2048;
            std::size_t nbPlayer = 1;
            std::size_t defaultNbEnemies = 20;
            GameEngine::Registry registry;
            GameEngine::SystemGroup systemGroup;
            std::vector<GameEngine::Entity> entityVector = {};
            std::vector<GameEngine::Entity> enemiesVector = {};
            std::vector<GameEngine::Position> enemiesPos = {};
            int totalScore = 0;

        public:
            AGame() : registry(nbEntities), systemGroup()
            {
                registry.registerComponent<GameEngine::Color>();
                registry.registerComponent<GameEngine::ZIndex>();
                registry.registerComponent<GameEngine::Outline>();
                registry.registerComponent<GameEngine::Sprite>();
                registry.registerComponent<GameEngine::SpriteTextureAnimation>();
                registry.registerComponent<GameEngine::SpriteTextureRect>();
            };
            void init(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies);
            void setup()
            {
                GameEngine::Entity score = createScore(registry);
                entityVector.push_back(score);
                for (int i = 0; i < nbPlayer; ++i) {
                    GameEngine::Entity movableEntity = spawnMovableEntity(registry);
                    entityVector.push_back(movableEntity);
                }
                GameEngine::Entity backgroundStar1 = createBackgroundStar(registry);
                entityVector.push_back(backgroundStar1);
                GameEngine::Entity backgroundStar2 = createBackgroundStar(registry);
                getRegistry().getComponent<GameEngine::Position>()[backgroundStar2].value().x = 1920;
                entityVector.push_back(backgroundStar2);
                GameEngine::Entity groundDown = createGroundDown(registry);
                entityVector.push_back(groundDown);
                GameEngine::Entity groundUp = createGroundUp(registry);
                entityVector.push_back(groundUp);
                GameEngine::Entity gameOver = createGameOver(registry);
                entityVector.push_back(gameOver);
                GameEngine::Entity youWin = createYouWin(registry);
                entityVector.push_back(youWin);
                for (int i = 0; i < defaultNbEnemies; ++i) {
                    GameEngine::Entity staticEntity = spawnEnemyEntity(registry);
                    entityVector.push_back(staticEntity);
                    enemiesVector.push_back(staticEntity);
                }
            };
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

            GameEngine::Registry &getRegistry() { return registry; };
            GameEngine::SystemGroup &getSystemGroup() { return systemGroup; };
            std::vector<GameEngine::Entity> getEnityVector() { return entityVector; };
            std::vector<GameEngine::Entity> getEnemiesVector() { return enemiesVector; };
            std::vector<GameEngine::Position> getEnemiesPos() { return enemiesPos; };
            std::size_t getNbEntities() { return nbEntities; };
            std::size_t getNbPlayer() { return nbPlayer; };
            std::size_t getDefaultNbEnemies() { return defaultNbEnemies; };
    };
} // namespace Game
#endif /* !AGAME_HPP_ */
