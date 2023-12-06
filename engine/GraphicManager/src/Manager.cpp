/*
** EPITECH PROJECT, 2023
** engine/GraphicManager/src/Manager.cpp
** File description:
** -
*/

#include "GraphicManager/Manager.hpp"

// CONSTRUCTOR

GraphicManager::Manager::Manager(void)
{
    type = SharedLibraryInfo::InfoType::LIBRARY;
}

GraphicManager::Manager::Manager(std::string const &filepath)
{
    Manager();
    load(filepath);
}

// INSTANTIATE

bool GraphicManager::Manager::instantiate(void)
{
    if (!callEntryPoint)
        return false;
    instance = (reinterpret_cast<Graphic::GraphicInstance (*)()>(callEntryPoint))();
    return true;
}
