/*
** EPITECH PROJECT, 2023
** libraries/SFML/src/EntryPoint.cpp
** File description:
** -
*/

#include "Game/GameInstance.hpp"
#include "RTouhou/Instance.hpp"
#include "SharedLibraryInfo/Info.hpp"

extern "C" Game::GameInstance entryPoint(void)
{
    return Game::createGameInstance<RTouhou::Instance>();
}

extern "C" SharedLibraryInfo::Info info(void)
{
    SharedLibraryInfo::Info information;

    information.name = "RTouhou";
    information.version = "1.0.0";
    information.type = SharedLibraryInfo::InfoType::GAME;
    return information;
}
