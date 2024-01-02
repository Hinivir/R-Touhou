/*
** EPITECH PROJECT, 2023
** engine/Game/src/AGame.cpp
** File description:
** -
*/

#include "Game/AGame.hpp"

// Base

void Game::AGame::init(void)
{
    refreshInputs();
}

// Inputs

void Game::AGame::refreshInputs(void)
{
    for (std::size_t i = 0; i < _inputsLength; i++) {
        _inputsPressed[i] = false;
        _inputsJustPressed[i] = false;
    }
}

void Game::AGame::refreshInputs(Input::InputMapWindow const &inputMapWindow)
{
    for (std::size_t i = 0; i < _inputsLength; i++) {
        _inputsPressed[i] = (inputMapWindow.input[i] == Input::InputMapInputValue::PRESSED || inputMapWindow.input[i] == Input::InputMapInputValue::HELD);
        _inputsJustPressed[i] = inputMapWindow.input[i] == Input::InputMapInputValue::PRESSED;
    }
}

bool Game::AGame::isInputPressed(LType::InputList const input)
{
    return _inputsPressed[static_cast<std::size_t>(input)];
}

bool Game::AGame::hasInputJustBeenPressed(LType::InputList const input)
{
    return _inputsJustPressed[static_cast<std::size_t>(input)];
}

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
