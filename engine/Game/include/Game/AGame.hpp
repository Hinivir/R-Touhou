/*
** EPITECH PROJECT, 2023
** engine/Game/include/AGame.hpp
** File description:
** -
*/

/// @file
/// @brief Default implemenation of AGame

#pragma once
#include "Game/IGame.hpp"

namespace Game {

class AGame : public Game::IGame
{
public:
    // << BASE >>
    // Init
    void init(void) override;
};

}
