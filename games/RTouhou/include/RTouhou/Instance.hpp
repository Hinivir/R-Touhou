/*
** EPITECH PROJECT, 2023
** games/RTouhou/include/RTouhou/Instance.hpp
** File description:
** -
*/

#pragma once
#include "Game/AGame.hpp"

namespace RTouhou {

class Instance : public Game::AGame
{
public:
    // << BASE >>
    // Init
    void init(void) override;
};

}
