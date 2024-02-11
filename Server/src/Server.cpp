/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.cpp
*/

#include "Server.hpp"
#include "SparseArray.hpp"
#include "Registry.hpp"
#include "Macros/ForEach.hpp"
#include "Init.hpp"
#include "ServerGame.hpp"

#include <iostream>
#include <chrono>
#include <map>
#include <string>
#include <vector>
#include <variant>
#include <thread>

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

Server::~Server(void) { socket.close(); }

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

void Server::handleMessageSetup() {
    handleMessageString();
    playersReady += 1;
}

void Server::handleMessageGame()
{
    inputMessage input = deserialize<inputMessage>(buffer);
    std::cout << "input received: " << input << std::endl;
    std::size_t id = input.id;
    if (input.key == sf::Keyboard::Key::Up) {
        inputId = id;
        changeX = 0;
        changeY = -10;
    } else if (input.key == sf::Keyboard::Key::Down) {
        inputId = id;
        changeX = 0;
        changeY = 10;
    } else if (input.key == sf::Keyboard::Key::Left) {
        inputId = id;
        changeX = -10;
        changeY = 0;
    } else if (input.key == sf::Keyboard::Key::Right) {
        inputId = id;
        changeX = 10;
        changeY = 0;
    } else if (input.key == sf::Keyboard::Key::Space) {
        isNewBullet = true;
        bulletId = id;
    }
}


