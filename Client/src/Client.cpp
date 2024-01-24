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

#define REGISTER_COMPONENT(COMPONENT) registry.registerComponent<COMPONENT>();

bool restartGame(GameEngine::Registry &registry, sf::RenderWindow &window, bool &isGameOver)
{
    registry.clear();
    isGameOver = false;
    return isGameOver;
}

Client::Client(const std::string ip, const std::string port): ANetwork::ANetwork(ip, port)
{
    try {
        this->serverEndpoint = asio::ip::udp::endpoint(asio::ip::make_address_v4(ip), std::stoi(port));
        this->socket.open(asio::ip::udp::v4());
        this->sendMessage("connect\n", this->serverEndpoint, false);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

Client::~Client()
{
    this->socket.close();
}

void Client::commandConnect()
{
    std::cout << "Connected to server" << std::endl;
}

void Client::commandDisconnect()
{
    std::cout << "Disconnected from server" << std::endl;
}

void Client::commandError()
{
    std::cout << "Error sending confirmation message to server" << std::endl;
}

void Client::commandReady()
{
    std::cout << "Ready to play" << std::endl;
    initGame();
}

void Client::commandFull()
{
    std::cout << "Server is full" << std::endl;
}

int Client::initGame()
{
    int nbRegistry = 2048;
    int totalScore = 0;
    bool isGameOver = false;
    int shootCoolDown = 0;
    int enemyCoolDown = 0;
    bool spawnEnemy = true;
    std::vector<GameEngine::Entity> entityVector;

    // client
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "R-Touhou");
    GameEngine::Registry registry(nbRegistry);
    GameEngine::System system;

    window.setFramerateLimit(60);

    // both
    /*GAME_ENGINE_FOR_EACH(REGISTER_COMPONENT, GameEngine::Color, GameEngine::Controllable, GameEngine::Drawable,
        GameEngine::Hitbox, GameEngine::Life, GameEngine::Path, GameEngine::Position, GameEngine::Projectile,
        GameEngine::Size, GameEngine::Sprite, GameEngine::SpriteTextureAnimation, GameEngine::SpriteTextureRect,
        GameEngine::Text, GameEngine::Velocity, GameEngine::ZIndex)*/

    registry.registerComponent<GameEngine::Color>();
    registry.registerComponent<GameEngine::Controllable>();
    registry.registerComponent<GameEngine::Drawable>();
    registry.registerComponent<GameEngine::Hitbox>();
    registry.registerComponent<GameEngine::Life>();
    registry.registerComponent<GameEngine::Outline>();
    registry.registerComponent<GameEngine::Path>();
    registry.registerComponent<GameEngine::Position>();
    registry.registerComponent<GameEngine::Projectile>();
    registry.registerComponent<GameEngine::Size>();
    registry.registerComponent<GameEngine::Sprite>();
    registry.registerComponent<GameEngine::SpriteTextureAnimation>();
    registry.registerComponent<GameEngine::SpriteTextureRect>();
    registry.registerComponent<GameEngine::Text>();
    registry.registerComponent<GameEngine::Velocity>();
    registry.registerComponent<GameEngine::ZIndex>();

    for (int i = 0; i < 4; i++) {
        GameEngine::Entity movableEntity = spawnMovableEntity(registry);
        registry.getComponent<GameEngine::Position>()[movableEntity].value().x = 250;
        registry.getComponent<GameEngine::Position>()[movableEntity].value().y = (i * 100 + registry.getComponent<GameEngine::Size>()[movableEntity].value().height) + (WINDOW_HEIGHT / 2);
        std::cout << "registry.getComponent<GameEngine::Position>()[movableEntity].value().y = " << registry.getComponent<GameEngine::Position>()[movableEntity].value().y << std::endl;
        entityVector.push_back(movableEntity);
    }
    GameEngine::Entity backgroundStar1 = createBackgroundStar(registry);
    entityVector.push_back(backgroundStar1);
    GameEngine::Entity backgroundStar2 = createBackgroundStar(registry);
    registry.getComponent<GameEngine::Position>()[backgroundStar2].value().x = 1920;
    entityVector.push_back(backgroundStar2);
    GameEngine::Entity groundDown = createGroundDown(registry);
    entityVector.push_back(groundDown);
    GameEngine::Entity groundUp = createGroundUp(registry);
    entityVector.push_back(groundUp);
    GameEngine::Entity score = createScore(registry);
    GameEngine::Entity gameOver = createGameOver(registry);
    GameEngine::Entity youWin = createYouWin(registry);

    for (int i = 0; i < std::rand() % 31; ++i) {
        GameEngine::Entity staticEntity = spawnEnemyEntity(registry);
        entityVector.push_back(staticEntity);
    }

    system.initEnemy(registry);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            window.close();
        registry.getComponent<GameEngine::Text>()[score].value().string = ("Score: " + std::to_string(totalScore));
        system.controlSystem(registry);

        if (shootCoolDown == 7) {
            system.attackSystem(registry, entityVector);
            shootCoolDown = 0;
        }
        if (enemyCoolDown == 50 && spawnEnemy) {
            for (int i = 0; i < std::rand() % 31; ++i) {
                GameEngine::Entity staticEntity = spawnEnemyEntity(registry);
                entityVector.push_back(staticEntity);
            }
            enemyCoolDown = 0;
            system.initEnemy(registry);
        }
        enemyCoolDown++;
        shootCoolDown++;
        system.spriteSystem(registry);
        system.drawSystem(registry, window);
        system.movementSystem(registry);
        system.collisionSystem(registry, totalScore);
        system.deleteEntitiesSystem(registry);
        window.display();
        window.clear();

        if (totalScore == 100) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                registry.garbageEntities.push_back(entity);
            //registry.garbageEntities.push_back(movableEntity);
            registry.garbageEntities.push_back(backgroundStar1);
            registry.garbageEntities.push_back(backgroundStar2);
            registry.garbageEntities.push_back(groundDown);
            registry.garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            registry.getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
        }
        /*if (!isGameOver && registry.getComponent<GameEngine::Life>()[movableEntity].value().life <= 0) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : entityVector)
                registry.garbageEntities.push_back(entity);
            registry.garbageEntities.push_back(movableEntity);
            registry.garbageEntities.push_back(backgroundStar1);
            registry.garbageEntities.push_back(backgroundStar2);
            registry.garbageEntities.push_back(groundDown);
            registry.garbageEntities.push_back(groundUp);
            window.clear(sf::Color::Black);
            registry.getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            isGameOver = true;
        }*/
    }
    return 0;
}

static const std::map<std::string, std::function<void(Client &)>> clientCommandHandler = {
    {CONNECTED, &Client::commandConnect},
    {DISCONNECTED, &Client::commandDisconnect},
    {ERROR_MSG, &Client::commandError},
    {READY, &Client::commandReady},
    {SERVER_FULL, &Client::commandFull},
};

void Client::handleMessageClient(std::string &message)
{
    std::cout << "message = " << message << std::endl;
    for (auto &command : clientCommandHandler) {
        if (message.find(command.first) != std::string::npos) {
            command.second(*this);
            break;
        }
    }
}
