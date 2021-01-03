#include "Bullet.h"

Bullet::Bullet(sf::Vector2f _position, sf::Vector2f _direction)
	: m_lifetime(600)
{
	m_shape.setRadius(3.0f);
	m_shape.setFillColor(sf::Color::White);
	m_position = _position;
	m_shape.setPosition(m_position);
	m_direction = _direction;
	normalize(m_direction);
	m_velocity = 4.0f;
	m_direction *= m_velocity;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	m_lifetime--;
	m_shape.move(m_direction);
	setPosition(m_shape.getPosition());
}

void Bullet::Draw(sf::RenderWindow& _window)
{
	_window.draw(m_shape);
}

int Bullet::getLifetime()
{
	return m_lifetime;
}

sf::FloatRect Bullet::getGlobalBounds()
{
	return m_shape.getGlobalBounds();
}
