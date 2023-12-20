/*
** EPITECH PROJECT, 2023
** libraries/SFML/src/EntryPoint.cpp
** File description:
** -
*/

#include "Graphic/GraphicInstance.hpp"
#include "LibrarySFML/Instance.hpp"
#include "SharedLibraryInfo/Info.hpp"

extern "C" Graphic::GraphicInstance entryPoint(void)
{
    return Graphic::createGraphicInstance<LibrarySFML::Instance>();
}

extern "C" SharedLibraryInfo::Info info(void)
{
    SharedLibraryInfo::Info information;

    information.name = "SFML";
    information.version = "1.0.0";
    information.type = SharedLibraryInfo::InfoType::LIBRARY;
    return information;
}
