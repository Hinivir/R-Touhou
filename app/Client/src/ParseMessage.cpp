/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ParseMessage.cpp
*/

#include "../include/Client.hpp"

static std::size_t SPEED = 5;

static const std::string RUN_GAME = "104: You are ready!";
static const std::string CONNECTED = "101: You are connected!";
static const std::string CONNECTED_AS = "You are connected as player ";
static const std::string CONNECTED_PLAYER = " players connected";

void Client::ParseMessage(const std::string message)
{
    if (strncmp(message.c_str(), RUN_GAME.c_str(), RUN_GAME.length()) == 0 && !this->inGame) {
        std::cout << "Game is running" << std::endl;
        this->inGame = true;
        std::thread gameThread([&]() { this->runGame(); });
        gameThread.detach();
    }
    if (strncmp(message.c_str(), RUN_GAME.c_str(), RUN_GAME.length()) == 0) {
        this->player.isConnected = true;
        std::cout << "You are connected!!!!!" << std::endl;
    }
    if (message.substr(0, CONNECTED_AS.size()) == CONNECTED_AS) {
        this->player.player_number = std::stoi(message.substr(CONNECTED_AS.size(), 1));
        std::cout << "You are player " << this->player.player_number << std::endl;
    }
    if (strncmp(message.c_str(), CONNECTED_PLAYER.c_str(), 1) == 0)
        this->other_player.player_number = std::stoi(message.substr(0, 1));
    if (this->inGame)
        this->handleMessageInGame(message);
}
