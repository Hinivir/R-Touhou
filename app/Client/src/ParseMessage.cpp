/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ParseMessage.cpp
*/

#include "../include/Client.hpp"

static const std::string RUN_GAME = "Game is ready! Let the fun begin!";//strcmp
static const std::string CONNECTED = "101:You are connected!";//strcmp
static const std::string CONNECTED_AS = "You are connected as player ";//strncmp
static const std::string CONNECTED_PLAYER = " players connected";

void Client::ParseMessage(const std::string message)
{
    if (message == RUN_GAME && !this->inGame) {
        this->inGame = true;
        std::thread gameThread([&]() { this->runGame(); });
        gameThread.detach();
    }
    if (message == CONNECTED)
        this->player.isConnected = true;
    if (message.substr(0, CONNECTED_AS.size()) == CONNECTED_AS)
        this->player.player_number = std::stoi(message.substr(CONNECTED_AS.size(), 1));
    if (strncmp(message.c_str(), CONNECTED_PLAYER.c_str(), 1) == 0)
        this->other_player.player_number = std::stoi(message.substr(0, 1));
    if (this->inGame)
        this->handleMessageInGame(message);
}
