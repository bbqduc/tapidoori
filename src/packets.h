#pragma once

#include <string>
#include <SFML/Network.hpp>

enum PacketType
{
    Connect, // Packet coming to server from client connect
    Disconnect, // Packet coming to server from client disconnect
	ServerChatMessage, // Packet coming to server from client chatmessage
	ClientChatMessage, // Packet coming to client about chatmessage
    SystemMessage, // Packet coming to client about general system message
};

enum SystemMessageType
{
    NewConnection,
    PlayerDisconnect
};

struct ConnectPacket
{
    std::string playername;

	friend sf::Packet& operator>>(sf::Packet &lhs, ConnectPacket &rhs);
	friend sf::Packet& operator<<(sf::Packet &lhs, const ConnectPacket &rhs);
};

struct ServerChatMessagePacket
{
	std::string msg;

	void HandlePacket(void *data);
	friend sf::Packet& operator>>(sf::Packet &lhs, ServerChatMessagePacket &rhs);
	friend sf::Packet& operator<<(sf::Packet &lhs, const ServerChatMessagePacket &rhs);
};

struct ClientChatMessagePacket
{
    unsigned clientId;
    std::string msg;
};

struct PacketParser
{
	static void Parse(sf::Packet &p);
};
