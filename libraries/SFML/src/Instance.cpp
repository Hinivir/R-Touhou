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
    if (!_renderWindow[windowId].isOpen()) return;
    sf::Event event;

    while (_renderWindow[windowId].pollEvent(event)) {
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
    closeWindowId(windowId);
    _renderWindow[windowId].create(sf::VideoMode::getDesktopMode(), "L-Type", sf::Style::Resize | sf::Style::Close);
    if (!_renderWindow[windowId].isOpen())
        return;
    _renderWindow[windowId].setFramerateLimit(60);
}

// Close

void LibrarySFML::Instance::closeWindowId(Graphic::WindowId const windowId)
{
    if (_renderWindow[windowId].isOpen())
        _renderWindow[windowId].close();
}

// Draw

void LibrarySFML::Instance::drawWindowId(Graphic::WindowId const windowId)
{
    if (!_renderWindow[windowId].isOpen())
        return;
    _renderWindow[windowId].clear(sf::Color::Black);
    _renderWindow[windowId].display();
}

// IsOpen

bool LibrarySFML::Instance::isWindowIdOpen(Graphic::WindowId const windowId) const
{
    return _renderWindow[windowId].isOpen();
}

// << MEMORY >>

// Clear/Reset

void LibrarySFML::Instance::reloadHard(void)
{
    closeWindowAll();
    openWindow();
}
