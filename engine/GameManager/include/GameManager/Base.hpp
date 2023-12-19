/*
** EPITECH PROJECT, 2023
** engine/GameManager/include/GameManager/Base.hpp
** File description:
** -
*/

/// @file
/// @brief Class used for managing games loaded dynamically

#pragma once
#include <chrono>
#include "LType/Delta.hpp"
#include "Game/GameInstance.hpp"
#include "GraphicClientProtocol/Layer/StackMap.hpp"
#include "Input/InputMapRef.hpp"
#include "SharedLibraryLoader/SpecializedLoader.hpp"

namespace GameManager {

/// @brief Clock type used to compute deltas
using Clock = std::chrono::time_point<std::chrono::high_resolution_clock>;
/// @return GameManager::Clock containing the current time
GameManager::Clock getClockNow(void);

class Base : public SharedLibraryLoader::SpecializedLoader<Game::GameInstance>
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
    /// << PROCESSES >>
    /// @brief Executes a process tick, every frame, and converts it for other processes
    void process(void);
    /// @brief Executes a process tick, every frame
    /// @param delta Time passed since last the process
    virtual void processGraphic(LType::Delta const delta);
    /// @brief Executes a physics tick, every engine frame
    /// @param delta Time passed since last the process
    virtual void processPhysics(LType::Delta const delta);
// PROTECTED ATTRIBUTES
protected:
    /// < MAPS >
    /// @brief InputMap
    Input::InputMapRef _inputMap = nullptr;
    /// @brief StackMap
    GraphicClientProtocol::Layer::StackMapRef _stackMap = nullptr;
    /// < DELTA >
    /// @brief Clock used for managing the delta passed through processes
    GameManager::Clock clock;
    /// @brief Physics delta stored for compensing lag and freezes
    LType::Delta deltaPhysicsStored = 0.0;
    /// @brief Limit of deltaPhysicsStored, otherwise triggers processGraphic
    LType::Delta deltaPhysicsCap = 1.0 / 10.0;
};

}
