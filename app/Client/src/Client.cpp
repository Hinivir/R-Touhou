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
    for (auto& [key, value] : inputHandler)
        if (std::strcmp(message.c_str(), value.c_str()) == 0)
            this->input_queue_.push(message);
    if (std::strcmp(message.c_str(), "Game is ready! Let the fun begin!") == 0)
        start_game();
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
    sf::RenderWindow window(sf::VideoMode(1200, 800), "R-Type");
    sf::Vector2i player_pos_ = sf::Vector2i(500, 500);
    sf::Vector2i second_player_pos_ = sf::Vector2i(500, 500);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ///////// GAME LOGIC /////////
        for (auto& [key, value] : inputHandler)
            if (sf::Keyboard::isKeyPressed(key))
                sendMessage(value);

        //manage the inputs of the user
//        for (auto& [key, value] : inputHandler) {
//            if (std::strcmp(value.c_str(), "UP") == 0)
//                player_pos_.y -= speed;
//            else if (std::strcmp(value.c_str(), "DOWN") == 0)
//                player_pos_.y += speed;
//            else if (std::strcmp(value.c_str(), "LEFT") == 0)
//                player_pos_.x -= speed;
//            else if (std::strcmp(value.c_str(), "RIGHT") == 0)
//                player_pos_.x += speed;
//            else if (std::strcmp(value.c_str(), "ACTION") == 0)
//                std::cout << "ACTION" << std::endl;
//            else if (std::strcmp(value.c_str(), "QUIT") == 0)
//                window.close();
//        }

        //manage the inputs of the other player
//        while (!input_queue_.empty()) {
//            if (std::strcmp(input_queue_.front().c_str(), "UP") == 0)
//                second_player_pos_.y -= speed;
//            else if (std::strcmp(input_queue_.front().c_str(), "DOWN") == 0)
//                second_player_pos_.y += speed;
//            else if (std::strcmp(input_queue_.front().c_str(), "LEFT") == 0)
//                second_player_pos_.x -= speed;
//            else if (std::strcmp(input_queue_.front().c_str(), "RIGHT") == 0)
//                second_player_pos_.x += speed;
//            else if (std::strcmp(input_queue_.front().c_str(), "ACTION") == 0)
//                std::cout << "ACTION FROM THE OTHER" << std::endl;
//            input_queue_.pop();
//        }        


        window.clear();
        window.display();
    }
    this->~Client();
}
