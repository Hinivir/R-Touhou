/*
** EPITECH PROJECT, 2023
** libraries/SFML/src/Instance.cpp
** File description:
** -
*/

#include <iostream>
#include <SFML/Window/Event.hpp>
#include "LibrarySFML/Conversion.hpp"
#include "LibrarySFML/Inputs.hpp"
#include "LibrarySFML/Instance.hpp"

// Constructor and Destructor

LibrarySFML::Instance::Instance(void)
{ }

LibrarySFML::Instance::~Instance()
{
    closeWindowAll();
}

// << INPUTS >>

// Refresh

void LibrarySFML::Instance::refreshInputMapWindowIdOnWindow(GraphicClientProtocol::WindowId const windowId, Input::InputMapWindow &inputMapWindow)
{
    inputMapWindow.clearEvent();
    if (!_renderWindow[windowId].isOpen()) return;
    sf::Event event;

    while (_renderWindow[windowId].pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::Closed:
            inputMapWindow.setEvent(Input::InputMapEvent::CLOSE, true);
            break;
        default:
            break;
        }
    }
    inputMapWindow.prepareInputs();
    for (std::size_t i = 0; i < KEYBOARD_TO_INPUT_LIST_LENGTH; i++) {
        if (sf::Keyboard::isKeyPressed(KEYBOARD_TO_INPUT_LIST[i].keyboard))
            inputMapWindow << KEYBOARD_TO_INPUT_LIST[i].input;
    }
    inputMapWindow.confirmInputs();
}

// << WINDOW >>

// Open

static std::string openWindowIdGetWindowName(GraphicClientProtocol::WindowId const windowId)
{
    if (windowId == GRAPHIC_WINDOWID_DEFAULT)
        return "L-Type";
    return "L-Type+";
}

void LibrarySFML::Instance::openWindowId(GraphicClientProtocol::WindowId const windowId)
{
    closeWindowId(windowId);
    _renderWindow[windowId].create(sf::VideoMode::getDesktopMode(), openWindowIdGetWindowName(windowId), sf::Style::Resize | sf::Style::Close);
    if (!_renderWindow[windowId].isOpen())
        return;
    _renderWindow[windowId].setFramerateLimit(60);
}

// Close

void LibrarySFML::Instance::closeWindowId(GraphicClientProtocol::WindowId const windowId)
{
    if (_renderWindow[windowId].isOpen())
        _renderWindow[windowId].close();
}

// Draw

void LibrarySFML::Instance::_drawWindowIdOnLayerSprites(GraphicClientProtocol::WindowId const windowId, GraphicClientProtocol::Layer::Sprites &layer)
{
    auto content = layer.content;
    auto iterator = layer.content.begin();
    bool filepathLoaded;
    sf::Vector2f position;
    std::size_t filepathLoadedAt;
    std::string filepath;

    while (iterator != layer.content.end()) {
        LType::EntityInstance entity = (*iterator).lock();
        if (!entity) {
            iterator = layer.content.erase(iterator);
            continue;
        }
        LType::Sprite &sprite = entity->getSprite();
        if (sprite.hidden)
            goto drawWindowIdOnLayerSpritesEndOfLoop;
        filepath = sprite.filepath;
        if (filepath.empty())
            goto drawWindowIdOnLayerSpritesEndOfLoop;
        filepathLoaded = false;
        for (std::size_t i = 0; i < _textureKeys.size(); i++) {
            if (_textureKeys[i] != filepath)
                continue;
            filepathLoaded = true;
            filepathLoadedAt = i;
            break;
        }
        if (!filepathLoaded) {
            std::cout << "Loading " << filepath << std::endl;
            _textureKeys.push_back(filepath);
            _textureValue.push_back(sf::Texture());
            if (_textureValue.back().loadFromFile(filepath)) {
                filepathLoaded = true;
                filepathLoadedAt = _textureValue.size() - 1;
            }
        }
        if (filepathLoaded) {
            _generalSprite.setTexture(_textureValue[filepathLoadedAt]);
            _generalSprite.setColor(LibrarySFML::colorConversion(sprite.modulate));
            _generalSprite.setScale(sf::Vector2f((sprite.flipH ? -1.0 : 1.0), (sprite.flipV ? -1.0 : 1.0)));
            //
            position.x = entity->getPosition().x;
            position.y = entity->getPosition().y;
            if (sprite.center) {
                position.x -= sf::Vector2f(_textureValue[filepathLoadedAt].getSize()).x * 0.5 * _generalSprite.getScale().x;
                position.y -= sf::Vector2f(_textureValue[filepathLoadedAt].getSize()).y * 0.5 * _generalSprite.getScale().y;
            }
            _generalSprite.setPosition(position);
            //
            _renderWindow[windowId].draw(_generalSprite);
        }
        drawWindowIdOnLayerSpritesEndOfLoop:
        iterator++;
    }
}

void LibrarySFML::Instance::drawWindowIdOnStack(GraphicClientProtocol::WindowId const windowId, GraphicClientProtocol::Layer::Stack &stack)
{
    if (!_renderWindow[windowId].isOpen())
        return;
    _renderWindow[windowId].clear(sf::Color::Black);
    for (auto &layer: stack) {
        switch (layer.type)
        {
        case GraphicClientProtocol::Layer::LayerType::COLOR:
            _renderWindow[windowId].clear(LibrarySFML::colorConversion(layer.value.color.color));
            break;
        case GraphicClientProtocol::Layer::LayerType::SPRITES:
            _drawWindowIdOnLayerSprites(windowId, layer.value.sprites);
        default:
            break;
        }
    }
    _renderWindow[windowId].display();
}

// IsOpen

bool LibrarySFML::Instance::isWindowIdOpen(GraphicClientProtocol::WindowId const windowId) const
{
    return _renderWindow[windowId].isOpen();
}

// << MEMORY >>

// Clear/Reset

void LibrarySFML::Instance::reload(void)
{
    _textureKeys.clear();
    _textureValue.clear();
}

void LibrarySFML::Instance::reloadHard(void)
{
    closeWindowAll();
    reload();
    openWindow();
}
