/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.cpp
*/

#include "Server.hpp"
#include "Registry.hpp"
#include "Systems.hpp"
#include "ServerGame.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>

Server::Server(const std::string &ip, const std::string &port) : ANetwork::ANetwork(ip, port), serverGame()
{
    _port = std::stoi(port);

    try {
        socket.close();
        socket.open(asio::ip::udp::v4());
        socket.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), _port));
    } catch (std::exception const &e) {
        std::cerr << "ERROR" << e.what() << std::endl;
        throw;
    }
}

Server::~Server(void)
{
    socket.close();
}

void Server::handleMessageString()
{
    std::string message = getBuffer().data();
    for (auto &command : serverCommandHandler) {
        if (message.find(command.first) != std::string::npos) {
            command.second(*this);
            return;
        }
    }
    std::cout << "Message received: " << getBuffer().data() << std::endl;
    std::stringstream ss;
    ss << playerNumberMap.at(senderEndpoint);
    std::string msg = "Player " + ss.str() + ": " + getBuffer().data();
    sendMessageStringToOtherClients(msg);
}

void Server::handleMessageSetup()
{
    handleMessageString();
}

void Server::handleMessageGame()
{
    inputMessage input = deserialize<inputMessage>(buffer);
    std::cout << "input received: " << input << std::endl;
    std::size_t id = input.id;
    for (std::size_t i = 0; i < 10; i++) {
        if (i == id) {
            std::cout << "id: " << id << std::endl;
            break;
        }
    }
}

void Server::handleMessageGame(Game::ServerGame &game) {
    inputMessage input = deserialize<inputMessage>(buffer);
    float x = game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x;
    float y = game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y;
    if (input.key == sf::Keyboard::Key::Up) {
        game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y -= 10;
        positionMessage toSend = {'p', int(input.id), x, y};
        sendMessageToOtherClients<positionMessage>(toSend);
    } else if (input.key == sf::Keyboard::Key::Down) {
        game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y += 10;
        positionMessage toSend = {'p', int(input.id), x, y};
        sendMessageToOtherClients<positionMessage>(toSend);
    } else if (input.key == sf::Keyboard::Key::Left) {
        game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x -= 10;
        positionMessage toSend = {'p', int(input.id), x, y};
        sendMessageToOtherClients<positionMessage>(toSend);
    } else if (input.key == sf::Keyboard::Key::Right) {
        game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x += 10;
        positionMessage toSend = {'p', int(input.id), x, y};
        sendMessageToOtherClients<positionMessage>(toSend);
    } else if (input.key == sf::Keyboard::Key::Space) {
        std::cout << "new bullet at " << x << " " << y << std::endl;
        ///////
        GameEngine::Entity bullet = game.getRegistry().spawnEntity();
        game.getRegistry().addComponent<GameEngine::Size>(bullet, GameEngine::Size{10, 10});
        game.getRegistry().addComponent<GameEngine::Position>(
            bullet, GameEngine::Position{
                        x, y + 50 / 2});
        game.getRegistry().addComponent<GameEngine::Velocity>(bullet, GameEngine::Velocity{25.0f, 0.0f});
        game.getRegistry().addComponent<GameEngine::Hitbox>(bullet, GameEngine::Hitbox{});
        game.getRegistry().addComponent<GameEngine::Drawable>(bullet, GameEngine::Drawable{true});
        game.getRegistry().addComponent<GameEngine::Sprite>(
            bullet, GameEngine::Sprite{"./../games/resources/R-Touhou/graphics/bullet.png",
                        sf::Sprite(), sf::Texture()});
        game.getRegistry().addComponent<GameEngine::ZIndex>(
            bullet, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});
        game.getRegistry().addComponent<GameEngine::Projectile>(bullet, GameEngine::Projectile{});
        game.getRegistry().addComponent<GameEngine::Path>(
            bullet, GameEngine::Path{x, y, 1920 + 50, 1080 + 50});
        game.getEntityVector().push_back(bullet);
        bulletMessage toSend = {'b', x, y};
        sendMessageToOtherClients<bulletMessage>(toSend);
        ///////////
    }
}

