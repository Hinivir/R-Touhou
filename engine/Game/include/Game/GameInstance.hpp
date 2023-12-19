/*
** EPITECH PROJECT, 2023
** engine/Game/include/GameInstance.hpp
** File description:
** -
*/

/// @file
/// @brief Instance of IGame

#pragma once
#include <Game/IGame.hpp>
#include <memory>

namespace Game {

using GameInstance = std::unique_ptr<Game::IGame>;

template <typename T>
static Game::GameInstance createGameInstance(void)
{
    return std::make_unique<T>();
}

}
