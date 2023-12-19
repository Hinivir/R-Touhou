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
#include <thread>
#include <SFML/Graphics.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

static const std::size_t speed = 100;

static const std::map<sf::Keyboard::Key, std::string> inputHandler = {
    {sf::Keyboard::Z, "UP"},
    {sf::Keyboard::S, "DOWN"},
    {sf::Keyboard::Q, "LEFT"},
    {sf::Keyboard::D, "RIGHT"},
    {sf::Keyboard::Space, "ACTION"},
    {sf::Keyboard::Escape, "QUIT"}
};

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
    if (std::strcmp(message.c_str(), "103:Disconnected!") == 0) {
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

void Client::start_game()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type");
    sf::RectangleShape player(sf::Vector2f(50, 50));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        for (auto& [key, value] : inputHandler) {
            if (sf::Keyboard::isKeyPressed(key)) {
                sendMessage(value);
            }
        }

        window.clear();
        window.display();
    }
}
