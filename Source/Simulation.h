#pragma once

#include <SFML/Graphics.hpp>

class Simulation
{
public:
	Simulation(unsigned int& _screenWidth, unsigned int& _screenHeigh, const char*& title);
	~Simulation();

	bool Update(float _deltaTime);
	void Draw(sf::RenderWindow window);
};

