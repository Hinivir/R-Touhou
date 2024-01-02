RFC XXXX: Simple Communication Protocol
Abstract
This document defines a simple communication protocol for client-server interaction using predefined status messages.

Status Messages
The following status messages are defined for communication between the client and server:

CONNECTED: Indicates a successful connection.

Message: "101: You are connected!\n"
DISCONNECTED: Indicates a disconnection.

Message: "103: You are disconnected!\n"
ERROR: Indicates an error in sending confirmation messages to the client.

Message: "102: Error sending confirmation message to client!\n"
READY: Indicates that the system is ready.

Message: "104: You are ready!\n"
SERVER_FULL: Indicates that the server is full.

Message: "105: Server is full!\n"
Usage
Connection Establishment
The client initiates a connection request to the server.
Upon successful connection, the server responds with the CONNECTED message.
Disconnection
The client initiates a disconnection request to the server.
Upon successful disconnection, the server responds with the DISCONNECTED message.
Error Handling
If an error occurs during the communication process, the server sends the ERROR message to the client.

Ready State
The server notifies the client when it is ready for further communication using the READY message.

Server Capacity
If the server is at full capacity and cannot accept new connections, it sends the SERVER_FULL message to the client.

Security Considerations
This simple protocol does not address security concerns and should be used in trusted environments only.

