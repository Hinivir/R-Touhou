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

void Client::commandConnect()
{
    std::cout << "Connected to server" << std::endl;
}

void Client::commandDisconnect()
{
    std::cout << "Disconnected from server" << std::endl;
}

void Client::commandError()
{
    std::cout << "Error sending confirmation message to server" << std::endl;
}

void Client::commandReady()
{
    std::cout << "Ready to play" << std::endl;
}

void Client::commandFull()
{
    std::cout << "Server is full" << std::endl;
}

static const std::map<std::string, std::function<void(Client &)>> clientCommandHandler = {
    {CONNECTED, &Client::commandConnect},
    {DISCONNECTED, &Client::commandDisconnect},
    {ERROR_MSG, &Client::commandError},
    {READY, &Client::commandReady},
    {SERVER_FULL, &Client::commandFull},
};

void Client::handleMessageClient(std::string &message)
{
    std::cout << "message = " << message << std::endl;
    for (auto &command : clientCommandHandler) {
        if (message.find(command.first) != std::string::npos) {
            command.second(*this);
            break;
        }
    }
}
