/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include <iostream>
#include <asio.hpp>
#include "../include/Server.hpp"

Server::Server(const std::string& ip, int const port)
    : server_socket(io_service, udp::endpoint(udp::v4(), port))
{
    try {
        server_socket.close();
        server_socket.open(udp::v4());
        server_socket.bind(udp::endpoint(udp::v4(), port));
    } catch (std::exception const &e) {
        std::cerr << "ERROR" << e.what() << std::endl;
        throw;
    }
}

Server::~Server(void)
{
    closeServer();
}

void Server::closeServer(void)
{
    server_socket.close();
}

void Server::startServer(void)
{
    std::cout << "Server started" << std::endl;
    acceptClients();
}

const std::map<std::string, std::function<void(Server &, const udp::endpoint&, const std::array<char, 2048>&, size_t)>> Server::serverCommandHandler = {
    {"connect\n", &Server::handleConnect},
    {"disconnect\n", &Server::handleDisconnect},
    {"ready\n", &Server::handleReady},
    {"game init\n", &Server::handleGameInit}
};

void Server::handleGameInit(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received)
{
    std::cout << "Client has init the game: " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
    initClients.push_back(client_endpoint);
    if (initClients.size() == connectedClients.size()) {
        std::cout << "All clients are ready. Starting the game!" << std::endl;
        isChatLocked = true;
        notifyGameReady();
        runGame("R-Type");
    }
}

void Server::handleConnect(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received)
{
    std::string message(buffer.data(), bytes_received);
    if (message == "connect\n") {
        if (std::find(alreadyConnectedClients.begin(), alreadyConnectedClients.end(), client_endpoint) == alreadyConnectedClients.end()) {
            if (playerCount < maxPlayers) {
                std::string playerMessage = "You are connected as player " + std::to_string(nextPlayerNumber) + "!\n";
                playerNumberMap[client_endpoint] = nextPlayerNumber;
                nextPlayerNumber++;std::string nbPlayer = std::to_string(playerCount) + " players connected\n";
                std::string newUserMessage = "New user connected: " + client_endpoint.address().to_string() + ":" + std::to_string(client_endpoint.port()) + "\n";
                broadcastMessage(newUserMessage, newUserMessage.size(), client_endpoint);
                try {
                    server_socket.send_to(asio::buffer(CONNECTED), client_endpoint);
                    server_socket.send_to(asio::buffer(playerMessage), client_endpoint);
                    server_socket.send_to(asio::buffer(nbPlayer), client_endpoint);
                } catch (std::exception const &e) {
                    server_socket.send_to(asio::buffer(ERROR), client_endpoint);
                    std::cerr << "Error sending confirmation message to client " << client_endpoint.address() << ":" << client_endpoint.port() << ": " << e.what() << std::endl;
                }
                std::cout << playerMessage << playerCount + 1 << ": " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
                connectedClients.push_back(client_endpoint);
                playerCount++;
                if (playerCount == maxPlayers)
                    notifyGameReady();
                alreadyConnectedClients.push_back(client_endpoint);
            } else {
                try {
                    server_socket.send_to(asio::buffer(SERVER_FULL), client_endpoint);
                } catch (std::exception const &e) {
                    std::cerr << "Error sending full message to client " << client_endpoint.address() << ":" << client_endpoint.port() << ": " << e.what() << std::endl;
                }
            }
        }
    }
}

void Server::handleDisconnect(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received)
{
    std::cout << "Disconnecting client: " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
    server_socket.send_to(asio::buffer(DISCONNECTED), client_endpoint);

    auto it = std::find(connectedClients.begin(), connectedClients.end(), client_endpoint);
    if (it != connectedClients.end()) {
        connectedClients.erase(it);
        auto alreadyConnectedIt = std::find(alreadyConnectedClients.begin(), alreadyConnectedClients.end(), client_endpoint);
        if (alreadyConnectedIt != alreadyConnectedClients.end())
            alreadyConnectedClients.erase(alreadyConnectedIt);
        auto playerNumberIt = playerNumberMap.find(client_endpoint);
        if (playerNumberIt != playerNumberMap.end()) {
            int disconnectedPlayerNumber = playerNumberIt->second;
            playerNumberMap.erase(playerNumberIt);
            playerCount--;
            for (auto& entry : playerNumberMap)
                if (entry.second > disconnectedPlayerNumber)
                    entry.second--;
            std::string nbPlayer = std::to_string(playerCount) + " players connected\n";
            broadcastMessage(nbPlayer, nbPlayer.size(), client_endpoint);
        }
        readyClients.erase(std::remove(readyClients.begin(), readyClients.end(), client_endpoint), readyClients.end());
    }
}

void Server::handleReady(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received)
{
    std::cout << "Client is ready: " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
    readyClients.push_back(client_endpoint);
    if (readyClients.size() == connectedClients.size()) {
        std::cout << "All clients are ready. Starting the game!" << std::endl;
        isChatLocked = true;
        notifyGameReady();
    }
}

void Server::connectClient(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received)
{
    if (bytes_received >= sizeof(client_message_t)) {
        client_message_t playerInfo = Serialization::deserialize<client_message_t>(
            std::vector<char>(buffer.begin(), buffer.begin() + sizeof(client_message_t))
        );
        broadcastStructureClient(playerInfo, sizeof(client_message_t), client_endpoint);
    } else {
        std::string message(buffer.data(), bytes_received);
        auto it = serverCommandHandler.find(message);
        if (it != serverCommandHandler.end())
            it->second(*this, client_endpoint, buffer, bytes_received);
        else
            broadcastMessage(buffer.data(), bytes_received, client_endpoint);
    }
}

void Server::notifyGameReady()
{
    for (const auto& client : connectedClients) {
        try {
            server_socket.send_to(asio::buffer(READY), client);
        } catch (std::exception const &e) {
            std::cerr << "Error sending game ready message to client " << client.address() << ":" << client.port() << ": " << e.what() << std::endl;
        }
    }
}

void Server::broadcastMessage(const std::string& message, size_t messageSize, const udp::endpoint& sender)
{
    int senderNumber = playerNumberMap[sender];
    std::string newMessage = std::to_string(senderNumber) + ": " + message;

    for (const auto& client : connectedClients) {
        if (client != sender) {
            try {
                server_socket.send_to(asio::buffer(newMessage.c_str(), newMessage.size()), client);
            } catch (std::exception const &e) {
                std::cerr << "Error sending message to client " << client.address() << ":" << client.port() << ": " << e.what() << std::endl;
            }
        }
    }
}

void Server::acceptClients()
{
    std::cout << "Waiting for clients..." << std::endl;
    try {
        while (1) {
            udp::endpoint client_endpoint;
            std::array<char, 2048> buffer;
            size_t bytes_received = server_socket.receive_from(asio::buffer(buffer), client_endpoint);
            if (bytes_received > 0)
                connectClient(client_endpoint, buffer, bytes_received);
            else
                std::cerr << "Error: Received 0 bytes from client." << std::endl;
            buffer.fill(0);
        }
    } catch (std::exception const &e) {
        std::cerr << "Error in acceptClients: " << e.what() << std::endl;
    }
}
