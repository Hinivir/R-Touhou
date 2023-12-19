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
    /// @brief Instantiate `callEntryPoint` inside of `instance`
    /// @param stackMap StackMap put inside of `self`
    /// @param inputMap InputMap put inside of `self`
    /// @return `true`, of `false` if a problem is encountered
    bool instantiate(GraphicClientProtocol::Layer::StackMapRef const &stackMap, Input::InputMapRef const &inputMap);
protected:
    // InputMap
    Input::InputMapRef _inputMap = nullptr;
    // StackMap
    GraphicClientProtocol::Layer::StackMapRef _stackMap = nullptr;
};

}
