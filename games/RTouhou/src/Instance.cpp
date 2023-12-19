/*
** EPITECH PROJECT, 2023
** games/RTouhou/src/EntryPoint.cpp
** File description:
** -
*/

#include <iostream>
#include "LType/Process.hpp"
#include "RTouhou/Instance.hpp"

static LTYPE_FUNCTION_PROCESS_PHYSICS(fishProcessPhysics, delta, _)
{
    std::cout << delta << std::endl;
}

void RTouhou::Instance::init(void)
{
    _processPhysicsStack.push_back({nullptr, fishProcessPhysics});
}
