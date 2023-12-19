/*
** EPITECH PROJECT, 2023
** engine/GameManager/src/Base.cpp
** File description:
** -
*/

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
    return true;
}
