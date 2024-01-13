/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ParseMessage.cpp
*/

#include "../include/Client.hpp"

static std::size_t SPEED = 5;

static const std::string CONNECTED = "101: You are connected!";//
static const std::string DISCONNECTED = "103: You are disconnected!";
static const std::string RUN_GAME = "104: You are ready!";//
static const std::string SERVER_FULL = "105: Server is full!";

static const std::string CONNECTED_AS = "You are connected as player ";//
static const std::string CONNECTED_PLAYER = " players connected";//
static const std::string NEW_USER = "New user connected";

void Client::parseMessage(const std::string message)
{
    //ready
    if (strncmp(message.c_str(), RUN_GAME.c_str(), RUN_GAME.length()) == 0 && !this->inGame) {
        this->inGame = true;
        std::thread gameThread([&]() { this->runGame("R-type"); });
        gameThread.detach();
    }
    //player number
    if (message.substr(0, CONNECTED_AS.size()) == CONNECTED_AS)
        this->player.player_number = std::stoi(message.substr(CONNECTED_AS.size(), 1));
    //connected player
    std::string messageConnected = message.substr(1, CONNECTED.length());
    if (strncmp(messageConnected.c_str(), CONNECTED_PLAYER.c_str(), CONNECTED_PLAYER.length()) == 0)
        this->addUsersWhenConnected(message.substr(0, 1));
    //new user
    std::string messageNewPlayer = message.substr(3, CONNECTED_PLAYER.length());
    if (strncmp(messageNewPlayer.c_str(), NEW_USER.c_str(), NEW_USER.length()) == 0)
        this->addNewUser(message.substr(NEW_USER.length(), 1));
}

void Client::addUsersWhenConnected(const std::string& message)
{
    std::size_t nb_user = std::stoi(message.substr(0, 1));

    while (nb_user != 0) {
        std::size_t player_number = nb_user;
        std::size_t pos_x = 50;
        std::size_t pos_y = nb_user * 100 + 50;
        player_t player = {player_number, pos_x, pos_y, true};
        this->players.push_back(player);
        nb_user--;
    }
}

void Client::addNewUser(const std::string& message)
{
    std::size_t player_number = this->players.size() + 2;
    std::size_t pos_x = 50;
    std::size_t pos_y = player_number * 100 + 50;
    player_t player = {player_number, pos_x, pos_y, true};
    this->players.push_back(player);
}
