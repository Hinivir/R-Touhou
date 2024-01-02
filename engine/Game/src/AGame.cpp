/*
** EPITECH PROJECT, 2023
** engine/Game/src/AGame.cpp
** File description:
** -
*/

#include "Game/AGame.hpp"

// Base

void Game::AGame::init(void)
{ }

// Stacks

void Game::AGame::addFunctionProcessGraphic(LType::FunctionTarget const target, LType::ProcessGraphic function)
{
    _processGraphicStack.push_back({target, function});
}

void Game::AGame::addFunctionProcessPhysics(LType::FunctionTarget const target, LType::ProcessPhysics function)
{
    _processPhysicsStack.push_back({target, function});
}

Game::ProcessGraphicStack const &Game::AGame::getProcessGraphicStack(void) const
{
    return _processGraphicStack;
}

Game::ProcessPhysicsStack const &Game::AGame::getProcessPhysicsStack(void) const
{
    return _processPhysicsStack;
}

// Entity

LType::EntityInstance Game::AGame::addEntity(LType::EntityInstance entity)
{
    _entityStack.push_back(entity);
    _entityStackNew.push_back(entity);
    return entity;
}

Game::EntityStack const &Game::AGame::getEntityStack(void) const
{
    return _entityStack;
}

Game::EntityPtrStack const &Game::AGame::getEntityStackNew(void) const
{
    return _entityStackNew;
}

void Game::AGame::clearEntityStackNew(void)
{
    _entityStackNew.clear();
}

// System

float Game::AGame::getProcessPhysicsPerSec(void) const
{
    return _processPhysicsPerSec;
}
