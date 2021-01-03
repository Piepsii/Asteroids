#pragma once
#include "SFML/Graphics.hpp"
#include "config.h"
#include "GameObject.h"
#include "Bullet.h"

class Ship 
: public GameObject{
public:
	Ship();
	~Ship();
	void Update();
	void Draw(sf::RenderWindow& _window);

	void updateTransform();
	void rotate(float _speed);
	void accelerate(float _velocity);
	void teleport();
	Bullet* shoot();
	sf::FloatRect getGlobalBounds();
	sf::ConvexShape getShape();

private:
	sf::ConvexShape m_shape;
	float m_angle;
	const float m_maxVelocity, m_minVelocity, m_acceleration;
	int m_teleportCooldown;
	
};