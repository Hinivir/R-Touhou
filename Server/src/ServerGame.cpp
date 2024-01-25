/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ServerGame.cpp
*/

#include "ServerGame.hpp"

Game::ServerGame::ServerGame()
    : AGame(1, 2048, 20)
{
    std::cout << "ServerGame created" << std::endl;
}

Game::ServerGame::~ServerGame()
{
    std::cout << "ServerGame destroyed" << std::endl;
}
