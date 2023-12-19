/*
** EPITECH PROJECT, 2023
** engine/GameManager/src/Base.cpp
** File description:
** -
*/

#include "GameManager/Base.hpp"

GameManager::Clock GameManager::getClockNow(void)
{
    return std::chrono::high_resolution_clock::now();
}

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
    clock = GameManager::getClockNow();
    deltaPhysicsStored = 0.0;
    return true;
}

void GameManager::Base::process(void)
{
    GameManager::Clock clockNew = GameManager::getClockNow();
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

void GameManager::Base::processPhysics(LType::Delta const delta)
{
    if (!instance) return;
    Game::ProcessPhysicsStack const &processPhysicsStack = instance->getProcessPhysicsStack();

    for (std::size_t i = 0; i < processPhysicsStack.size(); i++)
        processPhysicsStack[i].second(delta, processPhysicsStack[i].first);
}
