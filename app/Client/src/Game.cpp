/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "../include/Client.hpp"

void Client::initGame(std::string const gamename)
{
    if (gamename == "R-type") {
        std::cout << "R-type game init" << std::endl;
        //get the init function from the ecs
    }
    this->inGame = true;
    this->runGame();
}

void Client::runGame()
{
    //le thread de reception marche déjà, faut juste le modifier
    while (1) {
//        system.backgroundParallax(registry);
//        system.controlSystem(registry);
//        system.spriteSystem(registry);
//        system.attackSystem(registry);
//        system.drawSystem(registry, window);
//        system.deleteEntitiesSystem(registry);
    }
}
