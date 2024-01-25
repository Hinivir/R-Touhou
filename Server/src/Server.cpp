/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server(const std::string &ip, const std::string &port) : ANetwork::ANetwork(ip, port)
{
    _port = std::stoi(port);

    try {
        socket.close();
        socket.open(asio::ip::udp::v4());
        socket.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), _port));
    } catch (std::exception const &e) {
        std::cerr << "ERROR" << e.what() << std::endl;
        throw;
    }
}

Server::~Server(void)
{
    socket.close();
}

void Server::sendMessageToAllClients(const std::string& message) {
    std::stringstream ss;

    std::cout << clients.size() << std::endl;
    for (const auto& client : clients) {
        if (client != senderEndpoint) {
            ss << playerNumberMap.at(senderEndpoint);
            sendMessage<std::string>("Player " + ss.str() + ": " + getBuffer().data() , client, false);
        }
    }
}

void Server::manageServer()
{
    std::cout << "Waiting for clients..." << std::endl;
    try {
        while (1) {
            receiveMessage<std::string>(false);
            if (isMessage)
                sendMessageToAllClients(getBuffer().data());
            buffer.fill(0);
        }
    } catch (std::exception const &e) {
        std::cerr << "Error in manageServer: " << e.what() << std::endl;
    }
}

void Server::handleMessage() {}

void Server::commandConnect() {
    std::stringstream ss;

    if (std::find(clients.begin(), clients.end(), senderEndpoint) == clients.end()) {
        if (clients.size() < maxPlayers) {
            playerNumber++;
            playerNumberMap[senderEndpoint] = playerNumber;
            ss << playerNumber;
            sendMessage(CONNECTED, senderEndpoint, false);
            sendMessage("You are player " + ss.str() + "!\n", senderEndpoint, false);
            clients.push_back(senderEndpoint);
        }
    }
}
void Server::commandDisconnect() {
    sendMessage(DISCONNECTED, senderEndpoint, false);
}

void Server::commandError() {
    sendMessage(ERROR_MSG, senderEndpoint, false);
}

void Server::commandReady() {
    sendMessage(READY, senderEndpoint, false);
}
void Server::commandFull() {
    sendMessage(SERVER_FULL, senderEndpoint, false);
}
