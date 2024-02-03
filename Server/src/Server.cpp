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
#include "Init.hpp"
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
    char type = 'p';
    int id;
    float x;
    float y;

    friend std::ostream &operator<<(std::ostream &os, const positionMessage &message) {
        os << message.type << " " << message.id << " " << message.x << " " << message.y;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, positionMessage &message) {
        is >> message.type >> message.id >> message.x >> message.y;
        if (is.fail() || message.type != 'p') {
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

Server::Server(const std::string &ip, const std::string &port) : ANetwork::ANetwork(ip, port)
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
    try {
        inputMessage input = deserialize<inputMessage>(buffer);
        float x = game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x;
        float y = game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y;
        if (input.key == sf::Keyboard::Key::Up) {
            std::cout << "player " << input.id << " moved from " << x;
            game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y -= 10;
            std::cout << " to " << game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y << std::endl;
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
    } catch (std::exception const &e) {
        garbageMessage toSend = deserialize<garbageMessage>(buffer);
        std::cout << buffer.data() << std::endl;
        sendMessageToOtherClients<garbageMessage>(toSend);
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
    // TODO: need to setup Game
    this->isInChat = false;
    this->isInSetup = true;
    this->isInGame = false;

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
    std::size_t nbEnemies = 30;
    Game::ServerGame serverGame(this->playerNumber, 2048, nbEnemies);
    int nbRegistry = 2048;
    int totalScore = 0;
    bool isGameOver = false;
    int shootCoolDown = 0;
    int enemyCoolDown = 0;
    bool spawnEnemy = true;
    std::vector<GameEngine::Entity> enemyVector;

    GameEngine::SystemGroup system;

    for (std::size_t i = 0; i < playerNumber; i++) {
        GameEngine::Entity movableEntity = spawnMovableEntity(serverGame.getRegistry());
        serverGame.getEntityVector().push_back(movableEntity);
    }
    GameEngine::Entity backgroundStar1 = createBackgroundStar(serverGame.getRegistry());
    serverGame.getEntityVector().push_back(backgroundStar1);
    GameEngine::Entity backgroundStar2 = createBackgroundStar(serverGame.getRegistry());
    serverGame.getRegistry().getComponent<GameEngine::Position>()[backgroundStar2].value().x = 1920;
    serverGame.getEntityVector().push_back(backgroundStar2);
    GameEngine::Entity groundDown = createGroundDown(serverGame.getRegistry());
    serverGame.getEntityVector().push_back(groundDown);
    GameEngine::Entity groundUp = createGroundUp(serverGame.getRegistry());
    serverGame.getEntityVector().push_back(groundUp);
    GameEngine::Entity score = createScore(serverGame.getRegistry());
    GameEngine::Entity gameOver = createGameOver(serverGame.getRegistry());
    GameEngine::Entity youWin = createYouWin(serverGame.getRegistry());

    for (int i = 0; i < nbEnemies; ++i) {
        GameEngine::Entity staticEntity = spawnEnemyEntity(serverGame.getRegistry());
        serverGame.getEntityVector().push_back(staticEntity);
        enemyVector.push_back(staticEntity);
    }
    //  get message from server that gives us nb enemies and their position

    //generate random pos
    std::vector<std::pair<float, float>> enemyPositionVector;
    for (std::size_t i = 0; i < nbEnemies; i++) {
        float x = rand() % 1080 + 1920;
        float y = rand() % 1000 - 50;
        while (x < 50)
            x += 50;
        while (y < 1030)
            y += 1030;
        enemyPositionVector.push_back(std::pair<float, float>{x, y});
    }
    system.initEnemy(serverGame.getRegistry(), enemyPositionVector);
    sendMessageToAllClients<std::vector<std::pair<float, float>>>(enemyPositionVector);

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
//        test = !test;
    }
}
