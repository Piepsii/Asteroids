#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Ship.h"

Ship::Ship()
	: m_maxVelocity(1.5f), m_minVelocity(0.3f), m_angle(0.0f), m_acceleration(0.1f), m_teleportCooldown(0)
{
	m_velocity = 0.0f;
	m_shape.setPointCount(4);
	m_shape.setPoint(0, sf::Vector2f(15.5f, 3.0f));
	m_shape.setPoint(1, sf::Vector2f(28.0f, 27.0f));
	m_shape.setPoint(2, sf::Vector2f(15.5f, 21.0f));
	m_shape.setPoint(3, sf::Vector2f(3.0f, 27.0f));
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineThickness(2);
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setOrigin(16.0f, 16.0f);
	m_shape.setPosition(sf::Vector2f(320, 240));
}

Ship::~Ship()
{
}

void Ship::Update()
{
	updateTransform();
	if(m_teleportCooldown > 0)
		m_teleportCooldown--;
}

void Ship::Draw(sf::RenderWindow &_window)
{
	_window.draw(m_shape);
}

void Ship::updateTransform()
{
	m_direction.x = sin(m_angle * static_cast<float>(M_PI) / 180.0f) * m_velocity;
	m_direction.y = -cos(m_angle * static_cast<float>(M_PI) / 180.0f)  * m_velocity;
	m_shape.move(m_direction);
	setPosition(m_shape.getPosition());
	m_shape.setRotation(m_angle);
	accelerate(-0.02f);
	if (m_position.x < 0)
		m_shape.setPosition(static_cast<float>(config::WIDTH), m_position.y);
	if (m_position.y < 0)
		m_shape.setPosition(m_position.x, static_cast<float>(config::HEIGHT));
	if (m_position.x > config::WIDTH)
		m_shape.setPosition(0, m_position.y);
	if (m_position.y > config::HEIGHT)
		m_shape.setPosition(m_position.x, 0);
}

void Ship::rotate(float _speed)
{
	m_angle += _speed;
	m_angle = fmod(m_angle, 360.0f);
}

void Ship::accelerate(float _velocity)
{
	m_velocity += _velocity * m_acceleration;
	if (m_velocity > m_maxVelocity)
		m_velocity = m_maxVelocity;
	if (m_velocity < m_minVelocity)
		m_velocity = m_minVelocity;
}

void Ship::teleport()
{
	srand(static_cast<unsigned int>(time(NULL)));
	if (m_teleportCooldown == 0) 
	{
		m_teleportCooldown = 300;
		m_shape.setPosition(sf::Vector2f(static_cast<float>(rand() % config::WIDTH), static_cast<float>(rand() % config::HEIGHT)));
	}
}

Bullet* Ship::shoot()
{
	return new Bullet(m_position, m_direction);
}

sf::FloatRect Ship::getGlobalBounds()
{
	return m_shape.getGlobalBounds();
}

sf::ConvexShape Ship::getShape()
{
	return m_shape;
}