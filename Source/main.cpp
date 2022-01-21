#include "SFML/Graphics.hpp"

#include "Simulation.h"


int main(int argc, char** argv)
{
	sf::VideoMode video_mode(1080, 720);
	const char* title = "";

	Simulation* simulation = new Simulation(video_mode.width, video_mode.height, title);

	sf::RenderWindow window(video_mode, title);

	sf::Clock clock;
	sf::Time delta;
	float frameTime = 1.0f / 60.0f;
	bool running = true;

	while (running)
	{
		sf::Event event;
		delta = clock.restart();
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::EventType::Closed:
				running = false; break;

			}
		}

		window.clear(sf::Color::Black);
	
		window.display();
		sf::Time delay(sf::seconds(frameTime - delta.asSeconds()));
		sf::sleep(delay);
	}

	delete simulation;
	simulation = nullptr;
	return 0;
}