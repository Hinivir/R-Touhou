/*
** EPITECH PROJECT, 2023
** libraries/SFML/include/LibrarySFML/Instance.hpp
** File description:
** -
*/

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Graphic/AGraphic.hpp"

namespace LibrarySFML {

class Instance : public Graphic::AGraphic
{
public:
    Instance(void);
    ~Instance();
public:
    // << INPUTS >>
    // Refresh
    void refreshInputMapWindowIdOnWindow(GraphicClientProtocol::WindowId const windowId, Input::InputMapWindow &inputMapWindow) override;
    // << WINDOW >>
    // Open
    void openWindowId(GraphicClientProtocol::WindowId const windowId) override;
    // Close
    void closeWindowId(GraphicClientProtocol::WindowId const windowId) override;
    // Draw
    void drawWindowId(GraphicClientProtocol::WindowId const windowId) override;
    // IsOpen
    bool isWindowIdOpen(GraphicClientProtocol::WindowId const windowId) const override;
    // << MEMORY >>
    // Clear/Reset
    void reloadHard(void) override;
private:
    sf::RenderWindow _renderWindow;
};

}
