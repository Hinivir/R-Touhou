/*
** EPITECH PROJECT, 2023
** engine/Graphic/src/AGraphic.cpp
** File description:
** -
*/

#include "Graphic/AGraphic.hpp"

// Open

void Graphic::AGraphic::openWindow(void)
{
    openWindowId(GRAPHIC_WINDOWID_DEFAULT);
}

void Graphic::AGraphic::openWindowId(Graphic::WindowId const _windowId)
{ }

// Close

void Graphic::AGraphic::closeWindow(void)
{
    closeWindowId(GRAPHIC_WINDOWID_DEFAULT);
}

void Graphic::AGraphic::closeWindowAll(void)
{
    closeWindow();
}

void Graphic::AGraphic::closeWindowId(Graphic::WindowId const _windowId)
{ }

// Draw

void Graphic::AGraphic::drawWindow(void)
{
    openWindowId(GRAPHIC_WINDOWID_DEFAULT);
}

void Graphic::AGraphic::drawWindowAll(void)
{
    drawWindow();
}

void Graphic::AGraphic::drawWindowId(Graphic::WindowId const _windowId)
{ }

// IsOpen

bool Graphic::AGraphic::isWindowOpen(void) const
{
    return isWindowIdOpen(GRAPHIC_WINDOWID_DEFAULT);
}

bool Graphic::AGraphic::isWindowAnyOpen(void) const
{
    return isWindowOpen();
}

bool Graphic::AGraphic::isWindowIdOpen(Graphic::WindowId const _windowId) const
{
    return false;
}
