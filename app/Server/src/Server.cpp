/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Server.cpp
*/

#include <thread>
#include "../include/Server.hpp"

Server::Server(std::string const ip, std::size_t const port)
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

void Server::connectUser()
{
    while (1) {
        clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            std::cerr << "ERROR: cannot accept client" << std::endl;
            close(serverSocket);
            exit(84);
        }
        std::cout << "Client connected" << std::endl;
        this->clients.push_back(clientSocket); // Store the client socket
        std::thread clientThread(&Server::handleClient, this, clientSocket);
        clientThread.detach();
    }
}

void Server::handleClient(int const clientSocket)
{
    while (1) {
        char buffer[1024] = {0};
        std::string message = "le serv à bien recu le message \n";
        int valread = read(clientSocket, buffer, sizeof(buffer) - 1);

        std::cout << valread << std::endl;
        std::cout << "Client: " << buffer << std::endl;
        if (valread == -1) {
            std::cerr << "ERROR: cannot read from client" << std::endl;
            close(clientSocket);
            exit(84);
        } else if (valread == 0) {
            std::cout << "Client disconnected" << std::endl;
            close(clientSocket);
            close(this->clients.back());
            this->clients.pop_back();
            return;
        }
        buffer[valread] = '\0';
        send(clientSocket, message.c_str(), message.size(), 0);
        for (int socket : this->clients)
            if (socket != clientSocket)
                send(socket, buffer, strlen(buffer), 0);
    }
}
