/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include "../../../include/Server/Server.hpp"

Server::Server(std::string ip, std::size_t port)
{
    this->ip = ip;
    this->port = port;
}

Server::~Server()
{
    closeServer();
}

void Server::closeServer()
{
    while (!this->clients.empty()) {
        close(this->clients.back());
        this->clients.pop_back();
        std::cout << "Client disconnected" << std::endl;
    }
    close(this->serverSocket);
    std::cout << "Server closed" << std::endl;
}

void Server::setServer()
{
    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket == -1) {
        std::cerr << "ERROR: cannot create server socket" << std::endl;
        exit(84);
    }
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_addr.s_addr = INADDR_ANY;
    this->serverAddress.sin_port = htons(this->port);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "ERROR: cannot bind server" << std::endl;
        close(serverSocket);
        exit(84);
    }
    if (listen(serverSocket, 4) == -1) {
        std::cerr << "ERROR: cannot listen" << std::endl;
        close(serverSocket);
        exit(84);
    }
    std::cout << "Server is listening on port " << this->port << std::endl;
}

void Server::connectUser()//to upgrade (multithread)
{
    while (1) {
        clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            std::cerr << "ERROR: cannot accept client" << std::endl;
            close(serverSocket);
            exit(84);
        }
        std::cout << "Client connected" << std::endl;
        this->clients.push_back(clientSocket);
    }
}
