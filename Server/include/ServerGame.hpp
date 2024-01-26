/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ServerGame.hpp
*/

#ifndef SERVERGAME_HPP
#define SERVERGAME_HPP

    #include "AGame.hpp"

namespace Game {
    class ServerGame: public AGame
    {
        public:
            ServerGame(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies);
            ~ServerGame();
    };
}

#endif
