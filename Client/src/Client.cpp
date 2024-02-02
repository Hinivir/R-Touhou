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
    char type = 'c';
    int id;
    float x;
    float y;

    friend std::ostream &operator<<(std::ostream &os, const positionMessage &message) {
        os << message.type << " " << message.id << " " << message.x << " " << message.y;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, positionMessage &message) {
        is >> message.type >> message.id >> message.x >> message.y;
        if (is.fail() || message.type != 'c') {
            throw std::runtime_error("Error while deserializing positionMessage");
        }
        return is;
    }
};

struct bulletMessage {
    char type = 'b';
    float x;
    float y;

    friend std::ostream &operator<<(std::ostream &os, const bulletMessage &message) {
        os << message.type << " " << message.x << " " << message.y;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, bulletMessage &message) {
        is >> message.type >> message.x >> message.y;
        if (is.fail() || message.type != 'b') {
            throw std::runtime_error("Error while deserializing bulletMessage");
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
    char type = 'i';
    std::size_t id;
    sf::Keyboard::Key key;

    friend std::ostream &operator<<(std::ostream &os, const inputMessage &message) {
        os << message.type << " " << message.id << " " << message.key;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, inputMessage &message) {
        is >> message.type >> message.id >> message.key;
        if (is.fail() || message.type != 'i') {
            throw std::runtime_error("Error while deserializing inputMessage");
        }
        return is;
    }
};

struct garbageMessage {
    char type = 'g';
    int id;

    friend std::ostream &operator<<(std::ostream &os, const garbageMessage &message) {
        os << message.type << " " << message.id;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, garbageMessage &message) {
        is >> message.type >> message.id;
        if (is.fail() || message.type != 'g') {
            throw std::runtime_error("Error while deserializing garbageMessage");
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

Client::Client(const std::string ip, const std::string port) : ANetwork::ANetwork(ip, port)
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

bool Client::deserializeBulletMessage() {
    try {
        bulletMessage message = deserialize<bulletMessage>(this->buffer);
        newBulletPosX = message.x;
        newBulletPosY = message.y;
        std::cout << "new bullet at " << newBulletPosX << " " << newBulletPosY << std::endl;
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
    while (pos.empty()) { }
    std::cout << "Game started: " << pos.size() << std::endl;
    isInChat = false;
    Game::ClientGame clientGame(this->playerNumber, 2048, 30);
    int nbRegistry = 2048;
    int totalScore = 0;
    bool isGameOver = false;
    int shootCoolDown = 0;
    int enemyCoolDown = 0;
    bool spawnEnemy = true;
    std::vector<GameEngine::Entity> entityVector;
    std::vector<GameEngine::Entity> playerVector;
    std::size_t my_player;

    // client
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Touhou");
    GameEngine::SystemGroup system;

    window.setFramerateLimit(60);
    for (std::size_t i = 0; i < playerNumber; i++) {
        GameEngine::Entity movableEntity = spawnMovableEntity(clientGame.getRegistry());
        if (i == myNumber - 1)
            my_player = i;
        entityVector.push_back(movableEntity);
        playerVector.push_back(movableEntity);
    }
    std::cout << "my_player: " << my_player << std::endl;

    GameEngine::Entity backgroundStar1 = createBackgroundStar(clientGame.getRegistry());
    entityVector.push_back(backgroundStar1);
    //
    std::cout << backgroundStar1 << std::endl;
    GameEngine::Entity backgroundStar2 = createBackgroundStar(clientGame.getRegistry());
    clientGame.getRegistry().getComponent<GameEngine::Position>()[backgroundStar2].value().x = 1920;
    entityVector.push_back(backgroundStar2);
    GameEngine::Entity groundDown = createGroundDown(clientGame.getRegistry());
    entityVector.push_back(groundDown);
    GameEngine::Entity groundUp = createGroundUp(clientGame.getRegistry());
    entityVector.push_back(groundUp);
    GameEngine::Entity score = createScore(clientGame.getRegistry());
    GameEngine::Entity gameOver = createGameOver(clientGame.getRegistry());
    GameEngine::Entity youWin = createYouWin(clientGame.getRegistry());

    system.initEnemy(clientGame.getRegistry(), pos);

    for (std::size_t i = 0; i < pos.size(); ++i) {
        GameEngine::Entity staticEntity = spawnEnemyEntity(clientGame.getRegistry());
        entityVector.push_back(staticEntity);
    }

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
                if (key == sf::Keyboard::Space && shootCoolDown != 7)
                    break;
                inputMessage message = {'i', my_player, key};
                std::array<char, 2048> sendBuffer;
                serialize<inputMessage>(message, sendBuffer);
                sendMessage<std::array<char, 2048>>(sendBuffer, this->serverEndpoint, false);
                break;
            }
        }

        clientGame.getRegistry().getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(totalScore));
        system.controlSystem(clientGame.getRegistry());

        if (shootCoolDown == 7) {
            system.attackSystem(clientGame.getRegistry(), entityVector);
            shootCoolDown = 0;
        }
        if (enemyCoolDown == 50 && spawnEnemy) {
            for (int i = 0; i < std::rand() % 31; ++i) {
                GameEngine::Entity staticEntity = spawnEnemyEntity(clientGame.getRegistry());
                entityVector.push_back(staticEntity);
            }
            enemyCoolDown = 0;
            system.initEnemy(clientGame.getRegistry());
        }
        enemyCoolDown++;
        shootCoolDown++;
        if (entityPos != -1) {
            std::cout << entityPos << std::endl;
            clientGame.getRegistry().getComponent<GameEngine::Position>()[entityVector.at(entityPos)].value().x = newPosX;
            clientGame.getRegistry().getComponent<GameEngine::Position>()[entityVector.at(entityPos)].value().y = newPosY;
            entityPos = -1;
        }
        if (newBulletPosX != -1) {
            GameEngine::Entity bullet = clientGame.getRegistry().spawnEntity();
            clientGame.getRegistry().addComponent<GameEngine::Size>(bullet, GameEngine::Size{10, 10});
            clientGame.getRegistry().addComponent<GameEngine::Position>(
                bullet, GameEngine::Position{
                            newBulletPosX, newBulletPosY + 50 / 2});
            clientGame.getRegistry().addComponent<GameEngine::Velocity>(bullet, GameEngine::Velocity{25.0f, 0.0f});
            clientGame.getRegistry().addComponent<GameEngine::Hitbox>(bullet, GameEngine::Hitbox{});
            clientGame.getRegistry().addComponent<GameEngine::Drawable>(bullet, GameEngine::Drawable{true});
            clientGame.getRegistry().addComponent<GameEngine::Sprite>(
                bullet, GameEngine::Sprite{"./../games/resources/R-Touhou/graphics/bullet.png",
                            sf::Sprite(), sf::Texture()});
            clientGame.getRegistry().addComponent<GameEngine::ZIndex>(
                bullet, GameEngine::ZIndex{GAME_ENGINE_Z_INDEX_VALUE_DEFAULT_VALUE - 1});
            clientGame.getRegistry().addComponent<GameEngine::Projectile>(bullet, GameEngine::Projectile{});
            clientGame.getRegistry().addComponent<GameEngine::Path>(
                bullet, GameEngine::Path{newBulletPosX, newBulletPosY, 1920 + 50, 1080 + 50});
            entityVector.push_back(bullet);
            newBulletPosX = -1;
            newBulletPosY = -1;
            std::cout << entityVector.size() << std::endl;
        }
        GameEngine::System::sprite(clientGame.getRegistry());
        GameEngine::System::draw(clientGame.getRegistry(), window);
        system.movementSystem(clientGame.getRegistry());
        system.collisionSystem(clientGame.getRegistry(), totalScore);
        system.deleteEntitiesSystem(clientGame.getRegistry());
        window.display();
        window.clear();

        if (totalScore == 100) {
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
        }
    }
}
