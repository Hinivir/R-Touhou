/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.cpp
*/

#include "../include/Server.hpp"

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
    {"connect\n", &Server::handleConnect}
};

void Server::handleConnect(const asio::ip::udp::endpoint &endpoint, const std::array<char, 2048> &buffer, size_t size)
{
    std::string message(buffer.data(), size);
    if (message == "connect\n")
        verifConnected();
}

void Server::verifConnected()
{
    std::stringstream ss;

    if (std::find(clients.begin(), clients.end(), _endpoint) == clients.end()) {
        if (clients.size() < maxPlayers) {
            playerNumber++;
            playerNumberMap[_endpoint] = playerNumber;
            std::cout << "Client connected: " << _endpoint << " - Assigned Player " << playerNumber << std::endl;
            ss << playerNumber;
            sendMessage("You are player " + ss.str() + "!\n", _endpoint, false);
            clients.push_back(_endpoint);
        }
    }
}

void Server::receiveMessage()
{
    size_t bytes_received = socket.receive_from(asio::buffer(buffer), _endpoint);
    std::string message(buffer.data(), bytes_received);

    auto it = commandHandler.find(message);
    if (it != commandHandler.end())
        it->second(*this, _endpoint, buffer, bytes_received);
    else
        sendMessage("Unknown command\n", _endpoint, false);
}

void Server::acceptClients()
{
    std::cout << "Waiting for clients..." << std::endl;
    try {
        while (1) {
            receiveMessage();
            buffer.fill(0);
        }
    } catch (std::exception const &e) {
        std::cerr << "Error in acceptClients: " << e.what() << std::endl;
    }
}
