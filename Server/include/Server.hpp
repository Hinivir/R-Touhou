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
    void sendMessageToOtherClients(const std::string &message);
    void sendMessageToAllClients(const std::string &message);
    void sendMessageToClient(std::vector<std::pair<float, float>> &pos);
    bool handleCommand(std::array<char, 2048> buffer, size_t size);

    void handleMessageString();
    void handleMessageSetup(){ handleMessageString(); }

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
