/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ClientGame.cpp
*/

#include "ClientGame.hpp"

Game::ClientGame::ClientGame(std::size_t nbPlayer, std::size_t nbEntities, std::size_t defaultNbEnemies)
    : Game::AGame(nbPlayer, nbEntities, defaultNbEnemies)
{
    std::cout << "ClientGame created" << std::endl;
}

Game::ClientGame::~ClientGame()
{
    std::cout << "ClientGame destroyed" << std::endl;
}
