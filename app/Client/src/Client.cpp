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

Client::Client(asio::io_context& io_context, const std::string& server_ip, std::size_t server_port)
    : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
        server_endpoint_(asio::ip::address::from_string(server_ip), server_port) {}

Client::~Client() {}

void Client::sendMessage(const std::string& message) {
    socket_.send_to(asio::buffer(message), server_endpoint_);
}

void Client::getNewMessage(void) {
    std::array<char, 1024> recv_buf = {0};
    asio::error_code error;
    std::size_t len = socket_.receive_from(asio::buffer(recv_buf), server_endpoint_, 0, error);
    if (error && error != asio::error::message_size)
        throw asio::system_error(error);
    std::string message(recv_buf.data(), len);
    this->_messageQueue.push(message);
    std::cout << "received message: " << message << std::endl;
}

void Client::runClient(void) {
    std::string message;
    std::thread readThread([&]() {
        while (true) {
            this->getNewMessage();
        }
    });

    while (true) {
        char c = getch();
        if (inputHandler.find(c) != inputHandler.end()) {
            message = inputHandler.at(c);
            this->sendMessage(message);
        }
        if (c == 27) {
            std::terminate();
            break;
        }
    }
    readThread.join();
}
