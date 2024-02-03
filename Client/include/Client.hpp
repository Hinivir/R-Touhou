/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <cstdlib>
#include <array>

#include <asio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "SparseArray.hpp"

#include "Components/Components.hpp"
#include "Entity.hpp"
#include "ANetwork.hpp"

class Client : public ANetwork
{
  private:
    asio::ip::udp::endpoint senderEndpoint;
    std::size_t myNumber = 0;

    int entityPos = -1;
    float newPosX = 0;
    float newPosY = 0;

    float newBulletPosX = -1;
    float newBulletPosY = -1;
    std::vector<int> garbageToSend;
    std::vector<int> garbageToAdd;

  public:
    asio::ip::udp::endpoint serverEndpoint;
    std::vector<std::pair<float, float>> pos;
    Client(const std::string ip, const std::string port);
    ~Client();

    void handleMessageString();
    void handleMessageSetup();
    void handleMessageGame();

    bool deserializePositionMessage();
    bool deserializeInputMessage();
    bool deserializeGarbageMessage();
    bool deserializeBulletMessage();
    void managePackageGame();

    std::vector<std::function<bool()>> deserializeFunctions = {[this]() { return this->deserializePositionMessage(); },
        [this]() { return this->deserializeInputMessage(); }, [this]() { return this->deserializeGarbageMessage(); },
        [this]() { return this->deserializeBulletMessage(); }};

    void commandConnect();
    void commandDisconnect();
    void commandError();
    void commandReady();
    void commandFull();
    void commandClientDisconnect();
    void commandStartGame();

    void manageMessage(std::string &);
    void handleGame();
};
#endif
