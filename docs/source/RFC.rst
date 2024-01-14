.. _rtype-rfc:

RFC: For the R-Type Project
===================================================================

1. Integration with R-Type Project
----------------------------------

The FTP protocol, as outlined in this document, serves as a foundational component for the seamless integration of file transfer capabilities within the context of the "R-Type" project developed at Epitech.

1.1. Use Case
~~~~~~~~~~~~~

In the realm of the "R-Type" project, efficient asset management, including the exchange of game assets and configurations between client and server components, is paramount. FTP provides a standardized and reliable method for uploading, downloading, and managing these essential files.

1.2. Extending FTP for Gaming Assets
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

While FTP, in its standard form, caters to general file transfer needs, the "R-Type" project may introduce specific extensions to address the unique requirements of game asset management. These extensions could include specialized commands or metadata tailored to the needs of the gaming environment.

1.3. Security Considerations for Gaming Environments
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Given the sensitive nature of gaming assets and configurations, security considerations within the "R-Type" project should align with industry best practices. Implementers are encouraged to explore secure alternatives or additional encryption layers to protect intellectual property and sensitive game-related data.

1.4. Collaboration with Epitech Guidelines
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section of the RFC document aims to facilitate collaboration between the FTP protocol and the specific requirements of the "R-Type" project as envisioned by Epitech. Implementers and developers working on the project should refer to this document alongside any supplementary guidelines provided by Epitech to ensure a cohesive and effective integration of file transfer capabilities within the gaming ecosystem.

2. Protocol Overview
--------------------

2.1. Commands
~~~~~~~~~~~~~

This is the command that the client can use to communicate with the server:

- `connect`: Connect the client to the server.
- `ready`: The client is ready to play a game.
- `disconnect`: Disconnect the client from the server.
- `help`: Display a list of available commands.
- `msg`: Send a message to the server.

2.2. Responses
~~~~~~~~~~~~~

This is the response that the server can send to the client:

- `101`: You are connected!
- `102`: Error sending confirmation message to client!
- `103`: You are disconnected!
- `104`: You are ready!
- `105`: Server is full!

3. Data Send
------------

Send data using a structure (sending in bytes) and serialize it.
When receiving data, deserialize it and use the structure to get the data.

1. References
-------------

- `RFC 959 - File Transfer Protocol (FTP) <https://www.ietf.org/rfc/rfc959.txt>`_ for the official FTP specification.

5. Author's Address
-------------------

For inquiries or further information, please contact the protocol author:

**Drindael**

**cyprien.nguyen-van-vien@epitech.eu**

**Epitech**
