/*
** EPITECH PROJECT, 2023
** libraries/SFML/src/Instance.cpp
** File description:
** -
*/

#include <iostream>
#include <SFML/Window/Event.hpp>
#include "LibrarySFML/Instance.hpp"

// Constructor and Destructor

LibrarySFML::Instance::Instance(void)
{
    std::cout << "SFML: open" << std::endl;
}

LibrarySFML::Instance::~Instance()
{
    closeWindowAll();
    std::cout << "SFML: close" << std::endl;
}

// << INPUTS >>

// Refresh

void LibrarySFML::Instance::refreshInputMapWindowIdOnWindow(Graphic::WindowId const windowId, Input::InputMapWindow &inputMapWindow)
{
    inputMapWindow.clearEvent();
    if (windowId != GRAPHIC_WINDOWID_DEFAULT) return;
    sf::Event event;

    while (_renderWindow.pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::Closed:
            inputMapWindow.setEvent(Input::InputMapEvent::CLOSE, true);
            break;
        default:
            break;
        }
    }
}

// << WINDOW >>

// Open

void LibrarySFML::Instance::openWindowId(Graphic::WindowId const windowId)
{
    if (windowId != GRAPHIC_WINDOWID_DEFAULT)
        return;
    closeWindowId(windowId);
    _renderWindow.create(sf::VideoMode::getDesktopMode(), "L-Type", sf::Style::Resize | sf::Style::Close);
    if (!_renderWindow.isOpen())
        return;
    _renderWindow.setFramerateLimit(60);
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
    if (windowId != GRAPHIC_WINDOWID_DEFAULT || !_renderWindow.isOpen())
        return;
    _renderWindow.clear(sf::Color::Black);
    _renderWindow.display();
}

// IsOpen

bool LibrarySFML::Instance::isWindowIdOpen(Graphic::WindowId const windowId) const
{
    return (windowId == GRAPHIC_WINDOWID_DEFAULT && _renderWindow.isOpen());
}

// << MEMORY >>

// Clear/Reset

void LibrarySFML::Instance::reloadHard(void)
{
    closeWindowAll();
    openWindow();
}
