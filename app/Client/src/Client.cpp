/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "../include/Client.hpp"

#include <iostream>
#include <map>
#include <string>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

static const std::map<char, std::string> inputHandler = {
    {'z', "UP"},
    {'s', "DOWN"},
    {'q', "LEFT"},
    {'d', "RIGHT"},
    {' ', "ACTION"},
    {27, "QUIT"}
};

static int getch(void)
{
    struct termios oldSettings, newSettings;
    int ch;

    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

    return ch;
}

Client::Client(std::string const ip, std::size_t const port)
{
    this->ip = ip;
    this->port = port;
}

Client::~Client(void)
{
    if (this->userSocket != 0)
        this->closeClient();
}

bool Client::connectClient(void)
{
    this->userSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->userSocket == -1) {
        std::cerr << "ERROR: cannot create client socket" << std::endl;
        return false;
    }
    this->serverAddress.sin_family = AF_INET;
    this->serverAddress.sin_addr.s_addr = inet_addr(this->ip.c_str());
    this->serverAddress.sin_port = htons(this->port);
    if (connect(this->userSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "ERROR: cannot connect to server" << std::endl;
        close(this->userSocket);
        return false;
    }
    if (!this->setClient())
        return false;
    std::cout << "Connected to server" << std::endl;
    return true;
}

bool Client::setClient(void)
{
    int flags = fcntl(this->userSocket, F_GETFL, 0);

    if (flags == -1) {
        std::cerr << "ERROR: cannot get socket flags" << std::endl;
        close(this->userSocket);
        return false;
    }
    flags |= O_NONBLOCK;
    if (fcntl(this->userSocket, F_SETFL, flags) == -1) {
        std::cerr << "ERROR: cannot set socket flags" << std::endl;
        close(this->userSocket);
        return false;
    }
    return true;
}

void Client::closeClient(void)
{
    close(this->userSocket);
    std::cout << "Client closed" << std::endl;
}

void Client::sendMessage(std::string const message)
{
    std::cout << "Sending message: " << message << std::endl;
    send(this->userSocket, message.c_str(), message.size(), 0);
}

void Client::getMessage(void)
{
    char buffer[1024] = {0};

    read(this->userSocket, buffer, 1024);
    std::cout << "message from server: " << buffer << std::endl;
}

void Client::runClient(void)
{
    fd_set recvfds;
    fd_set sendfds;
    while (1) {
        FD_ZERO(&recvfds);
        FD_ZERO(&sendfds);

        FD_SET(STDIN_FILENO, &recvfds);
        FD_SET(this->userSocket, &recvfds);

        if (select(this->userSocket + 1, &recvfds, &sendfds, NULL, NULL) == -1) {
            std::cerr << "ERROR: cannot select" << std::endl;
            close(this->userSocket);
            return;
        }
        if (FD_ISSET(STDIN_FILENO, &recvfds)) {
            char c = getch();
            if (inputHandler.find(c) != inputHandler.end()) {
                this->sendMessage(inputHandler.at(c));
            }
        }
        if (FD_ISSET(this->userSocket, &recvfds)) {
            this->getMessage();
        }
    }
}
