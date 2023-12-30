/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ActionFunction.cpp
*/

#include "../include/Client.hpp"

void Client::upFunction(bool isReceived) {
    if (isReceived) {
        this->other_player.pos_y -= 1;
    } else {
        this->player.pos_y -= 1;
    }
}

void Client::downFunction(bool isReceived) {
    if (isReceived) {
        this->other_player.pos_y += 1;
    } else {
        this->player.pos_y += 1;
    }
}

void Client::leftFunction(bool isReceived) {
    if (isReceived) {
        this->other_player.pos_x -= 1;
    } else {
        this->player.pos_x -= 1;
    }
}

void Client::rightFunction(bool isReceived) {
    if (isReceived) {
        this->other_player.pos_x += 1;
    } else {
        this->player.pos_x += 1;
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
