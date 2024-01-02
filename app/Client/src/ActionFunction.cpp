/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ActionFunction.cpp
*/

#include "../include/Client.hpp"

static std::size_t SPEED = 5;

//ici, on regarde si le numéro est le notre ou pas

bool Client::checkCollision(int newPosX, int newPosY, int otherPosX, int otherPosY) {
    if (std::abs(newPosX - otherPosX) < 50 && std::abs(newPosY - otherPosY) < 50)
        return true;
    return false;
}

void Client::upFunction(bool isReceived) {
    int newPosY = isReceived ? this->other_player.pos_y - SPEED : this->player.pos_y - SPEED;
    if (!checkCollision(this->player.pos_x, newPosY, this->other_player.pos_x, this->other_player.pos_y)) {
        if (isReceived) {
            this->other_player.pos_y -= SPEED;
        } else {
            this->player.pos_y -= SPEED;
            this->sendMessage("UP");
        }
    }
}

void Client::downFunction(bool isReceived) {
    int newPosY = isReceived ? this->other_player.pos_y + SPEED : this->player.pos_y + SPEED;
    if (!checkCollision(this->player.pos_x, newPosY, this->other_player.pos_x, this->other_player.pos_y)) {
        if (isReceived) {
            this->other_player.pos_y += SPEED;
        } else {
            this->player.pos_y += SPEED;
            this->sendMessage("DOWN");
        }
    }
}

void Client::leftFunction(bool isReceived) {
    int newPosX = isReceived ? this->other_player.pos_x - SPEED : this->player.pos_x - SPEED;
    if (!checkCollision(newPosX, this->player.pos_y, this->other_player.pos_x, this->other_player.pos_y)) {
        if (isReceived) {
            this->other_player.pos_x -= SPEED;
        } else {
            this->player.pos_x -= SPEED;
            this->sendMessage("LEFT");
        }
    }
}

void Client::rightFunction(bool isReceived) {
    int newPosX = isReceived ? this->other_player.pos_x + SPEED : this->player.pos_x + SPEED;
    if (!checkCollision(newPosX, this->player.pos_y, this->other_player.pos_x, this->other_player.pos_y)) {
        if (isReceived) {
            this->other_player.pos_x += SPEED;
        } else {
            this->player.pos_x += SPEED;
            this->sendMessage("RIGHT");
        }
    }
}

void Client::actionFunction(bool isReceived) {
    if (isReceived) {
        std::cout << "fACTION" << std::endl;
    } else {
        std::cout << "ACTION" << std::endl;
    }
}

void Client::quitFunction(bool isReceived) {
    if (isReceived) {
        std::cout << "fQUIT" << std::endl;
    } else {
        std::cout << "QUIT" << std::endl;
    }
}
