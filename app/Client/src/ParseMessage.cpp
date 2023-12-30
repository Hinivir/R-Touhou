/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ParseMessage.cpp
*/

#include "../include/Client.hpp"

static const std::string RUN_GAME = "Game is ready! Let the fun begin!";
static const std::string CONNECTED = "101:You are connected!";
static const std::string CONNECTED_AS = "You are connected as player ";

void Client::ParseMessage(const std::string message)
{
    if (message == RUN_GAME && !this->inGame) {
        this->inGame = true;
        std::thread gameThread([&]() { this->runGame(); });
        gameThread.detach();
    }
    if (this->inGame)
        this->handleMessageInGame(message);
}
