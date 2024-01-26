/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ServerGame.cpp
*/

#include "ServerGame.hpp"

Game::ServerGame::ServerGame(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies)
    : AGame(nbPlayer, nbEntities, defaultNbEnemies)
{
    std::cout << "ServerGame created" << std::endl;
}

Game::ServerGame::~ServerGame()
{
    std::cout << "ServerGame destroyed" << std::endl;
}
