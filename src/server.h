#pragma once

#include "packets.h"
#include <iostream>
#include <vector>
#include <SFML/System.hpp>

struct ClientInfo
{
//    sf::IpAddress m_Address;
    sf::TcpSocket m_TcpSocket;
    std::string m_Name;

};

class TapidooriServer
{
    sf::TcpListener m_TcpListener;


    public:

    TapidooriServer(unsigned short);

	template<typename T>
	void HandlePacket(const T& packet);
    std::vector<ClientInfo> clients; // index in vector is clients id
    void PollForNewClient();
    void HandleNewClient(unsigned id);
    void Run();
};


template<>
void TapidooriServer::HandlePacket<ServerChatMessagePacket>(const ServerChatMessagePacket& packet)
{
	std::cout << "Received ServerChatMessagePacket with message : " << packet.msg << '\n';
}

