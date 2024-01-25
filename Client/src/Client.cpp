/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "Systems.hpp"
#include "Macros/ForEach.hpp"
#include "Init.hpp"

Client::Client(const std::string ip, const std::string port) : ANetwork::ANetwork(ip, port)
{
    try {
        this->serverEndpoint = asio::ip::udp::endpoint(asio::ip::make_address_v4(ip), std::stoi(port));
        this->socket.open(asio::ip::udp::v4());
        this->sendMessage<std::string>("connect\n", this->serverEndpoint, false);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

Client::~Client() { this->socket.close(); }

void Client::commandConnect() { std::cout << "Connected to server" << std::endl; }

void Client::commandDisconnect() { std::cout << "Disconnected from server" << std::endl; }

void Client::commandError() { std::cout << "Error sending confirmation message to server" << std::endl; }

void Client::commandReady() { std::cout << "Ready to play" << std::endl; }

void Client::commandFull() { std::cout << "Server is full" << std::endl; }

void Client::manageMessage(const std::type_info &info) {
    if (info == typeid(std::string))
        manageMessageString(getBuffer().data());
    else
        std::cout << "something else" << std::endl;
}

void Client::manageMessageString(const std::string message) {
    const std::string youArePlayer = "You are player ";

    if (strncmp(youArePlayer.c_str(), message.c_str(), youArePlayer.size()) == 0)
        this->playerNumber = std::stoi(message.substr(youArePlayer.size(), 1));
    else if (strcmp(NEW_CLIENT, message.c_str()) == 0)
        playerNumber++;
    std::cout << message << std::endl;
    std::cout << playerNumber << std::endl;
}
