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
            std::size_t myNumber = 0;

            ClientGame() : AGame() {};
            ~ClientGame() = default;
    };
} // namespace Game

#endif
