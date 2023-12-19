/*
** EPITECH PROJECT, 2023
** games/RTouhou/src/EntryPoint.cpp
** File description:
** -
*/

#include <iostream>
#include "LType/Entity.hpp"
#include "LType/Process.hpp"
#include "RTouhou/Instance.hpp"

static LTYPE_FUNCTION_PROCESS_PHYSICS(fishProcessPhysics, fish, delta)
{
    std::cout << (fish ? "true" : "false") << std::endl;
    std::cout << _game.getProcessPhysicsPerSec() << " " << delta << std::endl;
}

void RTouhou::Instance::init(void)
{
    LType::EntityInstance fish = addEntity(LType::createEntityInstance<LType::Entity>());

    addFunctionProcessPhysics(fish, fishProcessPhysics);
}
