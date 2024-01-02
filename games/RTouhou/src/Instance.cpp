/*
** EPITECH PROJECT, 2023
** games/RTouhou/src/EntryPoint.cpp
** File description:
** -
*/

#include <iostream>
#include "LType/Entity.hpp"
#include "LType/Process.hpp"
#include "RTouhou/Instance.hpp"

static LTYPE_FUNCTION_PROCESS_PHYSICS(fishProcessPhysics, fish, delta)
{
    if (!fish)
        return;
    float speed = 500.0;
    float directionH = ((_game.isInputPressed(LType::InputList::RIGHT)) ? 1.0 : 0.0) - ((_game.isInputPressed(LType::InputList::LEFT)) ? 1.0 : 0.0);
    float directionV = ((_game.isInputPressed(LType::InputList::DOWN )) ? 1.0 : 0.0) - ((_game.isInputPressed(LType::InputList::UP  )) ? 1.0 : 0.0);
    if (directionH != 0) {
        fish->getSprite().flipH = _game.isInputPressed(LType::InputList::RIGHT);
        fish->getPosition().x += speed * delta * directionH;
    }
    if (directionV != 0)
        fish->getPosition().y += speed * delta * directionV;
}

static LTYPE_FUNCTION_PROCESS_GRAPHIC(fishProcessGraphic, fish, _delta)
{
//    if (fish)
//        fish->getSprite().flipH = !fish->getSprite().flipH;
}

void RTouhou::Instance::init(void)
{
    LType::EntityInstance fish = addEntity(GAME_ENTITY);

    if (fish) {
        fish->setSprite(LType::Sprite("resources/R-Touhou/graphics/Fish.png"));
        fish->getSprite().flipV = false;
        fish->getPosition().x = 100.0;
        fish->getPosition().y = 100.0;
        addFunctionProcessPhysics(fish, fishProcessPhysics);
        addFunctionProcessGraphic(fish, fishProcessGraphic);
    }
    std::cout << "Game running at " << getProcessPhysicsPerSec() << " physics per second" << std::endl;
}
