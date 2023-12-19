/*
** EPITECH PROJECT, 2023
** engine/Game/include/IGame.hpp
** File description:
** -
*/

/// @file
/// @brief Interfaces for games

#pragma once

namespace Game {

class IGame
{
public:
    virtual ~IGame() = default;
public:
    // << BASE >>
    // Init
    virtual void init(void) = 0;
};

}
