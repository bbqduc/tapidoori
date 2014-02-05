#include <SFGUI/SFGUI.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "packets.h"

#ifdef __linux__
	#include <X11/Xlib.h>
#endif

static void InitTapiDoor()
{
	#ifdef __linux__
		XInitThreads();
	#endif
}

void render(sf::RenderWindow *window)
{
	while(window->isOpen())
	{
		window->display();
	}
}

struct ServerConnection
{
	int m_SocketStatus; 
	sf::IpAddress m_ServerAddress;
	unsigned short m_ServerPort;
	sf::TcpSocket *m_TcpSocket;
	sf::UdpSocket *m_UdpSocket;


	ServerConnection()
		:
			m_SocketStatus(-1),
			m_ServerAddress("0.0.0.0"),
			m_ServerPort(0),
			m_TcpSocket(new sf::TcpSocket()),
			m_UdpSocket(new sf::UdpSocket())
	{
	}

	void M_Connect(sf::IpAddress addr, unsigned short port) // todo : disconnect before connecting to another
	{
		m_ServerAddress = addr;
		m_ServerPort = port;
		m_SocketStatus = m_TcpSocket->connect(addr, port);
	}
	int M_GetStatus() { return m_SocketStatus; }

	~ServerConnection()
	{
		delete m_TcpSocket;
		delete m_UdpSocket;
	}
};


class GameClient
{
	public:

	GameClient()
		:
			m_RenderWindow(sf::VideoMode(800, 600), "Tapidoori"),
			m_Desktop(),
			m_SfgWindow(sfg::Window::Create()),
			m_SystemMessageBox(sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f))
	{
		m_SfgWindow->SetTitle("Messages");
		m_SfgWindow->Add(m_SystemMessageBox);
//		m_SfgWindow->SetPosition(sf::Vector2f(10.0f, 100.0f));
		m_Desktop.Add(m_SfgWindow);
		m_RenderWindow.resetGLStates();
	}

	bool M_ConnectToServer(sf::IpAddress addr, unsigned short port)
	{
		m_Connection.M_Connect(addr, port);

		bool connectionsuccesful = m_Connection.M_GetStatus() == sf::Socket::Done;
		if(connectionsuccesful) M_DisplaySystemMessage("Connected to server!");
		else M_DisplaySystemMessage("Connection to server failed.");

		return connectionsuccesful;
	}

	void M_Run()
	{
		sf::Clock clock;
		while(m_RenderWindow.isOpen())
		{
			sf::Event event;
			while(m_RenderWindow.pollEvent(event))
			{
				switch(event.type)
				{
					case sf::Event::Closed:
						{
							m_RenderWindow.close();
							break;
						}
					default: break;
				}
		}

		m_Desktop.Update( clock.restart().asSeconds());

		m_RenderWindow.clear();
		sfgui.Display(m_RenderWindow);
		m_RenderWindow.display();
		}
	}

	void M_DisplaySystemMessage(const std::string& msg)
	{
		m_SystemMessageBox->Pack(sfg::Label::Create(msg));
	}

	private:
	ServerConnection m_Connection;
	sfg::SFGUI sfgui; // todo : correct place?

	sf::RenderWindow m_RenderWindow;
	sfg::Desktop m_Desktop;
	std::shared_ptr<sfg::Window> m_SfgWindow;
	std::shared_ptr<sfg::Box> m_SystemMessageBox;
};


int main()
{
	InitTapiDoor();

	GameClient client;

	client.M_ConnectToServer("127.0.0.1", 53000);

	client.M_Run();

	return 0;
}
