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

int main()
{
	InitTapiDoor();
	sfg::SFGUI sfgui;

	sf::RenderWindow window(sf::VideoMode(800,600), "tapidoori");
	window.setActive(false);

	auto label = sfg::Label::Create("Hello world!");

	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	box->Pack(label);
	auto sfgwindow = sfg::Window::Create();
	sfgwindow->SetTitle("Hello world!");
	sfgwindow->Add(box);

	sfg::Desktop desktop;
	desktop.Add(sfgwindow);
	
	window.resetGLStates();

	sf::Thread thread(&render, &window);
	thread.launch();
	sf::Clock clock;

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			desktop.HandleEvent(event);
			switch(event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
				default: break;
			}
		}

		desktop.Update( clock.restart().asSeconds());

		window.clear();
		sfgui.Display(window);
		window.display();
	}
	thread.wait();

	sf::Packet p;
	MessagePacket mp; mp.msg="Hello world";
	p << mp;

	TestPacket tp;
	tp.a=1; tp.b=2; tp.c="Hello TestPacket";
	p << tp;

	PacketParser::Parse(p);
	return 0;
}
