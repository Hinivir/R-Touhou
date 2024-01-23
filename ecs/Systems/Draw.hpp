/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Systems/Draw.hpp
*/

#ifndef GAME_ENGINE_SYSTEMS_DRAW_HPP
#define GAME_ENGINE_SYSTEMS_DRAW_HPP

#include "Components/Color.hpp"
#include "Components/Drawable.hpp"
#include "Components/ZIndex.hpp"
#include "Components/Outline.Hpp"
#include "Components/Position.hpp"
#include "Components/Sprite.hpp"
#include "Components/SpriteTextureAnimation.hpp"
#include "Components/SpriteTextureRect.hpp"
#include "Components/Text.hpp"
#include "Components/ZIndex.hpp"
#include "Macros/Systems.hpp"

namespace GameEngine {

namespace System {

void draw(GameEngine::Registry &REGISTRY_DEFAULT_NAME, sf::RenderWindow &window)
{
    EXTRACT_COMPONENT_CONST(GameEngine::Drawable, drawables);
    EXTRACT_COMPONENT_CONST(GameEngine::Position, positions);
    EXTRACT_COMPONENT(GameEngine::Sprite, sprites);
    EXTRACT_COMPONENT_CONST(GameEngine::Color, colors);
    EXTRACT_COMPONENT_CONST(GameEngine::ZIndex, zIndexes);
    EXTRACT_COMPONENT_CONST(GameEngine::SpriteTextureAnimation, spriteTextureAnimations);
    EXTRACT_COMPONENT_CONST(GameEngine::SpriteTextureRect, spriteTextureRects);
    EXTRACT_COMPONENT(GameEngine::Text, texts);
    EXTRACT_COMPONENT_CONST(GameEngine::Outline, outlines);
    GameEngine::ZIndexValue lowestZIndex = GAME_ENGINE_Z_INDEX_VALUE_LOWEST_VALUE;
    GameEngine::ZIndexValue currentZIndex;

    do {
        currentZIndex = lowestZIndex;
        for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i) {
            if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
                continue;
            // Drawable - Continues if drawable is undefined or not visible
            FROM_COMPONENT_TO_VARIABLE_CONST(drawables, i, drawable, hasDrawable);
            if (!hasDrawable || !drawable.value().isVisible)
                continue;

            // ZIndex - Continues if (zIndex != currentZIndex)
            FROM_COMPONENT_TO_VARIABLE_CONST(zIndexes, i, zIndexComponent, hasZIndex);
            GameEngine::ZIndexValue const zIndex =
                hasZIndex ? zIndexComponent.value().zIndex : GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE;
            if (zIndex < currentZIndex)
                continue;
            if (zIndex != currentZIndex) {
                if (lowestZIndex == currentZIndex || zIndex < lowestZIndex)
                    lowestZIndex = zIndex;
                continue;
            }

            // Color
            FROM_COMPONENT_TO_VARIABLE_CONST(colors, i, colorComponent, hasColor);
            GameEngine::Color const color = hasColor ? colorComponent.value() : GameEngine::Color();
            // Outline
            FROM_COMPONENT_TO_VARIABLE_CONST(outlines, i, outlineComponent, hasOutline);
            GameEngine::Outline const &outline = hasOutline ? outlineComponent.value() : GameEngine::Outline();
            // Position
            FROM_COMPONENT_TO_VARIABLE_CONST(positions, i, positionComponent, hasPosition);
            GameEngine::Position const position =
                hasPosition ? positionComponent.value() : GameEngine::Position({0.0, 0.0});
            // Sprite
            FROM_COMPONENT_TO_VARIABLE(sprites, i, spriteComponent, hasSprite);
            // SpriteTextureAnimation
            FROM_COMPONENT_TO_VARIABLE_CONST(
                spriteTextureAnimations, i, spriteTextureAnimationComponent, hasSpriteTextureAnimation);
            GameEngine::SpriteTextureAnimation const spriteTextureAnimation =
                hasSpriteTextureAnimation ? spriteTextureAnimationComponent.value()
                                          : GameEngine::SpriteTextureAnimation();
            // SpriteTextureRects
            FROM_COMPONENT_TO_VARIABLE_CONST(
                spriteTextureRects, i, spriteTextureRectComponent, hasSpriteTextureRect);
            GameEngine::SpriteTextureRect const spriteTextureRect =
                hasSpriteTextureRect ? spriteTextureRectComponent.value() : GameEngine::SpriteTextureRect();
            // Text
            FROM_COMPONENT_TO_VARIABLE(texts, i, textComponent, hasText);

            if (hasText) {
                GameEngine::Text &text = textComponent.value();
                if (!text.isLoaded) {
                    if (text.font.loadFromFile(text.fontPath))
                        text.text.setFont(text.font);
                    if (text.text.getFont() == nullptr) {
                        goto drawSystemEndOfHasText;
                    }
                    text.isLoaded = true;
                }
                text.text.setString(text.string);
                text.text.setPosition(position.x, position.y);
                text.text.setCharacterSize(text.fontSize);
                if (hasOutline && outline.thickness > 0) {
                    text.text.setFillColor(
                        sf::Color(outline.color.r, outline.color.g, outline.color.b, outline.color.a));
                    for (sf::Vector2f const coor : {sf::Vector2f(-outline.thickness, -outline.thickness),
                             sf::Vector2f(-outline.thickness, 0),
                             sf::Vector2f(-outline.thickness, outline.thickness),
                             sf::Vector2f(0, -outline.thickness), sf::Vector2f(0, outline.thickness),
                             sf::Vector2f(outline.thickness, -outline.thickness),
                             sf::Vector2f(outline.thickness, 0),
                             sf::Vector2f(outline.thickness, outline.thickness)}) {
                        text.text.setPosition(position.x + coor.x, position.y + coor.y);
                        window.draw(text.text);
                    }
                }
                text.text.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
                text.text.setPosition(position.x, position.y);
                window.draw(text.text);
            }
        drawSystemEndOfHasText:
            if (hasSprite) {
                // Sprite
                sf::Sprite &sprite = spriteComponent.value().sprite;

                // SpriteTextureAnimation
                FROM_COMPONENT_TO_VARIABLE_CONST(
                    spriteTextureAnimations, i, spriteTextureAnimationComponent, hasSpriteTextureAnimation);
                GameEngine::SpriteTextureAnimation const spriteTextureAnimation =
                    hasSpriteTextureAnimation ? spriteTextureAnimationComponent.value()
                                              : GameEngine::SpriteTextureAnimation();

                // SpriteTextureRects
                FROM_COMPONENT_TO_VARIABLE_CONST(
                    spriteTextureRects, i, spriteTextureRectComponent, hasSpriteTextureRect);
                GameEngine::SpriteTextureRect const spriteTextureRect =
                    hasSpriteTextureRect ? spriteTextureRectComponent.value() : GameEngine::SpriteTextureRect();

                //
                sf::Vector2u const &spriteTextureSize = spriteComponent.value().texture.getSize();
                sf::IntRect textureRect = hasSpriteTextureRect
                                              ? sf::IntRect{spriteTextureRect.left, spriteTextureRect.top,
                                                    spriteTextureRect.width, spriteTextureRect.height}
                                              : sf::IntRect{0, 0, static_cast<int>(spriteTextureSize.x),
                                                    static_cast<int>(spriteTextureSize.y)};

                if (sprite.getTexture() == nullptr)
                    continue;
                sprite.setPosition(position.x, position.y);
                if (hasColor)
                    sprite.setColor(sf::Color(color.r, color.g, color.b, color.a));
                if (hasSpriteTextureAnimation) {
                    textureRect.width /= std::max(spriteTextureAnimation.slicing.x, 1);
                    textureRect.height /= std::max(spriteTextureAnimation.slicing.y, 1);
                    textureRect.left += spriteTextureAnimation.frame.y * textureRect.width;
                    textureRect.top += spriteTextureAnimation.frame.x * textureRect.height;
                }
                if (hasSpriteTextureRect || hasSpriteTextureAnimation)
                    sprite.setTextureRect(textureRect);
                textureRect = sprite.getTextureRect();
                if (hasOutline && outline.thickness > 0) {
                    sprite.setColor(
                        sf::Color(outline.color.r, outline.color.g, outline.color.b, outline.color.a));
                    for (sf::Vector2f const coor : {sf::Vector2f(-outline.thickness, -outline.thickness),
                             sf::Vector2f(-outline.thickness, 0),
                             sf::Vector2f(-outline.thickness, outline.thickness),
                             sf::Vector2f(0, -outline.thickness), sf::Vector2f(0, outline.thickness),
                             sf::Vector2f(outline.thickness, -outline.thickness),
                             sf::Vector2f(outline.thickness, 0),
                             sf::Vector2f(outline.thickness, outline.thickness)}) {
                        sprite.setPosition(position.x + coor.x, position.y + coor.y);
                        window.draw(sprite);
                    }
                }
                sprite.setColor(sf::Color(color.r, color.g, color.b, color.a));
                sprite.setPosition(position.x, position.y);
                window.draw(sprite);
            }
        }
    } while (currentZIndex != lowestZIndex);
}

}

}


#endif