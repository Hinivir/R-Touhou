# RFC: Integration of File Transfer Protocol (FTP) for the "R-Type" Project

### 1 Integration with R-Type Project

The FTP protocol, as outlined in this document, serves as a foundational component for the seamless integration of file transfer capabilities within the context of the "R-Type" project developed at Epitech.

#### 1.1 Use Case

In the realm of the "R-Type" project, efficient asset management, including the exchange of game assets and configurations between client and server components, is paramount. FTP provides a standardized and reliable method for uploading, downloading, and managing these essential files.

#### 1.2 Extending FTP for Gaming Assets

While FTP, in its standard form, caters to general file transfer needs, the "R-Type" project may introduce specific extensions to address the unique requirements of game asset management. These extensions could include specialized commands or metadata tailored to the needs of the gaming environment.

#### 1.3 Security Considerations for Gaming Environments

Given the sensitive nature of gaming assets and configurations, security considerations within the "R-Type" project should align with industry best practices. Implementers are encouraged to explore secure alternatives or additional encryption layers to protect intellectual property and sensitive game-related data.

#### 1.4 Collaboration with Epitech Guidelines

This section of the RFC document aims to facilitate collaboration between the FTP protocol and the specific requirements of the "R-Type" project as envisioned by Epitech. Implementers and developers working on the project should refer to this document alongside any supplementary guidelines provided by Epitech to ensure a cohesive and effective integration of file transfer capabilities within the gaming ecosystem.


## 2. Protocol Overview

### 2.1 Commands

FTP operations are initiated by a series of commands issued by the client to the server. These commands encompass a broad range of functionalities, including user authentication, directory listing, file retrieval, and storage. Key FTP commands include:

- `USER`: Initiates the authentication process by providing a username.
- `PASS`: Completes the authentication by supplying a password.
- `LIST`: Retrieves a detailed listing of files in the current directory.
- `RETR`: Initiates the retrieval of a specified file from the server.
- `STOR`: Facilitates the storage of a file on the server.
- `DELE`: Deletes a file on the server.
- `MKD`: Creates a new directory on the server.
- `RMD`: Removes an existing directory on the server.

### 2.2 Responses

FTP server responses consist of a three-digit numeric code followed by a human-readable message. These responses convey the success or failure of the executed command. Examples of FTP response codes include:

- `200`: Command okay.
- `500`: Syntax error, command not understood.
- `331`: User name okay, need password.
- `530`: Not logged in.
- `226`: Closing data connection, request successful.

---

## 3. Data Transfer

FTP employs separate channels for command and data transfer, enhancing efficiency and flexibility during file exchanges. Two primary modes govern data transfer:

### 3.1 Active Mode

In active mode, the client opens a random port for data transfer, and the server connects to this port. The client initiates active mode using the `PORT` command.

### 3.2 Passive Mode

Passive mode involves the server opening a random port, and the client connects to this port for data transfer. The client initiates passive mode using the `PASV` command.

---

## 4. Security Considerations

Security in FTP is a critical concern due to the lack of built-in encryption for data transfer and authentication credentials. It is highly recommended to implement secure alternatives such as FTPS (FTP Secure) or SFTP (SSH File Transfer Protocol) to safeguard sensitive data and credentials from potential eavesdropping and man-in-the-middle attacks.

---

## 5. Implementation Guidelines

Implementers are urged to adhere to the FTP specifications outlined in this document. While the protocol allows for extensions and additional features, compatibility with the FTP standard should be maintained to ensure seamless interoperability across diverse FTP clients and servers.

---

## 6. References

- [RFC 959 - File Transfer Protocol (FTP)](https://www.ietf.org/rfc/rfc959.txt) for the official FTP specification.

---

## 7. Author's Address

For inquiries or further information, please contact the protocol author:

**[Author Name]  
[Author Email]  
[Author Organization]  
[Author Address]**

---
