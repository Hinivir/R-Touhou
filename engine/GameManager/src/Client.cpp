/*
** EPITECH PROJECT, 2023
** engine/GameManager/src/Client.cpp
** File description:
** -
*/

#include "GameManager/Client.hpp"

bool GameManager::Client::instantiate(GraphicClientProtocol::Layer::StackMapRef const &stackMap, Input::InputMapRef const &inputMap)
{
    if (!GameManager::Base::instantiate(stackMap, inputMap))
        return false;
    stackMap->insert({GRAPHIC_WINDOWID_DEFAULT, GraphicClientProtocol::Layer::Stack()});
    auto defaultWindowInputMap = stackMap->find(GRAPHIC_WINDOWID_DEFAULT);
    if (defaultWindowInputMap != stackMap->end())
        defaultWindowInputMap->second.push_back(GraphicClientProtocol::Layer::StackElement(GraphicClientProtocol::Layer::Color(GraphicClientProtocol::Color(0.0, 0.0, 0.0))));
    return true;
}
