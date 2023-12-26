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

/*
static const std::map<sf::Keyboard::Key, std::string> inputHandler = {
    {sf::Keyboard::Z, "UP"},
    {sf::Keyboard::S, "DOWN"},
    {sf::Keyboard::Q, "LEFT"},
    {sf::Keyboard::D, "RIGHT"},
    {sf::Keyboard::Space, "ACTION"},
    {sf::Keyboard::Escape, "QUIT"}
};
*/

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

void Client::getNewMessage()
{
    socket_.async_receive_from(
        asio::buffer(receiveBuffer_),
        senderEndpoint_,
        [this](const asio::error_code &error, std::size_t bytesTransferred) {
            if (!error) {
                std::string message(receiveBuffer_.begin(), receiveBuffer_.begin() + bytesTransferred);
                this->getNewMessage();
            } else {
                std::cerr << "Error receiving data: " << error.message() << std::endl;
            }
        }
    );
}
