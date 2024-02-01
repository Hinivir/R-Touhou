/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server(const std::string &ip, const std::string &port) : ANetwork::ANetwork(ip, port), serverGame()
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

void Server::handleMessageString()
{
    std::string message = getBuffer().data();
    for (auto &command : serverCommandHandler) {
        if (message.find(command.first) != std::string::npos) {
            command.second(*this);
            return;
        }
    }
    std::cout << "Message received: " << getBuffer().data() << std::endl;
    std::stringstream ss;
    ss << playerNumberMap.at(senderEndpoint);
    std::string msg = "Player " + ss.str() + ": " + getBuffer().data();
    sendMessageStringToOtherClients(msg);
}

void Server::manageServer()
{
    std::cout << "Waiting for clients..." << std::endl;
    try {
        while (1) {
            receiveMessage(false);
            buffer.fill(0);
        }
    } catch (std::exception const &e) {
        std::cerr << "Error in manageServer: " << e.what() << std::endl;
    }
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
            sendMessage("Number of players: " + ss.str() + "\n", senderEndpoint, false);
            clients.push_back(senderEndpoint);
            sendMessageStringToOtherClients(NEW_CLIENT);
        }
    }
}

void Server::commandDisconnect() {
    sendMessage(DISCONNECTED, senderEndpoint, false);
    std::size_t idx = 0;

    for (const auto& client : clients) {
        if (client == senderEndpoint) {
            clients.erase(clients.begin() + idx);
            auto playerNumberIt = playerNumberMap.find(senderEndpoint);
            if (playerNumberIt != playerNumberMap.end()) {
                playerNumberMap.erase(playerNumberIt);
                playerNumber--;
            }
            break;
        }
        idx++;
    }
    std::cout << "connected number " << clients.size() << std::endl;
}

void Server::commandError() {
    sendMessage(ERROR_MSG, senderEndpoint, false);
}

void Server::commandReady() {
    clientsReady.push_back(senderEndpoint);
    sendMessage("Waiting other players...", senderEndpoint, false);
    sendMessage(READY, senderEndpoint, false);
    this->serverGame.init(this->playerNumber, 2048, 20);

}

void Server::commandFull() {
    sendMessage(SERVER_FULL, senderEndpoint, false);
}

void Server::commandClientDisconnect() {
    sendMessageToOtherClients(CLIENT_DISCONNECTED);
}

void Server::commandStartGame() {
    clientsSetup.push_back(senderEndpoint);
    if (clientsSetup.size() == clientsReady.size() && clientsSetup.size() == clients.size()) {
        sendMessageStringToAllClients(START_GAME);
        std::cout << "All clients are ready. Starting the game!" << std::endl;
        this->isInChat = false;
        this->isInSetup = false;
        this->isInGame = true;
        std::cout << "boolean pass" << std::endl;
        this->serverGame.setup();
        std::cout << "setup pass" << std::endl;
        handleGame();
    }
}

void Server::handleGame() {
    std::cout << "Game is starting" << std::endl;
    for (std::size_t i = serverGame.getNbPlayer(); i < serverGame.getDefaultNbEnemies() + serverGame.getNbPlayer(); i++) {
        float x = rand() % 1080 + 1920;
        float y = rand() % 1000 - 50;
        while (x < 50)
            x += 50;
        while (y < 1030)
            y += 1030;
        this->serverGame.getEnemiesPosPair().push_back(std::pair<float, float>{x, y});
    }
    std::cout << "Enemies Pos generated" << std::endl;
    serverGame.getSystemGroup().initEnemy(serverGame.getRegistry(), this->serverGame.getEnemiesPosPair());
    std::cout << "Enemies Pos set" << std::endl;
    sendMessageToAllClients<std::vector<std::pair<float, float>>>(this->serverGame.getEnemiesPosPair());
    std::cout << "Enemies Pos sent" << std::endl;
}
