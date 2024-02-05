# RFC Server R-Touhou: Simple Communication Protocol

## Introduction

This document defines a simple communication protocol for client-server interaction using predefined status messages for R-Touhou.

## Table of Contents

[1. Status Messages](#titre1)<br />
[2. Usage](#titre2)<br />
[3. Data Structure](#titre3)<br />

---

## <a id="titre1"></a>1. Status Messages

The following status messages are defined for communication between the client and server:

- **CONNECTED**: Indicates a successful connection.
  *Message: "101: You are connected!\n"*

- **DISCONNECTED**: Indicates a disconnection.
  *Message: "103: You are disconnected!\n"*

- **ERROR**: Indicates an error in sending confirmation messages to the client.
  *Message: "102: Error sending confirmation message to client!\n"*

- **READY**: Indicates that the system is ready.
  *Message: "104: You are ready!\n"*

- **SERVER_FULL**: Indicates that the server is full.
  *Message: "105: Server is full!\n"*

- **NEW_CLIENT**: Indicates that a client is connected.
  *Message: "106: New client connected!\n"*

---

## <a id="titre2"></a>2. Usage

**Connection Establishment:**
The client initiates a connection request to the server.
Upon successful connection, the server responds with the **CONNECTED** message.

**Disconnection:**
The client initiates a disconnection request to the server.
Upon successful disconnection, the server responds with the **DISCONNECTED** message.

**Error Handling:**
If an error occurs during the communication process, the server sends the **ERROR** message to the client.

**Ready State:**
The server notifies the client when it is ready for further communication using the **READY** message.

**Server Capacity:**
If the server is at full capacity and cannot accept new connections, it sends the **SERVER_FULL** message to the client.

**Security Considerations:**
This simple protocol does not address security concerns and should be used in trusted environments only.

## <a id="titre3"></a>3. Data Structure

Data must be sent to the server in this format:

| Magic Number (32-bit unsigned integer) | Packet Type (8-bit unsigned integer) | Payload Size (16-bit unsigned integer) |
|---|---|---|
|  |  |  |

### Player Related Events:

- #### TranformData*
  Data represents the Transform component of an entity:
  | id | x | y | dx | dy |
  |---|---|---|---|---|
  |  | Float | Float | Float | Float |

- #### EndGameData*
  Data represents the End Game component of an entity:
  | id |
  |---|
  | 8-bit unsigned integer |

- #### ScoreData*
  Data represents the score:
  | id |
  |---|
  | 16-bit unsigned integer |

- #### InputData*
  Data represents the Controllable component of an entity:
  | id | inputId | state |
  |---|---|---|
  | 16-bit unsigned integer | 8-bit unsigned integer | 8-bit unsigned integer |

- #### ControllableData*
  Data represents the Controllable component of an entity:
  | id |
  |---|
  | 16-bit unsigned integer | Float | Float |

- #### StatePlayerData*
  Data represents the State of the player:
  | id | invincibility |
  |---|---|
  | 16-bit unsigned integer | 8-bit unsigned integer |

- #### CollisionData*
  Data represents Collision:
  | id | idCallback | rectLeft | rectTop | rectRight | rectHeight | layer |
  |---|---|---|---|---|---|---|
  | 16-bit unsigned integer | 8-bit unsigned integer | Float | Float | Float | Float | 8-bit unsigned integer |

- #### TextureData*
  Data represents Texture:
  | id | idTexture | idOrderTexture | rectLeft | rectTop | rectWidth | rectHeight | rectTextureLeft | rectTextureTop | rectTextureWidth | rectTextureHeight | renderLayer | isAnimated | animationSpeed |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|float|

- #### MoveData*
  Data represents the Move component of an entity:
  | id | x | y | dx | dy |
  |---|---|---|---|---|
  | 16-bit unsigned integer | Float | Float | Float | Float |

- #### ShootData*
  Data represents Shoot entity:
  | id | x | y | dx | dy |
  |---|---|---|---|---|
  | 16-bit unsigned integer | Float | Float | Float | Float |

- #### TextureResponse*
  Data if texture needs to be resent:
  | id | idTexture |
  |---|---|
  | 16-bit unsigned integer | 16-bit unsigned integer |

- #### CollisionResponse*
  Data if Collision needs to be resent:
  | id |
  |---|
  | 16-bit unsigned integer |

---
