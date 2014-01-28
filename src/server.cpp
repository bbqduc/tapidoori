#include <SFML/Network.hpp>
#include <iostream>

int main()
{
	sf::UdpSocket sock;
	sock.bind(53000);
	std::cout << "Server is listening" << std::endl;

	char recvbuf[1024]={0};
	size_t received;
	sf::IpAddress ip;
	unsigned short port;

	sf::Socket::Status receiveStatus = sock.receive(recvbuf, 1024, received, ip, port);
	if(receiveStatus == sf::Socket::Done)
	{
		std::cout << recvbuf << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}

	return 0;
}
