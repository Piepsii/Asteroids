#include "SFML/Graphics.hpp"

#include "Game.h"


int main(int argc, char** argv)
{
	sf::VideoMode video_mode;
	const char* title = "";
	InputManager inputManager;

	Game* game = new Game(video_mode.width, video_mode.height, title, inputManager);

	sf::RenderWindow window(video_mode, title);
	sf::Clock clock;
	sf::Time delta;
	float frameTime = 1.0f / 60.0f;
	bool running = true;

	while (running)
	{
		sf::Event event;
		delta = clock.restart();
		inputManager.Update();
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				game->onKeyPressed(event.key.code); break;
			case sf::Event::KeyReleased:
				game->onKeyReleased(event.key.code); break;
			case sf::Event::EventType::Closed:
				running = false; break;

			}
		}

		window.clear(sf::Color::Black);
	
		if (game->Update(delta.asSeconds()))
			game->Draw(window);
		else
			running = false;
	
		window.display();
		sf::Time delay(sf::seconds(frameTime - delta.asSeconds()));
		sf::sleep(delay);
	}

	delete game;
	game = nullptr;
	return 0;
}