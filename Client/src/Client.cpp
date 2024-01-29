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
    this->isInSetup = true;
    this->isInChat = false;
    this->isInGame = false;
    // TODO: Setup game
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

void Client::commandFull() { std::cout << "Server is full" << std::endl; }

void Client::commandClientDisconnect() {
    playerNumber--;
}

void Client::manageMessage(std::string &message) {
    const std::string youArePlayer = "You are player ";

    if (strncmp(youArePlayer.c_str(), message.c_str(), youArePlayer.size()) == 0)
        this->playerNumber = std::stoi(message.substr(youArePlayer.size(), 1));
    else if (strcmp(NEW_CLIENT, message.c_str()) == 0)
        playerNumber++;
    std::cout << message << std::endl;
}

void Client::commandStartGame() {
    std::cout << "Game is starting" << std::endl;
    std::thread gameThread([&]() { runGame(); });
    gameThread.detach();
}

void Client::runGame() {
    receiveMessage(false);
    pos = deserialize<std::vector<std::pair<float, float>>>(this->buffer);
    for (auto &i : pos) {
        std::cout << i.first << "|" << i.second << std::endl;
    }
/*
    isInChat = false;
    Game::ClientGame clientGame(this->playerNumber, 2048, 30);
    int nbRegistry = 2048;
    int totalScore = 0;
    bool isGameOver = false;
    int shootCoolDown = 0;
//    int enemyCoolDown = 0;
    bool spawnEnemy = true;
    std::vector<GameEngine::Entity> entityVector;

    // client
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Touhou");
    GameEngine::SystemGroup system;

    window.setFramerateLimit(60);

    //loop for avery players
    GameEngine::Entity movableEntity = spawnMovableEntity(clientGame.getRegistry());
    entityVector.push_back(movableEntity);

    GameEngine::Entity backgroundStar1 = createBackgroundStar(clientGame.getRegistry());
    entityVector.push_back(backgroundStar1);
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

    //get message from server that gives us nb enemies and their position

//    system.initEnemy(registry);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            window.close();
        clientGame.getRegistry().getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(totalScore));
        system.controlSystem(clientGame.getRegistry());

        if (shootCoolDown == 7) {
            system.attackSystem(clientGame.getRegistry(), entityVector);
            shootCoolDown = 0;
        }
//        if (enemyCoolDown == 50 && spawnEnemy) {
//            for (int i = 0; i < std::rand() % 31; ++i) {
//                GameEngine::Entity staticEntity = spawnEnemyEntity(registry);
//                entityVector.push_back(staticEntity);
//            }
//            enemyCoolDown = 0;
//            system.initEnemy(registry);
//        }
//        enemyCoolDown++;
        shootCoolDown++;
        GameEngine::System::sprite(clientGame.getRegistry());
        GameEngine::System::draw(clientGame.getRegistry(), window);
        system.movementSystem(clientGame.getRegistry());
        system.collisionSystem(clientGame.getRegistry(), totalScore);
        system.deleteEntitiesSystem(clientGame.getRegistry());
        window.display();
        window.clear();

        if (totalScore == 100) {
//            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                clientGame.getRegistry().garbageEntities.push_back(entity);
            clientGame.getRegistry().garbageEntities.push_back(movableEntity);
            clientGame.getRegistry().garbageEntities.push_back(backgroundStar1);
            clientGame.getRegistry().garbageEntities.push_back(backgroundStar2);
            clientGame.getRegistry().garbageEntities.push_back(groundDown);
            clientGame.getRegistry().garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            clientGame.getRegistry().getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
        }
        if (!isGameOver && clientGame.getRegistry().getComponent<GameEngine::Life>()[movableEntity].value().life <= 0) {
//            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                clientGame.getRegistry().garbageEntities.push_back(entity);
            clientGame.getRegistry().garbageEntities.push_back(movableEntity);
            clientGame.getRegistry().garbageEntities.push_back(backgroundStar1);
            clientGame.getRegistry().garbageEntities.push_back(backgroundStar2);
            clientGame.getRegistry().garbageEntities.push_back(groundDown);
            clientGame.getRegistry().garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            clientGame.getRegistry().getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            isGameOver = true;
        }
    }
*/
}
