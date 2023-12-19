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

void Server::notifyGameReady()
{
    std::string gameReadyMessage = "Game is ready! Let the fun begin!\n";

    for (const auto& client : connectedClients) {
        try {
            server_socket.send_to(asio::buffer(gameReadyMessage), client);
        } catch (std::exception const &e) {
            std::cerr << "Error sending game ready message to client " << client.address() << ":" << client.port() << ": " << e.what() << std::endl;
        }
    }
}

void Server::connectClient(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received)
{
    std::string message(buffer.data(), bytes_received);
    if (message == "connect\n") {
        std::cout << "Client connected: " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
        connectedClients.push_back(client_endpoint);
        std::string confirmationMessage = "101:You are connected!\n";
        try {
            server_socket.send_to(asio::buffer(confirmationMessage), client_endpoint);
        } catch (std::exception const &e) {
            server_socket.send_to(asio::buffer("102:Error Connection!\n"), client_endpoint);
            std::cerr << "Error sending confirmation message to client " << client_endpoint.address() << ":" << client_endpoint.port() << ": " << e.what() << std::endl;
        }
    }
    //else if (message == "disconnect\n") {
    //    std::cout << "Disconnecting client: " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
    //    server_socket.send_to(asio::buffer("103:Disconnected!\n"), client_endpoint);
    //    auto it = std::find(connectedClients.begin(), connectedClients.end(), client_endpoint);
    //    if (it != connectedClients.end()) {
    //        connectedClients.erase(it);
    //        readyClients.erase(std::remove(readyClients.begin(), readyClients.end(), client_endpoint), readyClients.end());
    //    }
    //}
    else if (message == "ready\n") {
        std::cout << "Client is ready: " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
        readyClients.push_back(client_endpoint);
        if (readyClients.size() == connectedClients.size()) {
            std::cout << "All clients are ready. Starting the game!" << std::endl;
            isChatLocked = true;
            notifyGameReady();
            //lancé le jeu ici
        }
    }
    else
        broadcastMessage(buffer, bytes_received, client_endpoint);
    if (std::find(connectedClients.begin(), connectedClients.end(), client_endpoint) == connectedClients.end())
        connectedClients.push_back(client_endpoint);
}

void Server::broadcastMessage(const std::array<char, 2048>& buffer, size_t bytes_received, const asio::ip::udp::endpoint& sender)
{
    std::string message(buffer.data(), bytes_received);

    for (const auto& client : connectedClients) {
        if (client != sender) {
            if (message != "connect") {
                try {
                    server_socket.send_to(asio::buffer(message), client);
                } catch (std::exception const &e) {
                    std::cerr << "Error sending message to client " << client.address() << ":" << client.port() << ": " << e.what() << std::endl;
                }
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
        }
    } catch (std::exception const &e) {
        std::cerr << "Error in acceptClients: " << e.what() << std::endl;
    }
}
