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
    void refreshInputMapWindowIdOnWindow(Graphic::WindowId const windowId, Input::InputMapWindow &inputMapWindow) override;
    // << WINDOW >>
    // Open
    void openWindowId(Graphic::WindowId const windowId) override;
    // Close
    void closeWindowId(Graphic::WindowId const windowId) override;
    // Draw
    void drawWindowId(Graphic::WindowId const windowId) override;
    // IsOpen
    bool isWindowIdOpen(Graphic::WindowId const windowId) const override;
    // << MEMORY >>
    // Clear/Reset
    void reloadHard(void) override;
private:
    sf::RenderWindow _renderWindow;
};

}
