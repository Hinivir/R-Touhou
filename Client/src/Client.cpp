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
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <SFML/Graphics/Color.hpp>
#include "SparseArray.hpp"



Client::Client(const std::string ip, const std::string port): ANetwork::ANetwork(ip, port)
{
    try {
        this->serverEndpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(ip), std::stoi(port));
        this->socket.open(asio::ip::udp::v4());
        this->sendMessage("Connect\n", this->serverEndpoint, true);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

Client::~Client()
{
    this->socket.close();
}

/*

void Client::sendMessage(const std::string &message)
{
    socket_.async_send_to(asio::buffer(message), serverEndpoint_, [this](const asio::error_code &error, std::size_t) {
        if (error) {
            std::cerr << "Error sending data: " << error.message() << std::endl;
        }
    });
}

void Client::handleMessageInGame(const std::string &message)
{
    std::size_t player_number = std::stoi(message.substr(0, 1));
    std::string action = message.substr(3, message.length());
    std::cout << action << " from " << player_number << std::endl;
    for (auto const &[key, value] : inputHandler) {
        if (action == value.first) {
            value.second(*this, player_number);
        }
    }
}

void Client::getNewMessage()
{
    socket_.async_receive_from(asio::buffer(receiveBuffer_), senderEndpoint_,
        [this](const asio::error_code &error, std::size_t bytesTransferred) {
            if (!error) {
                if (this->inGame) {
                    std::string message(receiveBuffer_.begin(), receiveBuffer_.begin() + bytesTransferred);
                    this->parseMessage(message);
                } else {
                    std::string message(receiveBuffer_.begin(), receiveBuffer_.begin() + bytesTransferred);
                    std::cout << message << std::endl;
                    this->parseMessage(message);
                }
                this->getNewMessage();
            } else {
                std::cerr << "Error receiving data: " << error.message() << std::endl;
            }
        });
}

//this is a temporary function, we will have to change it with the game code
void Client::runGameTmp()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type");
    std::size_t player_number = this->players.size();

    // player
    this->player.pos_x = 50;                                    //
    this->player.pos_y = this->player.player_number * 100 + 50; //
    sf::RectangleShape player_shape(sf::Vector2f(50.f, 50.f));  //
    sf::Vector2i player_pos(this->player.pos_x, this->player.pos_y);
    player_shape.setPosition(player_pos.x, player_pos.y);
    std::size_t color_index = this->player.player_number - 1;
    player_shape.setFillColor(colors[this->player.player_number - 1]);

    // loop on other players
    std::vector<sf::RectangleShape> other_shape = {};

    for (auto p : this->players) {
        p.pos_x = 50;
        p.pos_y = p.player_number * 100 + 50;
    }
    for (std::size_t i = 0; i < player_number; i++) {
        sf::RectangleShape shape(sf::Vector2f(50.f, 50.f));
        shape.setPosition(this->players[i].pos_x, this->players[i].pos_y);
        shape.setFillColor(colors[this->players[i].player_number - 1]);
        other_shape.push_back(shape);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                for (auto const &[key, value] : inputHandler) {
                    if (event.key.code == key) {
                        value.second(*this, this->player.player_number);
                    }
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player_shape.setPosition(this->player.pos_x, this->player.pos_y);
        // loop on other players
        for (std::size_t i = 0; i < player_number; i++) {
            other_shape[i].setPosition(this->players[i].pos_x, this->players[i].pos_y);
        }
        window.clear();
        window.draw(player_shape);
        // loop on other players
        for (auto shape : other_shape) {
            window.draw(shape);
        }
        window.display();
    }
}
*/
