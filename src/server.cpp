#include <SFML/Network.hpp>
#include <iostream>
#include "server.h"

void TapidooriServer::PollForNewClient()
{
    ClientInfo& c = clients.back();

    sf::Socket::Status status = m_TcpListener.accept(c.m_TcpSocket);
    if(status == sf::Socket::Done)
    {
        // new client connection !
        c.m_Name = "Herkko";
        ClientInfo newc;
        clients.push_back(newc); // make a new empty client
        unsigned newclientid = clients.size();
        HandleNewClient(newclientid);
    }
}

TapidooriServer::TapidooriServer(unsigned short port)
{
    m_TcpListener.listen(port);
    m_TcpListener.setBlocking(false);
    std::cout << "Listening to TCP on port " << port << std::endl; // todo : some proper logging thing
}

void TapidooriServer::HandleNewClient(unsigned id)
{
    std::cout << "Got new client with id " << id << '\n';
    // broadcast system message of join
    // respond to new client with stuff
}

void TapidooriServer::Run()
{
    PollForNewClient();
//    sf::Sleep(1);
}

int main()
{
    TapidooriServer server(53000);

	return 0;
}
