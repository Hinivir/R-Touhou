/*
** EPITECH PROJECT, 2023
** r-type-mirror
** File description:
** ANetwork.hpp
*/

#ifndef ANETWORK_HPP
#define ANETWORK_HPP

#include <iostream>
#include <array>

#include <asio.hpp>
#include <map>

#define CONNECTED "101: You are connected!\n"
#define DISCONNECTED "103: You are disconnected!\n"
#define ERROR_MSG "102: Error sending confirmation message to client!\n"
#define READY "104: You are ready!\n"
#define SERVER_FULL "105: Server is full!\n"

template <typename senderMessage>
struct inGame_message
{
    std::size_t index;
    senderMessage message;
};

struct outGame_message
{
    asio::ip::udp::endpoint senderEndpoint;
    std::string &message;
};

class ANetwork {
    protected:
        std::array<char, 2048> buffer;
        std::string ip;
        std::string port;
        std::size_t bytesReceived;
        asio::io_context ioContext;
        asio::ip::udp::socket socket;
        asio::ip::udp::endpoint senderEndpoint;

        const std::map<std::string, std::function<void(ANetwork &)>> clientCommandHandler = {
            {CONNECTED, &ANetwork::commandConnect},
            {DISCONNECTED, &ANetwork::commandDisconnect},
            {ERROR_MSG, &ANetwork::commandError},
            {READY, &ANetwork::commandReady},
            {SERVER_FULL, &ANetwork::commandFull},
        };

  public:
    ANetwork(const std::string ip, const std::string port) : ioContext(), socket(ioContext)
    {
        this->ip = ip;
        this->port = port;
    }

    template<typename messageTemplate>
    void sendMessage(const messageTemplate &message, const asio::ip::udp::endpoint &receiverEndpoint, bool async)
    {
        if (async) {
            socket.async_send_to(asio::buffer(message), receiverEndpoint,
                [](const asio::error_code &error, std::size_t bytes_transferred) {
                    if (error) {
                        std::cerr << "ERROR: " << error.message() << std::endl;
                        return;
                    }
                });
        } else {
            socket.send_to(asio::buffer(message), receiverEndpoint);
        }
    }

    template<typename messageTemplate>
    void receiveMessage(bool async)
    {
        buffer.fill(0);
        if (async) {
            socket.async_receive_from(asio::buffer(buffer), senderEndpoint,
                [this](const asio::error_code &error, std::size_t bytes_transferred) {
                    if (!error) {
                        messageTemplate message = messageTemplate(buffer.begin(), buffer.begin() + bytes_transferred);
                        handleMessage<messageTemplate>(false, message);
                        receiveMessage<messageTemplate>(true);
                        //return buffer;
                    } else {
                        std::cerr << "ERROR: " << error.message() << std::endl;
                    }
                });
        } else {
            socket.receive_from(asio::buffer(buffer), senderEndpoint);
            //return buffer;
        }
    }

    template<typename messageTemplate>
    void handleMessage(bool isServer, messageTemplate &message)
    {
        if (isServer) {
            std::cout << "Server" << std::endl;
        } else {
            handleMessageClient<messageTemplate>(message);
        }
    }

    template<typename messageTemplate>
    void handleMessageClient(messageTemplate &message) {
        if (typeid(message) == typeid(std::string)) {
            std::cout << "message = " << message << std::endl;
            for (auto &command : clientCommandHandler) {
                if (message.find(command.first) != std::string::npos) {
                    command.second(*this);
                    break;
                }
            }
        } else {
            std::cout << "message is not a string" << std::endl;
        }
    }

    void commandConnect() { std::cout << "Connected to server" << std::endl; }
    void commandDisconnect() { std::cout << "Disconnected from server" << std::endl; }
    void commandError() { std::cout << "Error sending confirmation message to server" << std::endl; }
    void commandReady() { std::cout << "Ready to play" << std::endl; }
    void commandFull() { std::cout << "Server is full" << std::endl; }

    asio::io_context &getIoContext() { return this->ioContext; }
    std::array<char, 2048> getBuffer() { return this->buffer; }
};
#endif

