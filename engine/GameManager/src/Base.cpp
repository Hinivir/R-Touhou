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
    _deltaPhysicsStored = 0.0;
    return true;
}

void GameManager::Base::process(void)
{
    GameManager::Clock clockNew = GameManager::getClockNow();
    std::chrono::duration<LType::Delta, std::milli> deltaRaw = std::chrono::duration<LType::Delta, std::milli>(clockNew - clock);
    LType::Delta delta = deltaRaw.count() / 1e3;

    _deltaPhysicsCap = (instance ? (1.0 / instance->getProcessPhysicsPerSec()) : _deltaPhysicsCap);
    _deltaPhysicsStored += delta;
    if (_inputMap) {
        for (auto const &[windowId, window] : _inputMap->window) {
            if (windowId == GRAPHIC_WINDOWID_DEFAULT)
                instance->refreshInputs(window);
        }
    }
    while (_deltaPhysicsStored >= _deltaPhysicsCap) {
        processPhysics(_deltaPhysicsCap);
        _deltaPhysicsStored -= _deltaPhysicsCap;
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
    LType::GameRefenrence game = *instance.get();

    for (std::size_t i = 0; i < processPhysicsStack.size(); i++)
        if (processPhysicsStack[i].function)
            processPhysicsStack[i].function(game, processPhysicsStack[i].target.lock(), delta);
}
