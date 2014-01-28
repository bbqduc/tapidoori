#include "packets.h"
#include <SFML/System.hpp>
#include <iostream>

sf::Packet& operator>>(sf::Packet &lhs, MessagePacket &rhs)
{
	return lhs >> rhs.msg;
}

sf::Packet& operator<<(sf::Packet &lhs, const MessagePacket &rhs)
{
	return lhs << (sf::Uint8)Message << rhs.msg;
}

sf::Packet& operator>>(sf::Packet &p, TestPacket &t)
{
	return p >> t.a >> t.b >> t.c;
}

sf::Packet& operator<<(sf::Packet &p, const TestPacket &t)
{
	return p << (sf::Uint8)Test << t.a << t.b << t.c;
}

void MessagePacket::HandlePacket(void *data)
{
	std::cout << "MessagePacket::HandlePacket" << std::endl;
	std::cout << "MessagePacket.msg: " << msg << std::endl;
}

void TestPacket::HandlePacket(void *data)
{
	std::cout << "TestPacket::HandlePacket" << std::endl;
	std::cout << "TestPacket.a: " << a << std::endl;
	std::cout << "TestPacket.b: " << b << std::endl;
	std::cout << "TestPacket.c: " << c << std::endl;
}

template <typename T>
static inline void HandlePacket(sf::Packet &p)
{
	T packet;
	p >> packet;
	packet.HandlePacket(nullptr);
}

void PacketParser::Parse(sf::Packet &p)
{
	while(!p.endOfPacket())
	{
		sf::Uint8 type;
		p >> type;

		switch(type)
		{
			case Message: HandlePacket<MessagePacket>(p); break;
			case Test: HandlePacket<TestPacket>(p); break;
		}
	}
}
