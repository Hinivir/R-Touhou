/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include "ClientGame.hpp"
#include "Systems/Draw.hpp"
#include "Systems/Sprite.hpp"

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
    // TODO: Setup game
    sendMessage<std::string>("start game\n", this->serverEndpoint, false);
}

void Client::handleMessageString() {
    std::string message = getBuffer().data();
    if (message.find("You are player ") == 0)
        this->playerNumber = std::stoi(message.substr(15, 1));
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

void Client::commandFull() { std::cout << "Server is full" << std::endl; }

void Client::commandClientDisconnect() {
    playerNumber--;
}

void Client::manageMessage(std::string &message) {
    const std::string youArePlayer = "You are player ";
    const std::string playerNumberMsg = "Number of players: ";

    if (strncmp(youArePlayer.c_str(), message.c_str(), youArePlayer.size()) == 0)
        this->playerNumber = std::stoi(message.substr(youArePlayer.size(), 1));
    else if (strcmp(NEW_CLIENT, message.c_str()) == 0)
        playerNumber++;
    else if (strncmp(playerNumberMsg.c_str(), message.c_str(), playerNumberMsg.size()) == 0)
        playerNumber = std::stoi(message.substr(playerNumberMsg.size(), 1));
    std::cout << message << std::endl;
}

void Client::commandStartGame() {
    std::cout << "Game is starting" << std::endl;
    this->isInSetup = true;
    this->isInChat = false;
    while (this->clientGame.getEnemiesPosPair().empty()) { }
    this->clientGame.init(this->playerNumber, 2048, this->clientGame.getEnemiesPosPair().size());
    this->clientGame.setup();
    this->clientGame.myPlayer = this->myPlayer;

    std::thread gameThread([&]() { this->handleGame(); });
    gameThread.detach();
}

void Client::handleGame() {
    for (auto &i : this->clientGame.getEnemiesPosPair())
        std::cout << i.first << " | " << i.second << std::endl;
    isInChat = false;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Touhou");
    window.setFramerateLimit(60);
    this->clientGame.getSystemGroup().initEnemy(clientGame.getRegistry(), this->clientGame.getEnemiesPosPair());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            window.close();

        //clientGame.getRegistry().getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(totalScore));
        //this->clientGame.getSystemGroup().controlSystem(clientGame.getRegistry());

        /*if (shootCoolDown == 7) {
            system.attackSystem(clientGame.getRegistry(), entityVector);
            shootCoolDown = 0;
        }*/
        /*if (enemyCoolDown == 50 && spawnEnemy) {
            for (int i = 0; i < std::rand() % 31; ++i) {
                GameEngine::Entity staticEntity = this->clientGame.spawnEnemyEntity(clientGame.getRegistry());
                entityVector.push_back(staticEntity);
            }
            enemyCoolDown = 0;
            system.initEnemy(clientGame.getRegistry());
        }
        enemyCoolDown++;
        shootCoolDown++;*/

        GameEngine::System::sprite(clientGame.getRegistry());
        GameEngine::System::draw(clientGame.getRegistry(), window);

        //this->clientGame.getSystemGroup().movementSystem(clientGame.getRegistry());
        //system.collisionSystem(clientGame.getRegistry(), totalScore);
        //this->clientGame.getSystemGroup().deleteEntitiesSystem(clientGame.getRegistry());

        window.display();
        window.clear();
/*
        if (totalScore == 100) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                clientGame.getRegistry().garbageEntities.push_back(entity);
            window.clear(sf::Color::Black);
            clientGame.getRegistry().getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
        }
        if (!isGameOver && clientGame.getRegistry().getComponent<GameEngine::Life>()[this->clientGame.myPlayer].value().life <= 0) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                clientGame.getRegistry().garbageEntities.push_back(entity);
            window.clear(sf::Color::Black);
            clientGame.getRegistry().getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            isGameOver = true;
        }
        */
    }
}
