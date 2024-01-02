/*
** EPITECH PROJECT, 2023
** libraries/SFML/include/LibrarySFML/Instance.hpp
** File description:
** -
*/

#pragma once
#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Graphic/AGraphic.hpp"
#include "GraphicClientProtocol/Layer/Sprites.hpp"

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
    void drawWindowIdOnStack(GraphicClientProtocol::WindowId const windowId, GraphicClientProtocol::Layer::Stack &stack) override;
    // IsOpen
    bool isWindowIdOpen(GraphicClientProtocol::WindowId const windowId) const override;
    // << MEMORY >>
    // Clear/Reset
    void reload(void) override;
    void reloadHard(void) override;
protected:
    /// @brief Section of drawWindowIdOnStack maganing GraphicClientProtocol::Layer::Sprites
    /// @param windowId (GraphicClientProtocol::WindowId) Id of the window used for display
    /// @param layer (GraphicClientProtocol::Layer::Sprites) Layer used
    void _drawWindowIdOnLayerSprites(GraphicClientProtocol::WindowId const windowId, GraphicClientProtocol::Layer::Sprites &layer);
protected:
    sf::RectangleShape _areaShape;
    sf::RenderWindow _renderWindow[GRAPHIC_WINDOWID_MAX];
    std::vector<std::string> _textureKeys;
    std::vector<sf::Texture> _textureValue;
    sf::Sprite _generalSprite;
};

}
