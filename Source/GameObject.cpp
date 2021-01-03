#include "GameObject.h"

GameObject::GameObject()
	: m_isActive(true), m_velocity(0.0f)
{
}

GameObject::~GameObject()
{
}

void GameObject::setDirection(float _x, float _y)
{
	m_direction.x = _x;
	m_direction.y = _y;
}

void GameObject::setDirection(sf::Vector2f _vector)
{
	m_direction = _vector;
}

void GameObject::setPosition(float _x, float _y)
{
	m_position.x = _x;
	m_position.y = _y;
}

void GameObject::setPosition(sf::Vector2f _vector)
{
	m_position = _vector;
}

sf::Vector2f GameObject::getDirection()
{
	return m_direction;
}

sf::Vector2f GameObject::getPosition()
{
	return m_position;
}

void GameObject::normalize(sf::Vector2f& _vector)
{
	float magnitude = sqrt(_vector.x * _vector.x + _vector.y * _vector.y);
	_vector.x /= magnitude;
	_vector.y /= magnitude;
}

sf::FloatRect GameObject::getGlobalBounds()
{
	return sf::FloatRect(m_position, sf::Vector2f(50, 50));
}
