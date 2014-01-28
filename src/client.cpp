#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

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

	sf::RenderWindow window(sf::VideoMode(800,600), "tapidoori");
	window.setActive(false);

	sf::Thread thread(&render, &window);
	thread.launch();

	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
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
	}
	thread.wait();
	return 0;
}
