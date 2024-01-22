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

template <typename senderMessage>
struct inGame_message {
    std::size_t index;
    senderMessage message;
};

struct outGame_message {
    asio::ip::udp::endpoint senderEndpoint;
    std::string &message;
};

class ANetwork {
    protected:
        std::array<char, 2048> buffer;
        std::string ip;
        std::string port;
        asio::io_context ioContext;
        asio::ip::udp::socket socket;
        asio::ip::udp::endpoint senderEndpoint;

    public:
        ANetwork(const std::string ip, const std::string port): ioContext(), socket(ioContext) {
            this->ip = ip;
            this->port = port;
        }

        void sendMessage(const std::string &message, const asio::ip::udp::endpoint &receiverEndpoint, bool async) {
            if (async) {
                socket.async_send_to(asio::buffer(message), receiverEndpoint,
                    [](const asio::error_code &error, std::size_t bytes_transferred) {
                        if (error) {
                            std::cerr << "ERROR: " << error.message() << std::endl;
                            return;
                        }
                    }
                );
            } else {
                socket.send_to(asio::buffer(message), receiverEndpoint);
            }
        }

        outGame_message receiveMessage(asio::ip::udp::endpoint &senderEndpoint, bool async) {
            if (async) {
                socket.async_receive_from(asio::buffer(asio::buffer(buffer)), senderEndpoint,
                    [](const asio::error_code &error, std::size_t bytes_transferred) {
                        if (error) {
                            std::cerr << "ERROR: " << error.message() << std::endl;
                            return;
                        }
                    }
                );
            } else {
                socket.receive_from(asio::buffer(buffer), senderEndpoint);
            }
            std::cout << "From " << senderEndpoint.address().to_string() << ": " << buffer.data() << std::endl;
            outGame_message res = {senderEndpoint, *(new std::string(buffer.data()))};
            buffer.fill(0);
            return res;
        }
};
#endif
