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
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= static_cast<unsigned int>(~(ICANON | ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
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
    while (1) {
        int input = getch();
        if (inputHandler.find(input) != inputHandler.end()) {
            std::string message = inputHandler.at(input);
            this->sendMessage(message);
            if (message == "QUIT")
                break;
        }
        this->getMessage();
    }
}
