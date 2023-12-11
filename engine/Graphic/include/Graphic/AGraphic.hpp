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
    // << INPUTS >>
    // InputMap
    void setInputMap(Input::InputMapRef const &inputMap) final;
    Input::InputMapRef getInputMap(void) const final;
    // Refresh
    void refreshInputMap(void) override;
    void refreshInputMapWindowId(Graphic::WindowId const windowId) final;
    void refreshInputMapWindowIdOnWindow(Graphic::WindowId const windowId, Input::InputMapWindow &inputMapWindow) override;
    // << WINDOW >>
    // Open
    void openWindow(void) final;
    void openWindowId(Graphic::WindowId const windowId) override;
    // Close
    void closeWindow(void) final;
    void closeWindowAll(void) override;
    void closeWindowId(Graphic::WindowId const windowId) override;
    // Draw
    void drawWindow(void) final;
    void drawWindowAll(void) override;
    void drawWindowId(Graphic::WindowId const windowId) override;
    // IsOpen
    bool isWindowOpen(void) const final;
    bool isWindowAnyOpen(void) const override;
    bool isWindowIdOpen(Graphic::WindowId const windowId) const override;
protected:
    // InputMap
    Input::InputMapRef _inputMap = nullptr;
};

}