void Server::manageServer()
{
    std::cout << "Waiting for clients..." << std::endl;
    try {
        while (1) {
            receiveMessage(false);
            buffer.fill(0);
        }
    } catch (std::exception const &e) {
        std::cerr << "Error in manageServer: " << e.what() << std::endl;
    }
}

void Server::commandConnect() {
    std::stringstream ss;

    if (std::find(clients.begin(), clients.end(), senderEndpoint) == clients.end()) {
        if (clients.size() < maxPlayers) {
            playerNumber++;
            playerNumberMap[senderEndpoint] = playerNumber;
            ss << playerNumber;
            sendMessage(CONNECTED, senderEndpoint, false);
            sendMessage("You are player " + ss.str() + "!\n", senderEndpoint, false);
            sendMessage("Number of players: " + ss.str() + "\n", senderEndpoint, false);
            clients.push_back(senderEndpoint);
            sendMessageStringToOtherClients(NEW_CLIENT);
        }
    }
}

void Server::commandDisconnect() {
    sendMessage(DISCONNECTED, senderEndpoint, false);
    std::size_t idx = 0;

    for (const auto& client : clients) {
        if (client == senderEndpoint) {
            clients.erase(clients.begin() + idx);
            auto playerNumberIt = playerNumberMap.find(senderEndpoint);
            if (playerNumberIt != playerNumberMap.end()) {
                playerNumberMap.erase(playerNumberIt);
                playerNumber--;
            }
            break;
        }
        idx++;
    }
    std::cout << "connected number " << clients.size() << std::endl;
}

void Server::commandError() {
    sendMessage(ERROR_MSG, senderEndpoint, false);
}

void Server::commandReady() {
    clientsReady.push_back(senderEndpoint);
    sendMessage("Waiting other players...", senderEndpoint, false);
    sendMessage(READY, senderEndpoint, false);
    this->isInChat = false;
    this->isInSetup = true;
    this->isInGame = false;
    this->serverGame.init(this->playerNumber, 2048, 20);
    for (std::size_t i = this->serverGame.getNbPlayer(); i < this->serverGame.getDefaultNbEnemies() + this->serverGame.getNbPlayer(); i++) {
           float x = rand() % 1080 + 1920;
           float y = rand() % 1000 - 50;
           while (y < 50)
               y += 50;
           while (x < 1030)
               x += 1030;
            // x is larg and y is height
           this->serverGame.getEnemiesPosPair().push_back(std::pair<float, float>{x, y});
    }
    this->serverGame.setup();
    this->serverGame.getSystemGroup().initEnemy(serverGame.getRegistry(), this->serverGame.getEnemiesPosPair());
}

void Server::commandFull() {
    sendMessage(SERVER_FULL, senderEndpoint, false);
}

void Server::commandClientDisconnect() {
    sendMessageToOtherClients(CLIENT_DISCONNECTED);
}

void Server::commandStartGame() {
    clientsSetup.push_back(senderEndpoint);
    if (clientsSetup.size() == clientsReady.size() && clientsSetup.size() == clients.size()) {
        sendMessageStringToAllClients(START_GAME);
        std::cout << "All clients are ready. Starting the game!" << std::endl;
        this->isInChat = false;
        this->isInSetup = false;
        this->isInGame = true;
        sendMessageToAllClients<std::vector<std::pair<float, float>>>(this->serverGame.getEnemiesPosPair());
        handleGame();
    }
}

void Server::asyncReceive(Game::ServerGame &game)
{
    buffer.fill(0);
    socket.async_receive_from(asio::buffer(buffer), senderEndpoint,
        [this, &game](std::error_code const &error, std::size_t bytesReceived) {
            if (!error && bytesReceived > 0) {
                handleMessageGame(game);
                asyncReceive(game);
            } else {
                std::cerr << "Error in asyncReceive: " << error.message() << std::endl;
            }
    });
}

void Server::handleGame() {
    this->isInSetup = false;
    this->isInGame = true;
    runGame(serverGame);
}

void Server::runGame(Game::ServerGame &game)
{
    asyncReceive(game);
}
