/*
** EPITECH PROJECT, 2023
** engine/Graphic/include/IGraphic.hpp
** File description:
** -
*/

/// @file
/// @brief Interfaces for graphic libraries

#pragma once
#include <cstddef>

#define GRAPHIC_WINDOWID_DEFAULT 0

namespace Graphic {

using WindowId = size_t;

class IGraphic
{
public:
    virtual ~IGraphic() = default;
public:
    // Open
    virtual void openWindow(void) = 0;
    virtual void openWindowId(Graphic::WindowId const windowId) = 0;
    // Close
    virtual void closeWindow(void) = 0;
    virtual void closeWindowAll(void) = 0;
    virtual void closeWindowId(Graphic::WindowId const windowId) = 0;
    // Draw
    virtual void drawWindow(void) = 0;
    virtual void drawWindowAll(void) = 0;
    virtual void drawWindowId(Graphic::WindowId const windowId) = 0;
    // IsOpen
    virtual bool isWindowOpen(void) const = 0;
    virtual bool isWindowAnyOpen(void) const = 0;
    virtual bool isWindowIdOpen(Graphic::WindowId const windowId) const = 0;
};

}
