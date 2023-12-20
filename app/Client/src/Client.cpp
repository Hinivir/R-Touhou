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

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

static const std::size_t speed = 0.5f;

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
        server_endpoint_(asio::ip::address::from_string(server_ip), server_port) {
        }

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
        if (std::strcmp(message.c_str(), value.c_str()) == 0 && this->history_received_messages.size() < 10)
            this->history_received_messages.push(message);
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

void drawBlinkingZone(sf::RenderWindow& window, sf::RectangleShape& blinkingZone, bool& isVisible) {
    if (isVisible) {
        window.draw(blinkingZone);
    }
}

void Client::start_game()
{
    asio::io_context io_context;
    asio::steady_timer timer(io_context, asio::chrono::milliseconds(100));

    sf::RenderWindow window(sf::VideoMode(1200, 800), "R-Type");
    sf::RectangleShape square1(sf::Vector2f(50, 50));
    sf::RectangleShape square2(sf::Vector2f(50, 50));
    sf::RectangleShape blinkingZone(sf::Vector2f(200, 200));

    bool isVisible = true;
    blinkingZone.setFillColor(sf::Color(128, 0, 128));
    blinkingZone.setPosition(500, 300);

    square1.setFillColor(sf::Color::Red);
    square2.setFillColor(sf::Color::Green);
    square1.setPosition(100, 100);
    square2.setPosition(100, 300);

    sf::Clock clock;
    sf::Time elapsed;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ///////// GAME LOGIC /////////
//        for (auto& [key, value] : inputHandler) {
//            if (sf::Keyboard::isKeyPressed(key))
//                sendMessage(value);
//        }


        //manage the inputs of the user
        for (auto& [key, value] : inputHandler) {
                if (sf::Keyboard::isKeyPressed(key)) {
                    if (std::strcmp(value.c_str(), "UP") == 0)
                        square1.move(0, -speed);
                    else if (std::strcmp(value.c_str(), "DOWN") == 0)
                        square1.move(0, speed);
                    else if (std::strcmp(value.c_str(), "LEFT") == 0)
                        square1.move(-speed, 0);
                    else if (std::strcmp(value.c_str(), "RIGHT") == 0)
                        square1.move(speed, 0);
                    else if (std::strcmp(value.c_str(), "ACTION") == 0)
                        std::cout << "ACTION" << std::endl;
                    else if (std::strcmp(value.c_str(), "QUIT") == 0)
                        exit(0);
                }
        }

        //manage the inputs of the other player
        while (!history_received_messages.empty()) {
            std::string message = history_received_messages.front();
            history_received_messages.pop();
            if (std::strcmp(message.c_str(), "UP") == 0)
                square2.move(0, -speed);
            else if (std::strcmp(message.c_str(), "DOWN") == 0)
                square2.move(0, speed);
            else if (std::strcmp(message.c_str(), "LEFT") == 0)
                square2.move(-speed, 0);
            else if (std::strcmp(message.c_str(), "RIGHT") == 0)
                square2.move(speed, 0);
            else if (std::strcmp(message.c_str(), "ACTION") == 0)
                std::cout << "ACTION" << std::endl;
            else if (std::strcmp(message.c_str(), "QUIT") == 0)
                exit(0);
        }
        drawBlinkingZone(window, blinkingZone, isVisible);

        window.clear();
        window.draw(square1);
        window.draw(square2);
        window.display();
        timer.async_wait([&](const asio::error_code&) { runClient(); });
    }
    this->~Client();
}
