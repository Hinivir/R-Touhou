/*
** EPITECH PROJECT, 2023
** engine/Game/src/AGame.cpp
** File description:
** -
*/

#include "Game/AGame.hpp"

void Game::AGame::init(void)
{ }

Game::ProcessGraphicStack const &Game::AGame::getProcessGraphicStack(void) const
{
    return _processGraphicStack;
}

Game::ProcessPhysicsStack const &Game::AGame::getProcessPhysicsStack(void) const
{
    return _processPhysicsStack;
}
