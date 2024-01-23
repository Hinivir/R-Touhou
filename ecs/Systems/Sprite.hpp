/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Systems/Sprite.hpp
*/

#ifndef GAME_ENGINE_SYSTEMS_SPRITE_HPP
#define GAME_ENGINE_SYSTEMS_SPRITE_HPP

#include "Components/Size.hpp"
#include "Components/Sprite.hpp"
#include "Macros/Systems.hpp"

namespace GameEngine {

namespace System {

void sprite(GameEngine::Registry &r)
{
    EXTRACT_COMPONENT(GameEngine::Sprite, sprites);
    EXTRACT_COMPONENT_CONST(GameEngine::Size, sizes);

    for (size_t i = 0; i < sprites.size(); ++i) {
        if (std::find(r.garbageEntities.begin(), r.garbageEntities.end(), i) != r.garbageEntities.end())
            continue;
        // Sprite - Continues if sprite is undefined or if it has no path
        FROM_COMPONENT_TO_VARIABLE(sprites, i, spriteComponent, hasSprite);
        if (!hasSprite)
            continue;
        GameEngine::Sprite &sprite = spriteComponent.value();
        std::string const &path = sprite.path;
        if (path == "")
            continue;

        sprite.texture.loadFromFile(sprite.path);
        sprite.sprite.setTexture(sprite.texture);

        // Size
        FROM_COMPONENT_TO_VARIABLE_CONST(sizes, i, size, hasSize);
        if (hasSize)
            sprite.sprite.setScale(size.value().width / sprite.texture.getSize().x,
                size.value().height / sprite.texture.getSize().y);
    }
}

}

}


#endif