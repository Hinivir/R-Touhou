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

const std::map<std::string, std::function<void(Server&, const asio::ip::udp::endpoint&, const std::array<char, 2048>&, size_t)>> Server::commandHandler = {
    {"connect\n", &Server::handleConnect},
    {"ready\n", &Server::handleReady}
};

void Server::sendMessageToAllClients(const std::string& message, const asio::ip::udp::endpoint& sender) {
    std::stringstream ss;

    for (const auto& client : clients)
        if (client != sender) {
            ss << playerNumberMap.at(sender);
            sendMessage("Player " + ss.str() + ": " + message,  client, false);
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
    this->receiveMessage(false);
    std::string message;

    //auto it = commandHandler.find(this->getBuffer().data());
    if (!handleCommand(this->getBuffer(), bytesReceived)) {
        message = std::string(this->getBuffer().begin(), this->getBuffer().begin() + bytesReceived);
        sendMessageToAllClients(message, senderEndpoint);
    }
}

std::map<std::string, std::string> CommandMap = {
    {"connect\n", "Client connected"},
    {"ready\n", "Client ready"}
};


bool Server::handleCommand(std::array<char, 2048> buffer, size_t size)
{
    std::cout << "Command received: " << buffer.data() << std::endl;
    for (std::size_t i = 0; i < CommandMap.size(); i++) {
        if (CommandMap.find(buffer.data()) != CommandMap.end()) {//strcmp
            std::cout << "Command found: " << CommandMap[buffer.data()] << std::endl;
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
