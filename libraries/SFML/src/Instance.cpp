/*
** EPITECH PROJECT, 2023
** libraries/SFML/src/Instance.cpp
** File description:
** -
*/

#include <iostream>
#include "LibrarySFML/Instance.hpp"

// Constructor and Destructor

LibrarySFML::Instance::Instance(void)
{
    std::cout << "SFML: open" << std::endl;
    openWindow();
}

LibrarySFML::Instance::~Instance()
{
    std::cout << "SFML: close" << std::endl;
    closeWindowAll();
}

// Open

void LibrarySFML::Instance::openWindowId(Graphic::WindowId const windowId)
{
    if (windowId != GRAPHIC_WINDOWID_DEFAULT)
        return;
    closeWindowId(windowId);
    _renderWindow.create(sf::VideoMode::getDesktopMode(), "L-Type", sf::Style::Resize | sf::Style::Close);
}

// Close

void LibrarySFML::Instance::closeWindowId(Graphic::WindowId const windowId)
{
    if (windowId != GRAPHIC_WINDOWID_DEFAULT)
        return;
    if (_renderWindow.isOpen())
        _renderWindow.close();
}

// Draw

void LibrarySFML::Instance::drawWindowId(Graphic::WindowId const windowId)
{
    if (windowId != GRAPHIC_WINDOWID_DEFAULT || _renderWindow.isOpen()) return;
    _renderWindow.clear(sf::Color::Black);
    _renderWindow.display();
}

// IsOpen

bool LibrarySFML::Instance::isWindowIdOpen(Graphic::WindowId const windowId) const
{
    return (windowId == GRAPHIC_WINDOWID_DEFAULT && _renderWindow.isOpen());
}
