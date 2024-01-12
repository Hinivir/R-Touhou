/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Game.cpp
*/

#include "../include/Server.hpp"

void Server::initGame(std::string const gamename)
{
    if (gamename == "R-type") {
        std::cout << "R-type game init" << std::endl;
        //get the init function from the ecs
    }
    this->inGame = true;
    this->runGame();
}

void Server::runGame()
{
    //le thread de reception marche déjà, faut juste le modifier
    while (1) {
//        system.attackSystem(registry);
//        system.movementSystem(registry);
//        system.collisionSystem(registry, testscore);
//        system.deleteEntitiesSystem(registry);
    }
}
