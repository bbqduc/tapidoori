#include <SFML/Network.hpp>
#include <iostream>

int main()
{
	sf::UdpSocket sock;

	std::string str("Hello, I'm Client!");

	sf::Socket::Status sendStatus = sock.send(&str[0], str.length(), sf::IpAddress("127.0.0.1"), 53000);
	if(sendStatus == sf::Socket::Done)
	{
		std::cout << "Jipii!" << std::endl;
	}
	else
	{
		std::cout << "Oh noes" << std::endl;
	}

	return 0;
}
