Server Documentation
====================================

.. toctree::
   :maxdepth: 2
   :caption: Contents:

Server.hpp
------------------------------------

.. code:: cpp

    #ifndef SERVER_HPP
        #define SERVER_HPP

        #include <iostream>
        #include <vector>
        #include <asio.hpp>

    using asio::ip::udp;

    class Server
    {
        private:
            bool isChatLocked = false; // A boolean to know if the chat is locked
            asio::io_service io_service; //
            udp::socket server_socket; // The socket for the server to be able to communicate
            std::vector<udp::endpoint> connectedClients; // The vector of the endpoint of the client
            std::vector<udp::endpoint> readyClients; // The vector of the endpoint of the client that are ready
            // The confirmation message and the error message
            std::string confirmationMessage = "101: You are connected!\n";
            std::string errorMessage = "102: Error sending confirmation message to client!\n";

        public:
            Server(const std::string& ip, int const port); // The constructor of the server with ip and port
            ~Server(void); // The destructor of the class
            void closeServer(void); // A function to close the Server
            void startServer(void); // A function to start the Server
            // The function to connect a client to the server, it take the endpoint of the client, a buffer and the size of the buffer
            void connectClient(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
            void acceptClients(void); // The function to accept client
            // The function to broadcast a message to the other client
            void broadcastMessage(const std::array<char, 2048>& buffer, size_t bytes_received, const udp::endpoint& sender);
            void notifyGameReady(void); // The function to notify the client that the game is ready
    };
    #endif

The hpp file for the server, with the class, and the function need for the server.

Server.cpp : Include
------------------------------------

.. code:: cpp

    #include <iostream>
    #include <thread>
    #include <asio.hpp>
    #include "../include/Server.hpp"

The include for the file, we need iostream to write to std::cout, asio for the communication with udp and the include of the server hpp file

Server.cpp : Server::Server
------------------------------------

.. code:: cpp

    Server::Server(const std::string& ip, int const port)
    : server_socket(io_service, udp::endpoint(udp::v4(), port)) // the init of the server socket
    {
        try {
            server_socket.close(); // close the socket
            server_socket.open(udp::v4()); // open the socket with udp v4
            server_socket.bind(udp::endpoint(udp::v4(), port)); // bind the endpoint to the port
        } catch (std::exception const &e) { // catch any error
            std::cerr << "ERROR" << e.what() << std::endl; // write the error to the error output
            throw; // throw the code
        }
    }

The server constructor

Server.cpp : Server::~Server
------------------------------------

.. code:: cpp

    Server::~Server(void)
    {
        closeServer(); // Call the function to close the server
    }

The server destructor

Server.cpp : Server::closeServer
------------------------------------

.. code:: cpp

    void Server::closeServer(void)
    {
        server_socket.close(); // close the socket of the server
    }


The close server method

Server.cpp : Server::startServer
------------------------------------

.. code:: cpp

    void Server::startServer(void)
    {
        std::cout << "Server started" << std::endl; // write to cout that the server start
        acceptClients(); // call the accept client method
    }

The start server method

Server.cpp : Server::notifyGameReady
------------------------------------

.. code:: cpp

    void Server::notifyGameReady(void)
    {
        // set string to send to client
        std::string gameReadyMessage = "Game is ready! Let the fun begin!\n";

        // send message to all clients
        for (const auto& client : connectedClients) {
            try {
                server_socket.send_to(asio::buffer(gameReadyMessage), client);
            } catch (std::exception const &e) { // catch any error
                // write the error to the error output
                std::cerr << "Error sending game ready message to client " << client.address() << ":" << client.port() << ": " << e.what() << std::endl;
            }
        }
    }

The notify game ready method

Server.cpp : Server::connectClient
------------------------------------

.. code:: cpp

    void Server::connectClient(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received)
    {
        // set the string to the message received
        std::string message(buffer.data(), bytes_received);
        // if the message is connect
        if (message == "connect\n") {
            // write to cout that the client is connected
            std::cout << "Client connected: " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
            // push back the client endpoint in the vector of the connected client
            connectedClients.push_back(client_endpoint);
            // send the confirmation message to the client
            std::string confirmationMessage = "101:You are connected!\n";
            try {
                // try to send the confirmation message to the client
                server_socket.send_to(asio::buffer(confirmationMessage), client_endpoint);
            } catch (std::exception const &e) { // catch any error
                // send the error message to the client
                server_socket.send_to(asio::buffer("102:Error Connection!\n"), client_endpoint);
                // write the error to the error output
                std::cerr << "Error sending confirmation message to client " << client_endpoint.address() << ":" << client_endpoint.port() << ": " << e.what() << std::endl;
            }
        }
        // if the message is ready
        else if (message == "ready\n") {
            // write to cout that the client is ready
            std::cout << "Client is ready: " << client_endpoint.address() << ":" << client_endpoint.port() << std::endl;
            // push back the client endpoint in the vector of the ready client
            readyClients.push_back(client_endpoint);
            // if the number of ready client is the same as the number of connected client
            if (readyClients.size() == connectedClients.size()) {
                // write to cout that all the client are ready
                std::cout << "All clients are ready. Starting the game!" << std::endl;
                // set the chat to locked
                isChatLocked = true;
                // call the notify game ready method
                notifyGameReady();
            }
        }
        // if any other message
        else
            // call the broadcast message method
            broadcastMessage(buffer, bytes_received, client_endpoint);
        // find if the client is in the vector of the connected client
        if (std::find(connectedClients.begin(), connectedClients.end(), client_endpoint) == connectedClients.end())
            // push back the client endpoint in the vector of the connected client
            connectedClients.push_back(client_endpoint);
    }

The connect client method

Server.cpp : Server::acceptClients
------------------------------------

.. code:: cpp

    void Server::broadcastMessage(const std::array<char, 2048>& buffer, size_t bytes_received, const asio::ip::udp::endpoint& sender)
    {
        std::string message(buffer.data(), bytes_received); // the message received from the client

        for (const auto& client : connectedClients) { // for each client in the vector of the connected client
            if (client != sender) { // if the client is not the sender
                if (message != "connect") { // if the message is not connect
                    try { // try to send the message to the client
                        server_socket.send_to(asio::buffer(message), client); // send the message to the client
                    } catch (std::exception const &e) { // catch any error
                        // write the error to the error output
                        std::cerr << "Error sending message to client " << client.address() << ":" << client.port() << ": " << e.what() << std::endl;
                    }
                }
            }
        }
    }

The broadcast message method

Server.cpp : Server::acceptClients
------------------------------------

.. code:: cpp

    void Server::acceptClients()
    {
        std::cout << "Waiting for clients..." << std::endl; // write to cout that the server is waiting for client
        try {
            while (1) { // while the server is running
                udp::endpoint client_endpoint; // the endpoint of the client
                std::array<char, 2048> buffer; // the buffer of the message
                // the size of the message received
                size_t bytes_received = server_socket.receive_from(asio::buffer(buffer), client_endpoint);
                if (bytes_received > 0) // if the message received is more than 0
                    connectClient(client_endpoint, buffer, bytes_received); // call the connect client method
                else
                    // write to cerr that the server received 0 bytes from the client
                    std::cerr << "Error: Received 0 bytes from client." << std::endl;
            }
        } catch (std::exception const &e) { // catch any error
            // write the error to the error output
            std::cerr << "Error in acceptClients: " << e.what() << std::endl;
        }
    }

The accept client method

main.cpp : include
------------------------------------

.. code:: cpp

    #include "include/Server.hpp"
    #include <sstream>

The include for the file, the include of the server hpp file and the sstream for the stringstream

main.cpp : handleError
------------------------------------

.. code:: cpp

    static bool handle_error(int const argc, char const * const * const argv) {
        if (argc != 3) { // if the number of argument is not 3
            // write to cerr that the number of argument is invalid
            std::cerr << "ERROR: invalid number of arguments" << std::endl;
            // return true because there is an error
            return true;
        }
        std::stringstream ss(argv[2]); // the stringstream of the argument 2
        std::size_t port; // the port
        ss >> port; // put the argument 2 in the port
        if (ss.fail()) { // if the stringstream fail
            // write to cerr that the port is invalid
            std::cerr << "ERROR: invalid port \"" << argv[2] << "\"" << std::endl;
            // return true because there is an error
            return true;
        }
        // return false because there is no error
        return false;
    }

The handle error method

main.cpp : get_port
------------------------------------

.. code:: cpp

    static std::size_t get_port(char const * const portString) {
        std::stringstream ss(portString); // the stringstream of the port string
        std::size_t port; // the port
        ss >> port; // put the port string in the port
        return port; // return the port
    }

The get port method

main.cpp : main
------------------------------------

.. code:: cpp

    int main(int const argc, char const * const * const argv) {
        if (handle_error(argc, argv)) // if there is an error
            return 84; // return 84
        std::size_t const port = get_port(argv[2]); // get the port
        std::string const ip = argv[1]; // get the ip
        Server server(ip, port); // create the server
        server.startServer(); // start the server
        return 0; // return 0
    }

The main method