.. _server-doc:

Server Documentation
====================

Table of Contents
-----------------

1. `Introduction`_
2. `Class Overview`_
3. `Constructor and Destructor`_
4. `Server Operations`_
5. `Command Handling`_
6. `Utility Methods`_
7. `Notification Methods`_
8. `Exception Handling`_
9. `Usage`_
10. `Example`_

Introduction
------------

The `Server` class is a part of the r-type-mirror project and serves as the server-side implementation. It uses the Boost.Asio library for asynchronous networking operations.

Class Overview
--------------

The class provides functionalities for handling client connections, command processing, game initiation, and message broadcasting.

Constructor and Destructor
--------------------------

.. code-block:: cpp

   Server(const std::string& ip, int const port);
   ~Server(void);

- `ip`: IP address where the server is bound.
- `port`: Port number where the server is running.

The constructor initializes the server socket and binds it to the specified IP address and port. The destructor closes the server.

Server Operations
-----------------

.. code-block:: cpp

   void closeServer(void);
   void startServer(void);

- `closeServer`: Closes the server socket and releases resources.
- `startServer`: Initiates the server and begins waiting for incoming clients.

Command Handling
----------------

The `Server` class handles various client commands using a map of command strings to corresponding member functions.

.. code-block:: cpp

   static void handleConnect(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
   static void handleDisconnect(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
   static void handleReady(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);

Utility Methods
---------------

.. code-block:: cpp

   void connectClient(const udp::endpoint& client_endpoint, const std::array<char, 2048>& buffer, size_t bytes_received);
   void broadcastMessage(const std::string& message, size_t messageSize, const udp::endpoint& sender);
   void acceptClients();

- `connectClient`: Processes the received command and dispatches it to the appropriate handler.
- `broadcastMessage`: Sends a message to all connected clients except the sender.
- `acceptClients`: Waits for incoming clients, receives their commands, and takes appropriate actions.

Notification Methods
--------------------

.. code-block:: cpp

   void notifyGameReady();

- `notifyGameReady`: Notifies all connected clients when the game is ready to start.

Exception Handling
------------------

The class handles exceptions gracefully, printing error messages to the standard error stream.

Usage
-----

To use the `Server` class, create an instance with the desired IP address and port, then call `startServer` to begin accepting clients.

Example
-------

.. code-block:: cpp

   Server myServer("127.0.0.1", 8080);
   myServer.startServer();
