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
    // StackMap
    void setStackMap(GraphicClientProtocol::Layer::StackMapRef const &stackMap) final;
    GraphicClientProtocol::Layer::StackMapRef getStackMap(void) const final;
    // Refresh
    void refreshInputMap(void) override;
    void refreshInputMapWindowId(GraphicClientProtocol::WindowId const windowId) final;
    void refreshInputMapWindowIdOnWindow(GraphicClientProtocol::WindowId const windowId, Input::InputMapWindow &inputMapWindow) override;
    // << WINDOW >>
    // Open
    void openWindow(void) final;
    void openWindowId(GraphicClientProtocol::WindowId const windowId) override;
    // Close
    void closeWindow(void) final;
    void closeWindowAll(void) override;
    void closeWindowId(GraphicClientProtocol::WindowId const windowId) override;
    // Draw
    void drawWindow(void) final;
    void drawWindowAll(void) override;
    void drawWindowId(GraphicClientProtocol::WindowId const windowId) override;
    void drawWindowIdOnStack(GraphicClientProtocol::WindowId const windowId, GraphicClientProtocol::Layer::Stack const &stack) override;
    // IsOpen
    bool isWindowOpen(void) const final;
    bool isWindowAnyOpen(void) const override;
    bool isWindowIdOpen(GraphicClientProtocol::WindowId const windowId) const override;
    // << MEMORY >>
    // Clear/Reset
    void reload(void) override;
    void reloadHard(void) override;
protected:
    // InputMap
    Input::InputMapRef _inputMap = nullptr;
    // StackMap
    GraphicClientProtocol::Layer::StackMapRef _stackMap = nullptr;
};

}
