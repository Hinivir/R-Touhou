/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "../include/Client.hpp"
#include <arpa/inet.h>

Client::Client(std::string const ip, std::size_t const port)
{
    this->ip = ip;
    this->port = port;
}

Client::~Client(void)
{
}

void Client::connectClient(void)
{
    this->userSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->userSocket == -1) {
        std::cerr << "ERROR: cannot create client socket" << std::endl;
        exit(84);
    }
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_addr.s_addr = inet_addr(this->ip.c_str());
    this->serverAddress.sin_port = htons(this->port);
    if (connect(this->userSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "ERROR: cannot connect to server" << std::endl;
        close(this->userSocket);
        exit(84);
    }
    std::cout << "Connected to server" << std::endl;
    close(this->userSocket);
}

void Client::closeClient(void)
{
    close(this->userSocket);
    std::cout << "Client closed" << std::endl;
}
