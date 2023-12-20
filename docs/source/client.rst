Client Documentation
====================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

Client.hpp
------------------------------------

.. code:: cpp

    #ifndef CLIENT_HPP
    #define CLIENT_HPP

        #include <iostream>
        #include <queue>
        #include <asio.hpp>

        class Client {
        private:
            asio::ip::udp::socket socket_; // socket for the client
            asio::ip::udp::endpoint server_endpoint_; // endpoint for the server
            std::queue<std::string> _messageQueue; // queue for the messages

        public:
            // constructor and destructor
            Client(asio::io_context& io_context, const std::string& server_ip, std::size_t server_port);
            ~Client();
            // the function to send a message
            void sendMessage(const std::string& message);
            // the function to get the new message
            void getNewMessage(void);
            // the function to run the client
            void runClient(void);
    };

    #endif

The hpp file for the client

Client.cpp : Include
------------------------------------

.. code:: cpp

    #include "../include/Client.hpp"
    #include <iostream>
    #include <map>
    #include <string>

The include of the client

Client.cpp : inputHandler
------------------------------------

.. code:: cpp

    static const std::map<char, std::string> inputHandler = {
        {'z', "UP"},
        {'s', "DOWN"},
        {'q', "LEFT"},
        {'d', "RIGHT"},
        {' ', "ACTION"},
        {27, "QUIT"}
    };

The map for the input handler that transform the input into a message

Client.cpp : Client::Client
------------------------------------

.. code:: cpp

    Client::Client(asio::io_context& io_context, const std::string& server_ip, std::size_t server_port)
        : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
            server_endpoint_(asio::ip::address::from_string(server_ip), server_port) {}

The constructor of the client that take the io_context, the server ip and the server port

Client.cpp : Client::~Client
------------------------------------

.. code:: cpp

    Client::~Client() {}

The destructor of the client

Client.cpp : Client::sendMessage
------------------------------------

.. code:: cpp

    void Client::sendMessage(const std::string& message) {
        // send the message to the server
        socket_.send_to(asio::buffer(message), server_endpoint_);
    }

The function to send a message to the server

Client.cpp : Client::getNewMessage
------------------------------------

.. code:: cpp

    void Client::getNewMessage(void) {
        // the buffer for the message
        std::array<char, 1024> recv_buf = {0};
        // asio error code
        asio::error_code error;
        // receive the message from the server
        std::size_t len = socket_.receive_from(asio::buffer(recv_buf), server_endpoint_, 0, error);
        // if there is an error
        if (error && error != asio::error::message_size)
            // throw the error
            throw asio::system_error(error);
        // make a string with the message
        std::string message(recv_buf.data(), len);
        // push the message in the queue
        this->_messageQueue.push(message);
        // print the message
        std::cout << "received message: " << message << std::endl;
    }

The function to get the new message from the server

Client.cpp : Client::runClient
------------------------------------

.. code:: cpp

    
    void Client::runClient(void) {
        // the string for the message
        std::string message;
        // the thread for the read
        std::thread readThread([&]() {
            // while the message is not QUIT
            while (true) {
                // get the new message
                this->getNewMessage();
            }
        });

        // while the message is not QUIT
        while (true) {
            // get the input
            std::string buffer = {0};
            std::getline(std::cin, buffer);
            // send the message
            this->sendMessage(buffer);
        }
        // join the thread
        readThread.join();
    }

The function to run the client

main.cpp : Include
------------------------------------

.. code:: cpp

    #include "include/Client.hpp"
    #include <iostream>

The include of the main, the client and the iostream

main.cpp :: main
------------------------------------

.. code:: cpp

    int main(int const argc, char const * const * const argv)
    {
        // if the number of arguments is not 3
        if (argc != 3) {
            // print the usage of the program
            std::cerr << "Usage: " << argv[0] << " <ip> <port>" << std::endl;
            // return 84
            return 84;
        }
        // get the ip and the port
        std::string const ip = argv[1];
        std::size_t const port = std::stoi(argv[2]);
        // create the io_context
        asio::io_context io_context;
        // create the client
        Client Client(io_context, ip, port);
        // run the client
        Client.runClient();
        return 0;
    }

The main function of the program