void Server::handleMessageGame(Game::ServerGame &game)
{
    try {
        inputMessage input = deserialize<inputMessage>(buffer);
        float x = game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x;
        float y = game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y;
        if (input.key == sf::Keyboard::Key::Up) {
            game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y -= 10;
            positionMessage toSend = {'p', int(input.id), x, y};
            sendMessageToAllClients<positionMessage>(toSend);
        } else if (input.key == sf::Keyboard::Key::Down) {
            game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().y += 10;
            positionMessage toSend = {'p', int(input.id), x, y};
            sendMessageToAllClients<positionMessage>(toSend);
        } else if (input.key == sf::Keyboard::Key::Left) {
            game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x -= 10;
            positionMessage toSend = {'p', int(input.id), x, y};
            sendMessageToAllClients<positionMessage>(toSend);
        } else if (input.key == sf::Keyboard::Key::Right) {
            game.getRegistry().getComponent<GameEngine::Position>()[input.id].value().x += 10;
            positionMessage toSend = {'p', int(input.id), x, y};
            sendMessageToAllClients<positionMessage>(toSend);
        } else if (input.key == sf::Keyboard::Key::Space) {
            ///////
            GameEngine::Entity bullet = createBullet(game.getRegistry(), x, y);
            game.getEntityVector().push_back(bullet);
            bulletVector.push_back(bullet);
            bulletMessage toSend = {'b', x, y};
            sendMessageToAllClients<bulletMessage>(toSend);
            ///////////
        }
    } catch (std::exception const &e) {
        garbageMessage toSend = deserialize<garbageMessage>(buffer);
        sendMessageToAllClients<garbageMessage>(toSend);
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

void Server::commandConnect()
{
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

void Server::commandDisconnect()
{
    sendMessage(DISCONNECTED, senderEndpoint, false);
    std::size_t idx = 0;

    for (const auto &client : clients) {
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

void Server::commandError() { sendMessage(ERROR_MSG, senderEndpoint, false); }

void Server::commandReady()
{
    clientsReady.push_back(senderEndpoint);
    sendMessage("Waiting other players...", senderEndpoint, false);
    sendMessage(READY, senderEndpoint, false);
}

void Server::commandFull() { sendMessage(SERVER_FULL, senderEndpoint, false); }

void Server::commandClientDisconnect() { sendMessageToOtherClients(CLIENT_DISCONNECTED); }

void Server::commandStartGame()
{
    if (clientsReady.size() != clients.size()) {
        return;
    }
    std::cout << "Starting game..." << std::endl;
    this->isInSetup = true;
    this->isInChat = false;
    sendMessageToAllClients(START_GAME);
    handleGame();
}

void Server::asyncReceive(Game::ServerGame &game)
{
    buffer.fill(0);
    socket.async_receive_from(
        asio::buffer(buffer), senderEndpoint, [this, &game](std::error_code const &error, std::size_t bytesReceived) {
            if (!error && bytesReceived > 0) {
                handleMessageGame(game);
                asyncReceive(game);
            } else {
                std::cerr << "Error in asyncReceive: " << error.message() << std::endl;
            }
        });
}

void Server::handleGame()
{
    Game::ServerGame serverGame(this->playerNumber, 2048, nbEnemies);
    GameEngine::SystemGroup system;

    for (std::size_t i = 0; i < playerNumber; i++) {
        GameEngine::Entity movableEntity = spawnMovableEntity(serverGame.getRegistry());
        playerVector.push_back(movableEntity);
        serverGame.getEntityVector().push_back(movableEntity);
    }

    for (int i = 0; i < nbEnemies; ++i) {
        GameEngine::Entity staticEntity = spawnEnemyEntity(serverGame.getRegistry());
        serverGame.getEntityVector().push_back(staticEntity);
        enemyVector.push_back(staticEntity);
    }

    std::vector<std::pair<float, float>> enemyPositionVector;
    for (std::size_t i = 0; i < nbEnemies; i++) {
        float x = rand() % 1080 + 1920;
        float y = rand() % 1000 - 50;
        while (y < 50)
            y += 50;
        while (x < 1030)
            x += 1030;
        enemyPositionVector.push_back(std::pair<float, float>{x, y});
    }
    for (std::size_t i = 0; i < enemyPositionVector.size(); ++i) {
        float x = enemyPositionVector[i].first;
        float y = enemyPositionVector[i].second;
        serverGame.getRegistry().getComponent<GameEngine::Position>()[enemyVector[i]].value().x = x;
        serverGame.getRegistry().getComponent<GameEngine::Position>()[enemyVector[i]].value().y = y;
    }
    sendMessageToAllClients<std::vector<std::pair<float, float>>>(enemyPositionVector);

    //setup des players
    while (playersReady != playerNumber) {
        receiveMessage(false);
    }

    score = createScore(serverGame.getRegistry());
    gameOver = createGameOver(serverGame.getRegistry());
    youWin = createYouWin(serverGame.getRegistry());

    for (auto &entity: serverGame.getEntityVector()) {
        float x = serverGame.getRegistry().getComponent<GameEngine::Position>()[entity].value().x;
        float y = serverGame.getRegistry().getComponent<GameEngine::Position>()[entity].value().y;
    }

    this->isInSetup = false;
    this->isInGame = true;

    runGame(serverGame, system);
}

void Server::runGame(Game::ServerGame &game, GameEngine::SystemGroup &system)
{
    asio::steady_timer timer(getIoContext());
    int totalScore = 0;
    bool isGameOver = false;
    int shootCoolDown = 0;
    int enemyCoolDown = 0;
    std::vector<int> garbageToSend;
    bool spawnEnemy = true;
    const int targetFps = 15; //reduce for lower framerate
    const std::chrono::duration<double> frameDuration(1.0 / targetFps);

    asyncReceive(game);
    asio::io_context &io_context(getIoContext());
    std::thread t([&io_context]() { io_context.run(); });
    while (1) {
        auto start_time = std::chrono::high_resolution_clock::now();
        game.getRegistry().getComponent<GameEngine::Text>()[score].value().string =
            ("Score: " + std::to_string(totalScore));

//        if (enemyCoolDown == 50 && spawnEnemy) {
//            for (int i = 0; i < std::rand() % 31; ++i) {
//                GameEngine::Entity staticEntity = spawnEnemyEntity(game.getRegistry());
////                game.getEntityVector().push_back(staticEntity);
//            }
//            enemyCoolDown = 0;
//            system.initEnemy(game.getRegistry());
//        }
//        enemyCoolDown++;

        system.movementSystem(game.getRegistry());
        system.collisionSystem(game.getRegistry(), totalScore, garbageToSend, playerVector, enemyVector, bulletVector);

        system.deleteEntitiesSystem(game.getRegistry(), garbageToSend);

        // win
        if (totalScore == 100) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : game.getEntityVector())
                game.getRegistry().garbageEntities.push_back(entity);
            for (const auto &entity : playerVector)
                game.getRegistry().garbageEntities.push_back(entity);
            game.getRegistry().getComponent<GameEngine::Drawable>()[youWin].value().isVisible = true;
        }

        // game over
        if (!isGameOver) {
            enemyCoolDown = 0;
            spawnEnemy = false;
            for (const auto &entity : game.getEntityVector())
                game.getRegistry().garbageEntities.push_back(entity);
            for (const auto &entity : playerVector)
                game.getRegistry().garbageEntities.push_back(entity);
            game.getRegistry().getComponent<GameEngine::Drawable>()[gameOver].value().isVisible = true;
            isGameOver = true;
        }

        //send packages to clients
        for (auto &entity: game.getEntityVector()) {
            //-if (std::find(game.getRegistry().garbageEntities.begin(), game.getRegistry().garbageEntities.end(), entity) != game.getRegistry().garbageEntities.end())
                //continue;
            positionMessage toSend = {
                'p',
                int(entity),
                game.getRegistry().getComponent<GameEngine::Position>()[entity].value().x,
                game.getRegistry().getComponent<GameEngine::Position>()[entity].value().y
            };
//            std::cout << toSend << std::endl;
            sendMessageToAllClients<positionMessage>(toSend);
        }

        //fps
        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);
        auto sleep_duration = frameDuration - elapsed_time;
        if (sleep_duration > std::chrono::duration<double>(0)) {
            timer.expires_after(std::chrono::duration_cast<std::chrono::steady_clock::duration>(sleep_duration));
            timer.wait();
        }
    }
}
