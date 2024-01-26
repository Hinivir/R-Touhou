/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ClientGame.hpp
*/

#ifndef CLIENTGAME_HPP
#define CLIENTGAME_HPP

    #include "AGame.hpp"

namespace Game {
    class ClientGame: public AGame
    {
        public:
            ClientGame(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies);
            ~ClientGame();
    };
}

#endif
