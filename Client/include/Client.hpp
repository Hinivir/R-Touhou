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

  public:
    asio::ip::udp::endpoint serverEndpoint;
    std::vector <std::pair<float, float>> pos;
    Client(const std::string ip, const std::string port);
    ~Client();

    void handleMessageString();
    void handleMessageSetup();
    void handleMessageGame();

    bool deserializePositionMessage();
    bool deserializeInputMessage();
    bool deserializeGarbageMessage();
    void managePackageGame();

    std::vector<std::function<bool()>> deserializeFunctions = {
      [this]() { return this->deserializePositionMessage(); },
      [this]() { return this->deserializeInputMessage(); },
      [this]() { return this->deserializeGarbageMessage(); }
    };

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
