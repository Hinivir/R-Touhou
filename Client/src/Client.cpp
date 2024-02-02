/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include <iostream>
#include <map>
#include <variant>
#include <string>
#include <vector>

#include "Registry.hpp"
#include "Systems.hpp"
#include "Client.hpp"
#include "ClientGame.hpp"
#include "Systems/Draw.hpp"
#include "Systems/Sprite.hpp"

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
    this->clientGame.getEnemiesPosPair() = deserialize<std::vector<std::pair<float, float>>>(this->buffer);
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

bool Client::deserializeBulletMessage() {
    try {
        bulletMessage message = deserialize<bulletMessage>(this->buffer);
        newBulletPosX = message.x;
        newBulletPosY = message.y;
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
//        std::cerr << e.what() << std::endl;
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
    this->isInChat = false;
    this->isInSetup = true;
    std::thread gameThread([&]() { this->handleGame(); });
    gameThread.detach();
}

void Client::handleGame() {
    this->clientGame.init(this->playerNumber, 2048, 20);
    while (this->clientGame.getEnemiesPosPair().size() != 20) { }
    for (auto pos : this->clientGame.getEnemiesPosPair()) {
        std::cout << "pos: " << pos.first << " " << pos.second << std::endl;
    }
    std::cout << "Game started: " << this->clientGame.getEnemiesPosPair().size() << std::endl;
    std::size_t my_player = this->playerNumber;
    this->clientGame.setup();

    /*for (auto pos : this->clientGame.getEnemiesPosPair()) {
        std::cout << "pos: " << pos.first << " " << pos.second << std::endl;
    }*/
    this->clientGame.getSystemGroup().initEnemy(clientGame.getRegistry(), this->clientGame.getEnemiesPosPair());

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


    this->isInSetup = false;
    this->isInGame = true;
    while (window.isOpen()) {
        sf::Event event;

        //close window
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            window.close();

        //input inGame
        for (auto const &key: kepMap) {
            if (sf::Keyboard::isKeyPressed(key)) {
                if (key == sf::Keyboard::Space && this->clientGame.shootCoolDown != 7)
                    break;
                inputMessage message = {'i', my_player, key};
                std::array<char, 2048> sendBuffer;
                serialize<inputMessage>(message, sendBuffer);
                sendMessage<std::array<char, 2048>>(sendBuffer, this->serverEndpoint, false);
                break;
            }
        }

        //clientGame.getRegistry().getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(totalScore));
//        system.controlSystem(clientGame.getRegistry());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            if (clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(my_player)].value().y > 0)
                clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(my_player)].value().y -= 10;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            if (clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(my_player)].value().y < WINDOW_HEIGHT - 50)
                clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(my_player)].value().y += 10;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            if (clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(my_player)].value().x > 0)
                clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(my_player)].value().x -= 10;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            if (clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(my_player)].value().x < WINDOW_WIDTH - 50)
                clientGame.getRegistry().getComponent<GameEngine::Position>()[this->clientGame.getEntityVector().at(my_player)].value().x += 10;

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
            this->clientGame.getEntityVector().push_back(bullet);
            newBulletPosX = -1;
            newBulletPosY = -1;
            std::cout << this->clientGame.getEntityVector().size() << std::endl;
        }

        //draw
        GameEngine::System::sprite(clientGame.getRegistry());
        GameEngine::System::draw(clientGame.getRegistry(), window);
        this->clientGame.getSystemGroup().movementSystem(clientGame.getRegistry());
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

        //game over
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
