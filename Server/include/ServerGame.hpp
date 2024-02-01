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

            ServerGame() : AGame() {};
            ~ServerGame() = default;
    };
} // namespace Game

#endif
