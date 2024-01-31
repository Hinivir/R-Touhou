/*
** EPITECH PROJECT, 2023
** R-Touhou
** File description:
** Server.hpp
*/

#ifndef R_TYPE_SERVER_HPP
#define R_TYPE_SERVER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <asio.hpp>
#include "ANetwork.hpp"

class Server : protected ANetwork
{
  private:
    std::size_t _port;
    std::size_t maxPlayers = 4;
    std::vector<asio::ip::udp::endpoint> clients;
    std::vector<asio::ip::udp::endpoint> clientsReady;
    std::vector<asio::ip::udp::endpoint> clientsSetup;
    std::map<asio::ip::udp::endpoint, int> playerNumberMap;


  public:
    Server(const std::string &ip, const std::string &port);
    ~Server();
    void manageServer();
    void verifConnected();
    bool handleCommand(std::array<char, 2048> buffer, size_t size);

    void sendMessageStringToAllClients(const std::string& message)
    {
        for (const auto& client : clients)
            sendMessage<std::string>(message, client, false);
    }

    void sendMessageStringToOtherClients(const std::string& message)
    {
        for (const auto& client : clients)
            if (client != senderEndpoint)
                sendMessage<std::string>(message, client, false);
    }

    template<typename messageClient>
    void sendMessageToOtherClients(messageClient& pos)
    {
        std::array<char, 2048> buffer;

        serialize<messageClient>(pos, buffer);
        for (const auto& client : clients)
            if (client != senderEndpoint)
                sendMessage<std::array<char, 2048>>(buffer, client, false);
    }

    template<typename messageClient>
    void sendMessageToAllClients(messageClient & pos)
    {
        std::array<char, 2048> buffer;

        serialize<messageClient>(pos, buffer);
        for (const auto& client : clients)
            sendMessage<std::array<char, 2048>>(buffer, client, false);
    }

    void handleMessageString();
    void handleMessageSetup(){ handleMessageString(); }
    void handleMessageGame(){ handleMessageString(); }

    // command functions herited from ANetwork
    void commandConnect();
    void commandDisconnect();
    void commandError();
    void commandReady();
    void commandFull();
    void commandClientDisconnect();
    void commandStartGame();

    void handleGame();
};

#endif // R_TYPE_SERVER_HPP
