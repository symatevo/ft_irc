## Summary

In this project, you are required to implement an IRC server that can handle multiple connections from IRC clients. The server should follow the IRC protocol and provide functionalities such as connecting to the server, joining channels, sending and receiving messages, and handling commands.

## Skills to Learn

- Network Programming
- IRC Protocol
- Socket Programming
- Multi-threading

## The "FT_IRC" Project

### Description

The "FT_IRC" project involves creating an IRC server in C++ that is compatible with official IRC clients. You'll need to understand the IRC protocol, handle connections from clients using sockets, and process incoming messages. The server should support multiple simultaneous connections from various IRC clients and provide real-time chat functionalities.

IRC is a protocol used for text-based communication in chat rooms and channels. Clients use commands and messages to interact with the server and other users.

## Project Constraints

- Implement an IRC server in C++ that follows the IRC protocol.
- Handle multiple connections concurrently using multi-threading or other techniques.
- Support basic IRC commands like connecting to the server, joining channels, sending messages, and handling user commands.
- Ensure that the server is fully compatible with official IRC clients, allowing users to connect and interact seamlessly.

## Example Functionalities

- Accept and manage connections from IRC clients.
- Process IRC commands like JOIN, NICK, PRIVMSG, QUIT, etc.
- Handle JOIN and PART requests to allow users to join and leave channels.
- Manage multiple channels and handle channel messages.
- Provide real-time chat functionality among users in the same channel.

