#pragma once
#include "SFML/Graphics.hpp"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow& _window) = 0;

	void setDirection(float _x, float _y);
	void setDirection(sf::Vector2f _vector);
	void setPosition(float _x, float _y);
	void setPosition(sf::Vector2f _vector);
	sf::Vector2f getDirection();
	sf::Vector2f getPosition();
	void normalize(sf::Vector2f& _vector);
	sf::FloatRect getGlobalBounds();

	bool m_isActive;

protected:
	sf::Vector2f m_position, m_direction;
	float m_velocity;
};

