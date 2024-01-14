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

static const std::vector<sf::Color> colors = {
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Magenta,
    sf::Color::Cyan
};
//remplacer le bool par le numero du player
static const std::map<sf::Keyboard::Key,std::pair<std::string,std::function<void(Client &, std::size_t)>>> inputHandler = {
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
    try {
        asio::ip::udp::resolver resolver(ioContext);
        serverEndpoint_ = *resolver.resolve(asio::ip::udp::v4(), serverAddress, serverPort).begin();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
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
    std::size_t player_number = std::stoi(message.substr(0, 1));
    std::string action = message.substr(3, message.length());
    std::cout << action << " from " << player_number << std::endl;
    for (auto const& [key, value] : inputHandler) {
        if (action == value.first) {
            value.second(*this, player_number);
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
                if (!this->hasPos && startInit && hasEnemy) {
                    std::cout << "get received Position data" << std::endl;
                    std::vector<char> serializedData(receiveBuffer_.begin(), receiveBuffer_.begin() + bytesTransferred);
                    std::cout << "serializedData size: " << serializedData.size() << std::endl;
                    /////segfault here
                    const SparseArray<GameEngine::Position> a = Serialization::deserialize<SparseArray<GameEngine::Position>>(serializedData);
                    std::cout << "a size: " << a.size() << std::endl;
                    allPos = a;
                    std::cout << "allPos size: " << allPos.size() << std::endl;
                } else if (!this->hasEnemy && startInit) {
                    std::cout << "get received Enemies data" << std::endl;
                    std::vector<char> serializedData(receiveBuffer_.begin(), receiveBuffer_.begin() + bytesTransferred);
                    enemies = Serialization::deserialize<std::vector<GameEngine::Entity>>(serializedData);
                    this->hasEnemy = true;
                } else if (this->inGame) {
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
        }
    );
}

//this is a temporary function, we will have to change it with the game code
void Client::runGameTmp()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type");
    std::size_t player_number = this->players.size();

    //player
    this->player.pos_x = 50;//
    this->player.pos_y = this->player.player_number * 100 + 50;//
    sf::RectangleShape player_shape(sf::Vector2f(50.f, 50.f));//
    sf::Vector2i player_pos(this->player.pos_x, this->player.pos_y);
    player_shape.setPosition(player_pos.x, player_pos.y);
    std::size_t color_index = this->player.player_number - 1;
    player_shape.setFillColor(colors[this->player.player_number - 1]);

    //loop on other players
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
                for (auto const& [key, value] : inputHandler) {
                    if (event.key.code == key) {
                        value.second(*this, this->player.player_number);
                    }
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        player_shape.setPosition(this->player.pos_x, this->player.pos_y);
        //loop on other players
        for (std::size_t i = 0; i < player_number; i++) {
            other_shape[i].setPosition(this->players[i].pos_x, this->players[i].pos_y);
        }
        window.clear();
        window.draw(player_shape);
        //loop on other players
        for (auto shape : other_shape) {
            window.draw(shape);
        }
        window.display();
    }
}
