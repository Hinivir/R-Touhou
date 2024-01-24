/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "../include/Client.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Graphics/Color.hpp>
#include "SparseArray.hpp"



Client::Client(const std::string ip, const std::string port): ANetwork::ANetwork(ip, port)
{
    try {
        this->serverEndpoint = asio::ip::udp::endpoint(asio::ip::make_address_v4(ip), std::stoi(port));
        this->socket.open(asio::ip::udp::v4());
        this->sendMessage("connect\n", this->serverEndpoint, false);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

Client::~Client()
{
    this->socket.close();
}

static const std::map<std::string, std::string> clientCommandHandler = {
    {CONNECTED, "command connect"},
    {DISCONNECTED, "command disconnect"},
    {ERROR_MSG, "command error"},
    {READY, "command ready"},
    {SERVER_FULL, "command full"},
};

void Client::handleMessageClient(std::string &message)
{
    std::cout << "message = " << message << std::endl;
    for (auto &command : clientCommandHandler) {
        if (message.find(command.first) != std::string::npos) {
            std::cout << "command = " << command.second << std::endl;
            break;
        }
    }
}
