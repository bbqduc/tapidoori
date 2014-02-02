#pragma once

#include <string>
#include <SFML/Network.hpp>

enum PacketType
{
	Message,
	Test
};

struct MessagePacket
{
	std::string msg;

	void HandlePacket(void *data);
	friend sf::Packet& operator>>(sf::Packet &lhs, MessagePacket &rhs);
	friend sf::Packet& operator<<(sf::Packet &lhs, const MessagePacket &rhs);
};

struct TestPacket
{
	int a, b;
	std::string c;

	void HandlePacket(void *data);
	friend sf::Packet& operator>>(sf::Packet &lhs, TestPacket &rhs);
	friend sf::Packet& operator<<(sf::Packet &lhs, const TestPacket &rhs);
};

struct PacketParser
{
	static void Parse(sf::Packet &p);
};
