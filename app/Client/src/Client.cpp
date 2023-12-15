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

static const std::map<char, std::string> inputHandler = {
    {'z', "UP"},
    {'s', "DOWN"},
    {'q', "LEFT"},
    {'d', "RIGHT"},
    {' ', "ACTION"},
    {27, "QUIT"}
};

char _getch()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return (buf);
}

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

void Client::sendMessage(std::string const message)
{
    std::cout << "Sending message: " << message << std::endl;
}

void Client::getMessage(void)
{
    std::cout << "Getting message" << std::endl;
}

void Client::runClient(void)
{
    while (1) {
        char input = _getch();
        if (inputHandler.find(input) != inputHandler.end()) {
            this->sendMessage(inputHandler.at(input));
        }
    }
}
