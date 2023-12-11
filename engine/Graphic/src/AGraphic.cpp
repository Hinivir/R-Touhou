/*
** EPITECH PROJECT, 2023
** engine/Graphic/src/AGraphic.cpp
** File description:
** -
*/

#include "Graphic/AGraphic.hpp"

// << INPUTS >>

// InputMap

void Graphic::AGraphic::setInputMap(Input::InputMapRef const &inputMap)
{
    _inputMap = inputMap;
}

Input::InputMapRef Graphic::AGraphic::getInputMap(void) const
{
    return _inputMap;
}

// Refresh

void Graphic::AGraphic::refreshInputMap(void)
{
    for (GraphicClientProtocol::WindowId i = 0; i < GRAPHIC_WINDOWID_MAX; i++)
        refreshInputMapWindowId(i);
}

void Graphic::AGraphic::refreshInputMapWindowId(GraphicClientProtocol::WindowId const windowId)
{
    if (!_inputMap) return;
    auto defaultWindowInputMap = _inputMap->window.find(windowId);

    if (defaultWindowInputMap == _inputMap->window.end()) {
        _inputMap->window.insert({windowId, Input::InputMapWindow()});
        defaultWindowInputMap = _inputMap->window.find(windowId);
        if (defaultWindowInputMap == _inputMap->window.end())
            return;
    }
    return refreshInputMapWindowIdOnWindow(windowId, defaultWindowInputMap->second);
}

void Graphic::AGraphic::refreshInputMapWindowIdOnWindow(GraphicClientProtocol::WindowId const _windowId, Input::InputMapWindow &_inputMapWindow)
{ }

// << WINDOW >>

// Open

void Graphic::AGraphic::openWindow(void)
{
    openWindowId(GRAPHIC_WINDOWID_DEFAULT);
}

void Graphic::AGraphic::openWindowId(GraphicClientProtocol::WindowId const _windowId)
{ }

// Close

void Graphic::AGraphic::closeWindow(void)
{
    closeWindowId(GRAPHIC_WINDOWID_DEFAULT);
}

void Graphic::AGraphic::closeWindowAll(void)
{
    for (GraphicClientProtocol::WindowId i = 0; i < GRAPHIC_WINDOWID_MAX; i++)
        closeWindowId(i);
}

void Graphic::AGraphic::closeWindowId(GraphicClientProtocol::WindowId const _windowId)
{ }

// Draw

void Graphic::AGraphic::drawWindow(void)
{
    drawWindowId(GRAPHIC_WINDOWID_DEFAULT);
}

void Graphic::AGraphic::drawWindowAll(void)
{
    for (GraphicClientProtocol::WindowId i = 0; i < GRAPHIC_WINDOWID_MAX; i++)
        drawWindowId(i);
}

void Graphic::AGraphic::drawWindowId(GraphicClientProtocol::WindowId const _windowId)
{ }

// IsOpen

bool Graphic::AGraphic::isWindowOpen(void) const
{
    return isWindowIdOpen(GRAPHIC_WINDOWID_DEFAULT);
}

bool Graphic::AGraphic::isWindowAnyOpen(void) const
{
    for (GraphicClientProtocol::WindowId i = 0; i < GRAPHIC_WINDOWID_MAX; i++)
        if (isWindowIdOpen(i))
            return true;
    return false;
}

bool Graphic::AGraphic::isWindowIdOpen(GraphicClientProtocol::WindowId const _windowId) const
{
    return false;
}

// << MEMORY >>

// Clear/Reset

void Graphic::AGraphic::reload(void)
{ }

void Graphic::AGraphic::reloadHard(void)
{
    reload();
}
