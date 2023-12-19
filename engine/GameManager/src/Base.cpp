/*
** EPITECH PROJECT, 2023
** engine/GameManager/src/Base.cpp
** File description:
** -
*/

#include <iostream>
#include "GameManager/Base.hpp"

bool GameManager::Base::instantiate(GraphicClientProtocol::Layer::StackMapRef const &stackMap, Input::InputMapRef const &inputMap)
{
    if (!callEntryPoint)
        return false;
    instance = (reinterpret_cast<Game::GameInstance (*)()>(callEntryPoint))();
    if (!instance)
        return false;
    _inputMap = inputMap;
    _stackMap = stackMap;
    instance->init();
    clock = std::chrono::high_resolution_clock::now();
    deltaPhysicsStored = 0.0;
    return true;
}

void GameManager::Base::process(void)
{
    GameManager::Clock clockNew = std::chrono::high_resolution_clock::now();
    std::chrono::duration<LType::Delta, std::milli> deltaRaw = std::chrono::duration<LType::Delta, std::milli>(clockNew - clock);
    LType::Delta delta = deltaRaw.count() / 1e3;

    deltaPhysicsStored += delta;
    while (deltaPhysicsStored >= deltaPhysicsCap) {
        processPhysics(deltaPhysicsCap);
        deltaPhysicsStored -= (deltaPhysicsCap);
    }
    processGraphic(delta);
    clock = clockNew;
}

void GameManager::Base::processGraphic(LType::Delta const _delta)
{ }

void GameManager::Base::processPhysics(LType::Delta const _delta)
{ }
