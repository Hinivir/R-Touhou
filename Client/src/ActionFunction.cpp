/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ActionFunction.cpp
*/

#include "../include/Client.hpp"
/*
static std::size_t SPEED = 5;

void Client::upFunction(std::size_t player_number)
{
    bool isReceived = player_number != this->player.player_number;

    if (isReceived) {
        for (auto &p : this->players) {
            if (p.player_number == player_number) {
                std::cout << p.pos_y << std::endl;
                p.pos_y -= SPEED;
                std::cout << p.pos_y << std::endl;
                break;
            }
        }
    } else {
        this->player.pos_y -= SPEED;
        this->sendMessage("UP");
    }
}

void Client::downFunction(std::size_t player_number)
{
    bool isReceived = player_number != this->player.player_number;

    if (isReceived) {
        for (auto &p : this->players) {
            if (p.player_number == player_number) {
                p.pos_y += SPEED;
                break;
            }
        }
    } else {
        this->player.pos_y += SPEED;
        this->sendMessage("DOWN");
    }
}

void Client::leftFunction(std::size_t player_number)
{
    bool isReceived = player_number != this->player.player_number;

    if (isReceived) {
        for (auto &p : this->players) {
            if (p.player_number == player_number) {
                p.pos_x -= SPEED;
                break;
            }
        }
    } else {
        this->player.pos_x -= SPEED;
        this->sendMessage("LEFT");
    }
}

void Client::rightFunction(std::size_t player_number)
{
    bool isReceived = player_number != this->player.player_number;

    if (isReceived) {
        for (auto &p : this->players) {
            std::cout << p.player_number << std::endl;
            if (p.player_number == player_number) {
                p.pos_x += SPEED;
                break;
            }
        }
    } else {
        this->player.pos_x += SPEED;
        this->sendMessage("RIGHT");
    }
}

void Client::actionFunction(std::size_t player_number)
{
    bool isReceived = player_number != this->player.player_number;

    if (isReceived) {
        std::cout << "fACTION" << std::endl;
    } else {
        std::cout << "ACTION" << std::endl;
    }
}

void Client::quitFunction(std::size_t player_number)
{
    bool isReceived = player_number != this->player.player_number;

    if (isReceived) {
        std::cout << "fQUIT" << std::endl;
    } else {
        std::cout << "QUIT" << std::endl;
    }
}
*/
