/*
** EPITECH PROJECT, 2024
** L-Type-Server
** File description:
** Game.hpp
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "Registry.hpp"
#include "Entity.hpp"
#include "Systems.hpp"
#include <iostream>
#include <vector>
#include <string>

namespace GameEngine
{
    class Game
    {
      public:
        Game(std::string gameName, std::size_t maxEntities) : gameName(gameName), maxEntities(maxEntities){};
        ~Game();

        std::string gameName;
        std::size_t maxEntities;
        std::vector<Entity> entities = {};
        Registry registry = Registry(maxEntities);
        System systems;
    };
} // namespace GameEngine

#endif // GAME_HPP