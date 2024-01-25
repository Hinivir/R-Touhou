/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ClientGame.cpp
*/

#include "ClientGame.hpp"

Game::ClientGame::ClientGame()
    : AGame(1, 2048, 20)
{
    std::cout << "ClientGame created" << std::endl;
}

Game::ClientGame::~ClientGame()
{
    std::cout << "ClientGame destroyed" << std::endl;
}
