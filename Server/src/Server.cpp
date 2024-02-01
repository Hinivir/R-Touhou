/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.cpp
*/

#include "Server.hpp"
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "Systems.hpp"
#include "Macros/ForEach.hpp"
#include "ServerGame.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>

std::ostream &operator<<(std::ostream &os, std::vector<std::pair<float, float>> &pos)
{
    for (auto &i : pos) {
        os << i.first << " " << i.second << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, std::vector<std::pair<float, float>>& pos)
{
    std::string line;
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        std::pair<float, float> p;
        iss >> p.first >> p.second;
        pos.push_back(p);
    }
    return is;
}

struct positionMessage {
    int id;
    float x;
    float y;

    friend std::ostream &operator<<(std::ostream &os, const positionMessage &message) {
        os << message.id << " " << message.x << " " << message.y;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, positionMessage &message) {
        is >> message.id >> message.x >> message.y;
        if (is.fail()) {
            throw std::runtime_error("Error while deserializing positionMessage");
        }
        return is;
    }
};

struct shootMessage {
    float shootX;
    float shootY;
    std::size_t id;

    friend std::ostream &operator<<(std::ostream &os, const shootMessage &message) {
        os << message.shootX << " " << message.shootY << " " << message.id;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, shootMessage &message) {
        is >> message.shootX >> message.shootY >> message.id;
        if (is.fail()) {
            throw std::runtime_error("Error while deserializing shootMessage");
        }
        return is;
    }
};

std::ostream &operator<<(std::ostream &os, sf::Keyboard::Key &key)
{
    os << key;
    return os;
}

std::istream &operator>>(std::istream &is, sf::Keyboard::Key &key)
{
    int k;
    is >> k;
    key = static_cast<sf::Keyboard::Key>(k);
    if (is.fail()) {
        throw std::runtime_error("Error while deserializing sf::Keyboard::Key");
    }
    return is;
}

struct inputMessage {
    std::size_t id;
    sf::Keyboard::Key key;

    friend std::ostream &operator<<(std::ostream &os, const inputMessage &message) {
        os << message.id << " " << message.key;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, inputMessage &message) {
        is >> message.id >> message.key;
        if (is.fail()) {
            throw std::runtime_error("Error while deserializing inputMessage");
        }
        return is;
    }
};

struct garbageMessage {
    int id;

    friend std::ostream &operator<<(std::ostream &os, const garbageMessage &message) {
        os << message.id;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, garbageMessage &message) {
        is >> message.id;
        if (is.fail()) {
            throw std::runtime_error("Error while deserializing garbageMessage");
        }
        return is;
    }
};

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

void Server::handleMessageGame(Game::ServerGame &game)
{
    inputMessage input = deserialize<inputMessage>(buffer);
    if (input.key == sf::Keyboard::Key::Up) {
        game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y -= 10;
    } else if (input.key == sf::Keyboard::Key::Down)
        game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y += 10;
    else if (input.key == sf::Keyboard::Key::Left)
        game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x -= 10;
    else if (input.key == sf::Keyboard::Key::Right)
        game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x += 10;
    else if (input.key == sf::Keyboard::Key::Space) {
        GameEngine::Entity shoot = game.createShoot(game.getRegistry(), game.getRegistry().getEntityById(input.id));
        game.getEntityVector().push_back(shoot);
        shootMessage shootMsg = {game.getRegistry().getComponent<GameEngine::Position>()[shoot].value().x,
            game.getRegistry().getComponent<GameEngine::Position>()[shoot].value().y, input.id};
        sendMessageToAllClients<shootMessage>(shootMsg);
    }
    float x = game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x;
    float y = game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y;
    positionMessage toSend = {int(input.id), x, y};
    sendMessageToOtherClients<positionMessage>(toSend);
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
    // TODO: need to setup Game
    this->isInChat = false;
    this->isInSetup = true;
    this->isInGame = false;
    // Need to put random number of enemies
    this->serverGame.init(this->playerNumber, 2048, 20);

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
        this->serverGame.setup();
        for (std::size_t i = this->serverGame.getNbPlayer(); i < this->serverGame.getDefaultNbEnemies() + this->serverGame.getNbPlayer(); i++) {
            float x = rand() % 1080 + 1920;
            float y = rand() % 1000 - 50;
            while (x < 50)
                x += 50;
            while (y < 1030)
                y += 1030;
            this->serverGame.getEnemiesPosPair().push_back(std::pair<float, float>{x, y});
        }
        this->serverGame.getSystemGroup().initEnemy(serverGame.getRegistry(), this->serverGame.getEnemiesPosPair());
        sendMessageToAllClients<std::vector<std::pair<float, float>>>(this->serverGame.getEnemiesPosPair());
        std::cout << "Enemies pos: " << this->serverGame.getEnemiesPosPair().size() << std::endl;
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
    asio::io_context &io_context(getIoContext());
    std::thread t([&io_context]() { io_context.run(); });
    while (1) {
        if (test) {
            std::cout << "test" << std::endl;
            test = false;
        }
    }
}
