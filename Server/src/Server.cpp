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

void Server::sendMessageToAllClients(const std::string& message, const asio::ip::udp::endpoint& sender) {
    std::stringstream ss;

    std::cout << clients.size() << std::endl;
    for (const auto& client : clients) {
        if (client != sender) {
            std::cout << client << "|" << sender << std::endl;
            ss << playerNumberMap.at(sender);
            sendMessage<std::string>("Player " + ss.str() + ": " + getBuffer().data() , client, false);
        }
    }
}

void Server::handleConnect(const asio::ip::udp::endpoint &endpoint, const std::array<char, 2048> &buffer, size_t size)
{
    std::string message(buffer.data(), size);
    if (message == "connect\n")
        verifConnected();
}

void Server::handleReady(const asio::ip::udp::endpoint &endpoint, const std::array<char, 2048> &buffer, size_t size)
{
    std::string message(buffer.data(), size);
    std::cout << message << std::endl;
    if (message == "ready\n")
        sendMessage(READY, senderEndpoint, false);
}

void Server::verifConnected()
{
    std::stringstream ss;

    if (std::find(clients.begin(), clients.end(), senderEndpoint) == clients.end()) {
        if (clients.size() < maxPlayers) {
            playerNumber++;
            playerNumberMap[senderEndpoint] = playerNumber;
            std::cout << "Client connected: " << senderEndpoint << " - Assigned Player " << playerNumber << std::endl;
            ss << playerNumber;
            sendMessage(CONNECTED, senderEndpoint, false);
            sendMessage("You are player " + ss.str() + "!\n", senderEndpoint, false);
            clients.push_back(senderEndpoint);
        }
    }
}

void Server::manageMessage()
{
    this->receiveMessage<std::string>(false);

    if (handleCommand(this->getBuffer(), bytesReceived)) {
        std::string message(this->getBuffer().data(), bytesReceived);
        sendMessageToAllClients(message, senderEndpoint);
    } else {
        std::string message(this->getBuffer().data(), bytesReceived);
        sendMessageToAllClients(message, senderEndpoint);
    }
}

std::map<std::string, std::string> CommandMap = {
    {"connect\n", CONNECTED},
    {"ready\n", READY}
};


bool Server::handleCommand(std::array<char, 2048> buffer, size_t size)
{
    std::string message(buffer.data(), size);

    for (auto it = CommandMap.begin(); it != CommandMap.end(); it++) {
        if (it->first == getBuffer().data()) {
            std::cout << "Command received: " << buffer.data() << std::endl;
            sendMessage(it->second, senderEndpoint, false);
            return true;
        }
    }
    return false;
}

void Server::manageServer()
{
    std::cout << "Waiting for clients..." << std::endl;
    try {
        while (1) {
            manageMessage();
            buffer.fill(0);
        }
    } catch (std::exception const &e) {
        std::cerr << "Error in manageServer: " << e.what() << std::endl;
    }
}

void Server::handleMessage() {}
void Server::commandConnect() {}
void Server::commandDisconnect() {}
void Server::commandError() {}
void Server::commandReady() {}
void Server::commandFull() {}
