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
#include <fstream>

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

Client::~Client()
{
    if (this->socket.is_open())
        this->socket.close();
}

void Client::commandConnect() { std::cout << "Connected to server" << std::endl; }

void Client::commandDisconnect()
{
    std::cout << "Disconnected from server" << std::endl;
    this->running = false;
    if (this->socket.is_open())
        this->socket.close();
}

void Client::commandError() { std::cout << "Error sending confirmation message to server" << std::endl; }

void Client::commandReady() { sendMessage<std::string>("start game\n", this->serverEndpoint, false); }

void Client::handleMessageString()
{
    std::string message = getBuffer().data();
    for (auto &command : clientCommandHandler) {
        if (message.find(command.first) != std::string::npos) {
            command.second(*this);
            return;
        }
    }
    manageMessage(message);
}

void Client::handleMessageSetup() { pos = deserialize<std::vector<std::pair<float, float>>>(this->buffer); }

bool Client::deserializePositionMessage()
{
    try {
        positionMessage message = deserialize<positionMessage>(this->buffer);
        if (receivePackage)
            posToUpdate.push_back(message);
    } catch (std::exception &e) {
        return false;
    }
    return true;
}

bool Client::deserializeInputMessage()
{
    try {
        inputMessage message = deserialize<inputMessage>(this->buffer);
    } catch (std::exception &e) {
        return false;
    }
    return true;
}

bool Client::deserializeGarbageMessage()
{
    try {
        garbageMessage message = deserialize<garbageMessage>(this->buffer);
        garbageToAdd.push_back(message.id);
    } catch (std::exception &e) {
        return false;
    }
    return true;
}

bool Client::deserializeBulletMessage()
{
    try {
        bulletMessage message = deserialize<bulletMessage>(this->buffer);
        if (receivePackage)
            newBullets.push_back(message);
    } catch (std::exception &e) {
        return false;
    }
    return true;
}

bool Client::deserializeScoreMessage()
{
    try {
        scoreMessage message = deserialize<scoreMessage>(this->buffer);
        totalScore += 5;
    } catch (std::exception &e) {
        return false;
    }
    return true;

}

void Client::managePackageGame()
{
    for (auto &deserializeFunction : deserializeFunctions) {
        if (deserializeFunction())
            return;
    }
    std::cout << "Error while deserializing" << std::endl;
}

void Client::handleMessageGame() { managePackageGame(); }

void Client::commandFull() { std::cout << "Server is full" << std::endl; }

void Client::commandClientDisconnect() { playerNumber--; }

