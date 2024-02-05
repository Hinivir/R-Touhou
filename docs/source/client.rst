.. _client-doc:

Client documentation
====================

Here is the documentation of the client.

Table of Contents
-----------------

1. `How to run a client`_
2. `Explaining the code`_

How to run a client
-------------------

Before trying to connect a client, you must run a server. See the `Client documentation`_.

The binary of the client can be found in ``/app/Client/``.
You can launch a client by running this command:

.. code-block:: bash

    ./L-Type-Client [ip] [port]

where ``ip`` is the ip where the server is running, and ``port`` is the port where the server runs.
You can connect as many clients as you want.

Explaining the code
-------------------

All prototypes of the Client functions are regrouped in a ``Client`` class. See ``/app/Client/include/Client.hpp``.

Here are basic explanations of how the client works.

Client connection
~~~~~~~~~~~~~~~~~

We use the ``asio`` library for our clients and server. It allows us to use the udp protocol instead of tcp, which allows us to send more packages but they are more sensitive.

.. code-block:: cpp

    Client(
         asio::io_context& ioContext,
         const std::string& serverAddress,
         const std::string& serverPort
    );

- ``ioContext`` provides the Core I/O functionality for asynchronous I/O objects
- ``serverAddress`` is the ip address given as argument when executing the program
- ``serverPort`` is the server port given as argument when executing the program

When exiting the program, the client will disconnect with the destructor ``~Client()``.

Send and receive messages
~~~~~~~~~~~~~~~~~~~~~~~~

The client is able to receive and send messages asynchronously. To do that, a thread will be running to handle new messages, while the main program sends them.

.. code-block:: cpp

    void sendMessage(const std::string& message);
    void getNewMessage();
    void handleMessageInGame(const std::string& message);
    void ParseMessage(const std::string message);

- ``sendMessage``: takes the message as an argument and send it to the server
- ``getNewMessage``: receive new messages from server
- ``handleMessageInGame``: takes the received message if we are in a game, and will handle inputs
- ``ParseMessage``: takes the received message, will setup the game, create place for new users

In-game functions
~~~~~~~~~~~~~~~~~

.. code-block:: cpp

    void handleGame();
    bool checkCollision(int newPosX, int newPosY, int otherPosX, int otherPosY);
    void upFunction(bool isReceived);
    void downFunction(bool isReceived);
    void leftFunction(bool isReceived);
    void rightFunction(bool isReceived);
    void actionFunction(bool isReceived);
    void quitFunction(bool isReceived)
