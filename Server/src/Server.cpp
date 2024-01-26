/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.cpp
*/

#include "Server.hpp"
#include "ServerGame.hpp"

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

void Server::sendMessageToAllClients(const std::string& clientMessage) {
    std::stringstream ss;

    std::cout << clients.size() << std::endl;
    for (const auto& client : clients) {
        if (client != senderEndpoint) {
            ss << playerNumberMap.at(senderEndpoint);
            if (clientMessage == NEW_CLIENT)// tmp
                sendMessage<std::string>(clientMessage, client, false);
            else
                sendMessage<std::string>("Player " + ss.str() + ": " + clientMessage , client, false);
        }
    }
}

void Server::manageServer()
{
    std::cout << "Waiting for clients..." << std::endl;
    try {
        while (1) {
            receiveMessage<std::string>(false);
            buffer.fill(0);
        }
    } catch (std::exception const &e) {
        std::cerr << "Error in manageServer: " << e.what() << std::endl;
    }
}

void Server::manageMessage(const std::type_info &info) {
    if (info == typeid(std::string))
        std::cout << "Message received: " << getBuffer().data() << std::endl;
    sendMessageToAllClients(getBuffer().data());
}

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
            sendMessageToAllClients(NEW_CLIENT);
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
    clientsReady.push_back(senderEndpoint);
    if (clientsReady.size() == clients.size()) {
        std::cout << "All clients are ready. Starting the game!" << std::endl;
        runGame();
    }
}

void Server::commandFull() {
    sendMessage(SERVER_FULL, senderEndpoint, false);
}

void Server::runGame() {
    Game::ServerGame serverGame(this->playerNumber, 2048, 30);
}
