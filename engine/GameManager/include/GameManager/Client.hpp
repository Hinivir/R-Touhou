/*
** EPITECH PROJECT, 2023
** engine/GameManager/include/GameManager/Client.hpp
** File description:
** -
*/

/// @file
/// @brief Class used for managing games loaded dynamically

#pragma once
#include "GameManager/Base.hpp"

namespace GameManager {

namespace Layer {

enum Layers_e {
    STATIC_BACKGROUND,
    SPRITES,
};

}

class Client : public GameManager::Base
{
// LOADER
public:
    /// @brief Instantiate `callEntryPoint` inside of `instance`
    /// @param stackMap StackMap put inside of `self`
    /// @param inputMap InputMap put inside of `self`
    /// @return `true`, of `false` if a problem is encountered
    bool instantiate(GraphicClientProtocol::Layer::StackMapRef const &stackMap, Input::InputMapRef const &inputMap);
// GAME MANAGER
public:
    /// @brief Executes a process tick, every frame
    /// @param delta Time passed since last the process
    void processGraphic(LType::Delta const delta) override;
};

}
