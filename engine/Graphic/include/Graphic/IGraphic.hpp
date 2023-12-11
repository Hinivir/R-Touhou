/*
** EPITECH PROJECT, 2023
** engine/Graphic/include/IGraphic.hpp
** File description:
** -
*/

/// @file
/// @brief Interfaces for graphic libraries

#pragma once
#include "Graphic/WindowId.hpp"
#include "Input/InputMapRef.hpp"

#define GRAPHIC_WINDOWID_DEFAULT 0

namespace Graphic {

class IGraphic
{
public:
    virtual ~IGraphic() = default;
public:
    // << INPUTS >>
    // InputMap
    virtual void setInputMap(Input::InputMapRef const &inputMap) = 0;
    virtual Input::InputMapRef getInputMap(void) const = 0;
    // Refresh
    virtual void refreshInputMap(void) = 0;
    virtual void refreshInputMapWindowId(Graphic::WindowId const windowId) = 0;
    virtual void refreshInputMapWindowIdOnWindow(Graphic::WindowId const windowId, Input::InputMapWindow &inputMapWindow) = 0;
    // << WINDOW >>
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
