/*
** EPITECH PROJECT, 2023
** games/RTouhou/src/EntryPoint.cpp
** File description:
** -
*/

#include <iostream>
#include "LType/Process.hpp"
#include "RTouhou/Instance.hpp"

static LTYPE_FUNCTION_PROCESS_PHYSICS(fishProcessPhysics, delta)
{
    std::cout << delta << std::endl;
}

void RTouhou::Instance::init(void)
{
    processPhysicsStack.push_back(fishProcessPhysics);
}