void Client::manageMessage(std::string &message)
{
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

void Client::commandStartGame()
{
    std::cout << "Game is starting" << std::endl;
    std::thread gameThread([&]() { this->handleGame(); });
    gameThread.detach();
}

void Client::handleGame()
{
    std::ofstream file(".highscore", std::ios_base::app);
    this->isInSetup = true;
    this->isInChat = false;
    while (pos.size() < 30) { }
    std::cout << "Game started" << std::endl;
    isInChat = false;
    Game::ClientGame clientGame(this->playerNumber, 2048, 30);
    int nbRegistry = 2048;
    bool isGameOver = false;
    int shootCoolDown = 0;
    std::vector<GameEngine::Entity> entityVector;
    std::vector<GameEngine::Entity> enemyVector;
    std::vector<GameEngine::Entity> playerVector;
    std::vector<GameEngine::Entity> localVector;
    std::vector<int> deadPlayerVector;
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

    GameEngine::Entity backgroundStar1 = createBackgroundStar(clientGame.getLocalRegistry());
    localVector.push_back(backgroundStar1);
    GameEngine::Entity backgroundStar2 = createBackgroundStar(clientGame.getLocalRegistry());
    clientGame.getLocalRegistry().getComponent<GameEngine::Position>()[backgroundStar2].value().x = 1920;
    localVector.push_back(backgroundStar2);
    GameEngine::Entity groundDown = createGroundDown(clientGame.getLocalRegistry());
    localVector.push_back(groundDown);
    GameEngine::Entity groundUp = createGroundUp(clientGame.getLocalRegistry());
    localVector.push_back(groundUp);
    std::size_t deadPlayers = 0;

    for (int i = 0; i < 30; ++i) {
        GameEngine::Entity staticEntity = spawnEnemyEntity(clientGame.getRegistry());
        entityVector.push_back(staticEntity);
        enemyVector.push_back(staticEntity);
    }

    for (std::size_t i = 0; i < pos.size(); ++i) {
        float x = pos[i].first;
        float y = pos[i].second;
        clientGame.getRegistry().getComponent<GameEngine::Position>()[enemyVector[i]].value().x = x;
        clientGame.getRegistry().getComponent<GameEngine::Position>()[enemyVector[i]].value().y = y;
    }

    GameEngine::Entity score = createScore(clientGame.getRegistry());

    GameEngine::Entity gameOver = createGameOver(clientGame.getLocalRegistry());
    GameEngine::Entity youWin = createYouWin(clientGame.getLocalRegistry());
    sendMessage<std::string>("got\n", this->serverEndpoint, false);

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

        // input inGame
        if (isAlive) {
            for (auto const &key : kepMap) {
                if (sf::Keyboard::isKeyPressed(key)) {
                    if (key == sf::Keyboard::Space && shootCoolDown < 7)
                        break;
                    else if (key == sf::Keyboard::Space && shootCoolDown >= 7)
                        shootCoolDown = 0;
                    inputMessage message = {'i', my_player, key};
                    std::array<char, 2048> sendBuffer;
                    serialize<inputMessage>(message, sendBuffer);
                    sendMessage<std::array<char, 2048>>(sendBuffer, this->serverEndpoint, false);
                    break;
                }
            }
        }
        shootCoolDown++;
        clientGame.getRegistry().getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(totalScore));

        receivePackage = false;

        while (garbageToAdd.size() > 0) {
            int id = garbageToAdd.back();
            if (id == my_player)
                isAlive = false;
            if (
                find(playerVector.begin(), playerVector.end(), id) != playerVector.end() &&
                find(deadPlayerVector.begin(), deadPlayerVector.end(), id) == deadPlayerVector.end()
            ) {
                deadPlayers += 1;
                deadPlayerVector.push_back(id);
                }
            garbageToAdd.pop_back();
            clientGame.getRegistry().garbageEntities.push_back(id);
        }

        while (newBullets.size() > 0) {
            bulletMessage message = newBullets.back();
            newBullets.pop_back();
            GameEngine::Entity bullet = createBullet(clientGame.getRegistry(), message.x, message.y);
            entityVector.push_back(bullet);
        }

        while (posToUpdate.size() > 0) {
            positionMessage message = posToUpdate.back();
            posToUpdate.pop_back();
            if (message.id > entityVector.size())
                continue;
            clientGame.getRegistry().getComponent<GameEngine::Position>()[message.id].value().x = message.x;
            clientGame.getRegistry().getComponent<GameEngine::Position>()[message.id].value().y = message.y;
        }
        receivePackage = true;

        // win
        if (totalScore >= 100) {
            window.clear(sf::Color::Black);
            clientGame.getLocalRegistry().getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
            file << "1OO - WIN" << std::endl;
            file.close();
        } else if (deadPlayers == playerNumber) {
            isGameOver = true;
            window.clear(sf::Color::Black);
            clientGame.getLocalRegistry().getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            file << std::to_string(totalScore) << " - GAME OVER" << std::endl;
            file.close();
        }
        // draw
        GameEngine::System::sprite(clientGame.getLocalRegistry());
        GameEngine::System::draw(clientGame.getLocalRegistry(), window);
        if (!isGameOver && totalScore < 100) {
            GameEngine::System::sprite(clientGame.getRegistry());
            GameEngine::System::draw(clientGame.getRegistry(), window);
        }
        window.display();
        window.clear();
    }
}
