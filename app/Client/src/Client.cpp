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

static const float speed = 0.005;

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
    asio::io_context io_context;
    asio::steady_timer timer(io_context, asio::chrono::milliseconds(1));

    socket_.send_to(asio::buffer(message), server_endpoint_);
    timer.async_wait([&](const asio::error_code&) { sendMessage(message); });
}

void Client::getNewMessage() {
    std::size_t len = socket_.receive_from(asio::buffer(recv_buf_), server_endpoint_);
    std::string message(recv_buf_.data(), len);

    std::cout << "Received: " << message << std::endl;

    if (message == "QUIT") {
        disconnectFlag_ = true;
    }
    for (auto& [key, value] : inputHandler) {
        if (message == value) {
            history_received_messages.push(message);
        }
    }
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

void handleCollisions(sf::RectangleShape& movingSquare, const sf::RectangleShape& stationarySquare, float speed) {
    sf::FloatRect movingRect = movingSquare.getGlobalBounds();
    sf::FloatRect stationaryRect = stationarySquare.getGlobalBounds();

    if (movingRect.intersects(stationaryRect)) {
        if (speed > 0) {
            movingSquare.setPosition(stationaryRect.left - movingRect.width, movingRect.top);
        } else {
            movingSquare.setPosition(stationaryRect.left + stationaryRect.width, movingRect.top);
        }
    }
}

void Client::start_game()
{
    asio::io_context io_context;
    asio::steady_timer timer(io_context, asio::chrono::milliseconds(100));

    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type");
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

        elapsed = clock.getElapsedTime();
        if (elapsed.asMilliseconds() > 500) {
            isVisible = !isVisible;
            clock.restart();
        }

        handleCollisions(square1, square2, speed);
        //manage the inputs of the user
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            sendMessage("UP");
            square1.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sendMessage("DOWN");
            square1.move(0, speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            sendMessage("LEFT");
            square1.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sendMessage("RIGHT");
            square1.move(speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            sendMessage("ACTION");
            std::cout << "ACTION" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            sendMessage("QUIT");
            exit(0);
        }

        //manage the inputs of the other player
        handleCollisions(square2, square1, speed);
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
        }
        drawBlinkingZone(window, blinkingZone, isVisible);

        window.clear();
        window.draw(square1);
        window.draw(square2);
        window.display();
        timer.async_wait([&](const asio::error_code&) { start_game(); });
    }
    this->~Client();
}
