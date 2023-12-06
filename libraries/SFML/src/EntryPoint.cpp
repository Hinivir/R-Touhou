/*
** EPITECH PROJECT, 2023
** libraries/SFML/src/EntryPoint.cpp
** File description:
** -
*/

#include <SharedLibraryInfo/Info.hpp>

extern "C" void entryPoint(void)
{
    return;
}

extern "C" SharedLibraryInfo::Info info(void)
{
    SharedLibraryInfo::Info information;

    information.name = "SFML";
    information.version = "1.0.0";
    information.type = SharedLibraryInfo::InfoType::LIBRARY;
    return information;
}
