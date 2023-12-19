/*
** EPITECH PROJECT, 2023
** engine/GameManager/src/Client.cpp
** File description:
** -
*/

#include <iostream>
#include "GameManager/Client.hpp"

bool GameManager::Client::instantiate(GraphicClientProtocol::Layer::StackMapRef const &stackMap, Input::InputMapRef const &inputMap)
{
    if (!GameManager::Base::instantiate(stackMap, inputMap))
        return false;
    if (!stackMap)
        return false;
    stackMap->insert({GRAPHIC_WINDOWID_DEFAULT, GraphicClientProtocol::Layer::Stack()});
    auto defaultWindowInputMap = stackMap->find(GRAPHIC_WINDOWID_DEFAULT);
    if (defaultWindowInputMap != stackMap->end())
        defaultWindowInputMap->second.push_back(GraphicClientProtocol::Layer::StackElement(GraphicClientProtocol::Layer::Color(GraphicClientProtocol::Color(0.0, 0.0, 0.0))));
    return true;
}

void GameManager::Client::processGraphic(LType::Delta const delta)
{
    if (!instance) return;
    Game::ProcessGraphicStack const &processGraphicStack = instance->getProcessGraphicStack();
    LType::GameRefenrence game = *instance.get();

    for (std::size_t i = 0; i < processGraphicStack.size(); i++)
        if (processGraphicStack[i].function)
            processGraphicStack[i].function(game, processGraphicStack[i].target.lock(), delta);
}
