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

static const std::map<sf::Keyboard::Key,std::pair<std::string,std::function<void(Client &, bool)>>> inputHandler = {
    {sf::Keyboard::Z, {"UP", &Client::upFunction}},
    {sf::Keyboard::S, {"DOWN", &Client::downFunction}},
    {sf::Keyboard::Q, {"LEFT", &Client::leftFunction}},
    {sf::Keyboard::D, {"RIGHT", &Client::rightFunction}},
    {sf::Keyboard::Space, {"ACTION", &Client::actionFunction}},
    {sf::Keyboard::Escape, {"QUIT", &Client::quitFunction}}
};

Client::Client(
    asio::io_context &ioContext,
    const std::string &serverAddress,
    const std::string &serverPort)
    : ioContext_(ioContext),
      socket_(
          ioContext,
          asio::ip::udp::endpoint(asio::ip::udp::v4(),
                                  0))
{
    asio::ip::udp::resolver resolver(ioContext);
    serverEndpoint_ = *resolver.resolve(asio::ip::udp::v4(), serverAddress, serverPort).begin();
}

Client::~Client() {}

void Client::sendMessage(const std::string &message)
{
    socket_.async_send_to(
        asio::buffer(message),
        serverEndpoint_,
        [this](const asio::error_code &error, std::size_t) {
            if (error) {
                std::cerr << "Error sending data: " << error.message() << std::endl;
            }
        }
    );
}

void Client::handleMessageInGame(const std::string &message)
{
    for (auto const& [key, value] : inputHandler) {
        if (message == value.first) {
            value.second(*this, true);
        }
    }
}

void Client::getNewMessage()
{
    socket_.async_receive_from(
        asio::buffer(receiveBuffer_),
        senderEndpoint_,
        [this](const asio::error_code &error, std::size_t bytesTransferred) {
            if (!error) {
                std::string message(receiveBuffer_.begin(), receiveBuffer_.begin() + bytesTransferred);
                std::cout << message << std::endl;
                this->ParseMessage(message);
                this->getNewMessage();
            } else {
                std::cerr << "Error receiving data: " << error.message() << std::endl;
            }
        }
    );
}

//this is a temporary function, we will have to change it with the game code
void Client::runGame()
{
    //setup players
    if (this->player.player_number == 1)
        this->other_player.player_number = 2;
    else
        this->other_player.player_number = 1;
    this->player.pos_x = 50;
    this->player.pos_y = this->player.player_number * 100 + 50;
    this->other_player.pos_x = 50;
    this->other_player.pos_y = this->other_player.player_number * 100 + 50;
    //
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type");

    sf::RectangleShape player_shape(sf::Vector2f(50.f, 50.f));
    sf::Vector2i player_pos(this->player.pos_x, this->player.pos_y);

    sf::RectangleShape other_shape(sf::Vector2f(50.f, 50.f));
    sf::Vector2i other_pos(this->other_player.pos_x, this->other_player.pos_y);

    player_shape.setPosition(player_pos.x, player_pos.y);
    if (this->player.player_number == 1)
        player_shape.setFillColor(sf::Color::Red);
    else
        player_shape.setFillColor(sf::Color::Green);

    other_shape.setPosition(other_pos.x, other_pos.y);
    if (this->other_player.player_number == 1)
        other_shape.setFillColor(sf::Color::Red);
    else
        other_shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Vector2i new_player_pos(this->player.pos_x, this->player.pos_y);
        sf::Vector2i new_other_pos(this->other_player.pos_x, this->other_player.pos_y);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                for (auto const& [key, value] : inputHandler) {
                    if (event.key.code == key) {
                        value.second(*this, false);
                    }
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player_shape.setPosition(new_player_pos.x, new_player_pos.y);
        other_shape.setPosition(new_other_pos.x, new_other_pos.y);
        window.clear();
        window.draw(player_shape);
        window.draw(other_shape);
        window.display();
    }
}
