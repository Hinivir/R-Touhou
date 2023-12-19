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
/*
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
*/
Client::Client(asio::io_context& io_context, const std::string& server_ip, std::size_t server_port)
    : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
        server_endpoint_(asio::ip::address::from_string(server_ip), server_port) {}

Client::~Client() {}

void Client::sendMessage(const std::string& message) {
    socket_.send_to(asio::buffer(message), server_endpoint_);
}

void Client::getNewMessage() {
    asio::error_code error;
    std::size_t len = socket_.receive_from(asio::buffer(recv_buf_), server_endpoint_, 0, error);
    if (error && error != asio::error::message_size)
        throw asio::system_error(error);
    std::string message(recv_buf_.data(), len);
    std::cout << message << std::endl;
    if (std::strcmp(message.c_str(), "103:Disconnected!\n") == 0) {
        std::cout << "Server disconnected!" << std::endl;
        disconnectFlag_ = true;
        exit(0);
    }
}

void Client::runClient() {
    std::thread readThread([&]() {
        while (!disconnectFlag_) {
            getNewMessage();
        }
    });

    asio::io_context io_context;
    asio::steady_timer timer(io_context, asio::chrono::milliseconds(100));

    timer.async_wait([&](const asio::error_code&) {
        std::unique_lock<std::mutex> lock(input_mutex_);
        if (!input_buffer_.empty()) {
            sendMessage(input_buffer_);
            input_buffer_.clear();
        }
        timer.expires_at(timer.expiry() + asio::chrono::milliseconds(100));
        timer.async_wait([&](const asio::error_code&) { runClient(); });
    });

    std::thread ioThread([&]() {
        while (!disconnectFlag_) {
            char c;
            std::cin.get(c);

            {
                std::unique_lock<std::mutex> lock(input_mutex_);
                input_buffer_.push_back(c);
            }
        }
    });

    io_context.run();
    ioThread.join();
    readThread.join();
}
