/*
** EPITECH PROJECT, 2023
** engine/GameManager/include/GameManager/Base.hpp
** File description:
** -
*/

/// @file
/// @brief Class used for managing games loaded dynamically

#pragma once
#include "Game/GameInstance.hpp"
#include "GraphicClientProtocol/Layer/StackMap.hpp"
#include "Input/InputMapRef.hpp"
#include "SharedLibraryLoader/SpecializedLoader.hpp"

namespace GameManager {

class Base : public SharedLibraryLoader::SpecializedLoader<Game::GameInstance>
{
public:
    bool instantiate(GraphicClientProtocol::Layer::StackMapRef const &stackMap, Input::InputMapRef const &inputMap);
protected:
    // InputMap
    Input::InputMapRef _inputMap = nullptr;
    // StackMap
    GraphicClientProtocol::Layer::StackMapRef _stackMap = nullptr;
};

}
