#pragma once

#include <string>
#include <SFML/Network.hpp>

enum PacketType
{
	Message,
	Test
};

class ParsablePacket
{
	virtual void HandlePacket(void *data)=0;
};

struct MessagePacket : public ParsablePacket
{
	std::string msg;

	void HandlePacket(void *data);
	friend sf::Packet& operator>>(sf::Packet &lhs, MessagePacket &rhs);
	friend sf::Packet& operator<<(sf::Packet &lhs, const MessagePacket &rhs);
};

struct TestPacket : public ParsablePacket
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
