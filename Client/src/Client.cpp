/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "Systems.hpp"
#include "Macros/ForEach.hpp"
#include "Init.hpp"

#include "ClientGame.hpp"
#include "Systems/Draw.hpp"
#include "Systems/Sprite.hpp"

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

static const std::vector<sf::Keyboard::Key> kepMap = {
    {sf::Keyboard::Key::Up},
    {sf::Keyboard::Key::Left},
    {sf::Keyboard::Key::Down},
    {sf::Keyboard::Key::Right},
    {sf::Keyboard::Key::Space},
};

Client::Client(const std::string ip, const std::string port) : ANetwork::ANetwork(ip, port), clientGame()
{
    try {
        this->serverEndpoint = asio::ip::udp::endpoint(asio::ip::make_address_v4(ip), std::stoi(port));
        this->socket.open(asio::ip::udp::v4());
        this->sendMessage<std::string>("connect\n", this->serverEndpoint, false);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

Client::~Client() {
    if (this->socket.is_open())
        this->socket.close();
}

void Client::commandConnect() { std::cout << "Connected to server" << std::endl; }

void Client::commandDisconnect() {
    std::cout << "Disconnected from server" << std::endl;
    this->running = false;
    if (this->socket.is_open())
        this->socket.close();
}

void Client::commandError() { std::cout << "Error sending confirmation message to server" << std::endl; }

void Client::commandReady() {
    sendMessage<std::string>("start game\n", this->serverEndpoint, false);
}

void Client::handleMessageString() {
    std::string message = getBuffer().data();
    for (auto &command : clientCommandHandler) {
        if (message.find(command.first) != std::string::npos) {
            command.second(*this);
            return;
        }
    }
    manageMessage(message);
}

void Client::handleMessageSetup() {
    pos = deserialize<std::vector<std::pair<float, float>>>(this->buffer);
}

bool Client::deserializePositionMessage() {
    try {
        positionMessage message = deserialize<positionMessage>(this->buffer);
        entityPos = message.id;
        newPosX = message.x;
        newPosY = message.y;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Client::deserializeInputMessage() {
    try {
        inputMessage message = deserialize<inputMessage>(this->buffer);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Client::deserializeGarbageMessage() {
    try {
        garbageMessage message = deserialize<garbageMessage>(this->buffer);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Client::deserializeShootMessage() {
    try {
        shootMessage message = deserialize<shootMessage>(this->buffer);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

void Client::managePackageGame() {
    for (auto &deserializeFunction : deserializeFunctions) {
        if (deserializeFunction())
            return;
    }
    std::cout << "Error while deserializing" << std::endl;
}

void Client::handleMessageGame() {
    std::cout << buffer.data() << std::endl;
    managePackageGame();
}

void Client::commandFull() { std::cout << "Server is full" << std::endl; }

void Client::commandClientDisconnect() {
    playerNumber--;
}

void Client::manageMessage(std::string &message) {
    const std::string youArePlayer = "You are player ";
    const std::string playerNumberMsg = "Number of players: ";

    if (strncmp(youArePlayer.c_str(), message.c_str(), youArePlayer.size()) == 0)
        this->myNumber = std::stoi(message.substr(youArePlayer.size(), 1));
    else if (strcmp(NEW_CLIENT, message.c_str()) == 0)
        playerNumber++;
    else if (strncmp(playerNumberMsg.c_str(), message.c_str(), playerNumberMsg.size()) == 0)
        playerNumber = std::stoi(message.substr(playerNumberMsg.size(), 1));
    std::cout << message << std::endl;
}

void Client::commandStartGame() {
    std::cout << "Game is starting" << std::endl;
    std::thread gameThread([&]() { this->handleGame(); });
    gameThread.detach();
}

void Client::handleGame() {
    this->isInSetup = true;
    this->isInChat = false;
    this->clientGame.init(this->playerNumber, 2048, 20);
    while (this->clientGame.getEnemiesPosPair().empty()) { }
    std::cout << "Game started: " << this->clientGame.getEnemiesPosPair().size() << std::endl;
    isInChat = false;
    std::size_t my_player;
    this->clientGame.setup();

    for (auto pos : this->clientGame.getEnemiesPosPair()) {
        std::cout << "pos: " << pos.first << " " << pos.second << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Touhou");

    window.setFramerateLimit(60);
    /*for (std::size_t i = 0; i < playerNumber; i++) {
        GameEngine::Entity movableEntity = spawnMovableEntity(clientGame.getRegistry());
        if (i == myNumber - 1)
            my_player = i;
        this->clientGame.getEntityVector().push_back(movableEntity);
        //this->clientGame.getEntityVector() playerVector.push_back(movableEntity);
    }*/
    //std::cout << "my_player: " << my_player << std::endl;

    this->clientGame.getSystemGroup().initEnemy(clientGame.getRegistry(), this->clientGame.getEnemiesPosPair());

    this->isInSetup = false;
    this->isInGame = true;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            window.close();

        for (auto const &key: kepMap) {
            if (sf::Keyboard::isKeyPressed(key)) {
                inputMessage message = {my_player, key};
                std::array<char, 2048> sendBuffer;
                serialize<inputMessage>(message, sendBuffer);
                sendMessage<std::array<char, 2048>>(sendBuffer, this->serverEndpoint, false);
            }
        }

        //clientGame.getRegistry().getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(totalScore));
        this->clientGame.getSystemGroup().controlSystem(clientGame.getRegistry());

        /*if (shootCoolDown == 7) {
            system.attackSystem(clientGame.getRegistry(), entityVector);
            shootCoolDown = 0;
        }*/
        /*if (enemyCoolDown == 50 && spawnEnemy) {
            for (int i = 0; i < std::rand() % 31; ++i) {
                GameEngine::Entity staticEntity = spawnEnemyEntity(clientGame.getRegistry());
                entityVector.push_back(staticEntity);
            }
            enemyCoolDown = 0;
            system.initEnemy(clientGame.getRegistry());
        }
        enemyCoolDown++;
        shootCoolDown++;*/
        if (entityPos != -1) {
            std::cout << entityPos << std::endl;
            clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(entityPos)].value().x = newPosX;
            clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(entityPos)].value().y = newPosY;
            entityPos = -1;
        }
        GameEngine::System::sprite(clientGame.getRegistry());
        GameEngine::System::draw(clientGame.getRegistry(), window);
        //this->clientGame.getSystemGroup().movementSystem(clientGame.getRegistry());
        //this->clientGame.getSystemGroup().collisionSystem(clientGame.getRegistry(), totalScore);
        this->clientGame.getSystemGroup().deleteEntitiesSystem(clientGame.getRegistry());
        window.display();
        window.clear();

        /*if (totalScore == 100) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                clientGame.getRegistry().garbageEntities.push_back(entity);
            for (const auto &entity : playerVector)
                clientGame.getRegistry().garbageEntities.push_back(entity);
            clientGame.getRegistry().garbageEntities.push_back(backgroundStar1);
            clientGame.getRegistry().garbageEntities.push_back(backgroundStar2);
            clientGame.getRegistry().garbageEntities.push_back(groundDown);
            clientGame.getRegistry().garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            clientGame.getRegistry().getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
        }
        if (!isGameOver && clientGame.getRegistry().getComponent<GameEngine::Life>()[my_player].value().life <= 0) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                clientGame.getRegistry().garbageEntities.push_back(entity);
            for (const auto &entity : playerVector)
                clientGame.getRegistry().garbageEntities.push_back(entity);
            clientGame.getRegistry().garbageEntities.push_back(backgroundStar1);
            clientGame.getRegistry().garbageEntities.push_back(backgroundStar2);
            clientGame.getRegistry().garbageEntities.push_back(groundDown);
            clientGame.getRegistry().garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            clientGame.getRegistry().getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            isGameOver = true;
        }*/
    }
}
