#include "UFO.h"

UFO::UFO()
{
	setPosition(sf::Vector2f(static_cast<float>(rand() % config::WIDTH), static_cast<float>(rand() % config::HEIGHT)));
	m_tileset.loadFromFile("../Assets/tileset_asteroids.png");
	m_sprite.setTexture(m_tileset);
	m_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(16.0f, 16.0f);
	m_sprite.setScale(sf::Vector2f(1.5, 1.5));
	m_isActive = true;
	m_angle = static_cast<float>(rand() % 360);
	m_velocity = 1.0f;
}

UFO::~UFO()
{
}

void UFO::Update()
{
	if (m_isActive)
	{
		m_angle += static_cast<float>(rand() / RAND_MAX) * 0.1f;
		m_direction.x = sin(m_angle * static_cast<float>(M_PI) / 180.0f) * m_velocity;
		m_direction.y = -cos(m_angle * static_cast<float>(M_PI) / 180.0f) * m_velocity;

		m_sprite.move(m_direction);
		m_position = m_sprite.getPosition();
		if (m_position.x < 0)
			m_sprite.setPosition(static_cast<float>(config::WIDTH), m_position.y);
		if (m_position.y < 0)
			m_sprite.setPosition(m_position.x, static_cast<float>(config::HEIGHT));
		if (m_position.x > config::WIDTH)
			m_sprite.setPosition(0, m_position.y);
		if (m_position.y > config::HEIGHT)
			m_sprite.setPosition(m_position.x, 0);
	}
}

void UFO::Draw(sf::RenderWindow& _window)
{
	if (m_isActive)
	{
	_window.draw(m_sprite);
	}
}

Bullet* UFO::shoot(GameObject& _target)
{
	return new Bullet(m_position, vectorToTarget(_target));
}

sf::Vector2f UFO::vectorToTarget(GameObject& _target)
{
	return sf::Vector2f(_target.getPosition().x - m_position.x, _target.getPosition().y - m_position.y);
}

sf::FloatRect UFO::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}
