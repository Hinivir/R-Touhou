/*
** EPITECH PROJECT, 2023
** engine/Graphic/include/AGraphic.hpp
** File description:
** -
*/

/// @file
/// @brief Default implemenation of AGraphic

#pragma once
#include <memory>
#include "Graphic/IGraphic.hpp"

namespace Graphic {

class AGraphic : public Graphic::IGraphic
{
public:
    // Open
    void openWindow(void) override;
    void openWindowId(Graphic::WindowId const windowId) override;
    // Close
    void closeWindow(void) override;
    void closeWindowAll(void) override;
    void closeWindowId(Graphic::WindowId const windowId) override;
    // Draw
    void drawWindow(void) override;
    void drawWindowAll(void) override;
    void drawWindowId(Graphic::WindowId const windowId) override;
    // IsOpen
    bool isWindowOpen(void) const override;
    bool isWindowAnyOpen(void) const override;
    bool isWindowIdOpen(Graphic::WindowId const windowId) const override;
};

}
