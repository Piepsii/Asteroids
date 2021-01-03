#include "Asteroid.h"

Asteroid::Asteroid()
{
	setPosition(sf::Vector2f(static_cast<float>(rand() % config::WIDTH), 0.0f));
	m_tileset.loadFromFile("../Assets/tileset_asteroids.png");
	m_sprite.setTexture(m_tileset);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(16.0f, 16.0f);
	m_sprite.setScale(sf::Vector2f(1.5, 1.5));
	m_isActive = true;
	m_direction = sf::Vector2f(0.0f, 0.0f);
	m_angle = static_cast<float>(rand() % 360);
	m_velocity = 0.7f;
	m_state = 0;
}

Asteroid::Asteroid(sf::Vector2f _position, float _angle, int _state)
{
	setPosition(sf::Vector2f(static_cast<float>(rand() % config::WIDTH), 0.0f));
	m_tileset.loadFromFile("../Assets/tileset_asteroids.png");
	m_sprite.setTexture(m_tileset);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_sprite.setPosition(_position);
	m_sprite.setOrigin(16.0f, 16.0f);
	m_sprite.setScale(sf::Vector2f(1.5, 1.5));
	m_isActive = true;
	m_direction = sf::Vector2f(0.0f, 0.0f);
	m_angle = _angle;
	m_velocity = 1.0f;
	m_state = _state;
}

Asteroid::~Asteroid()
{
	delete this;
}

void Asteroid::Update()
{
	if (m_isActive)
	{
		if (m_state == 1)
			m_sprite.setScale(1.2f, 1.2f);
		if (m_state == 2)
			m_sprite.setScale(0.8f, 0.8f);
		m_angle += 0.1f;
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

void Asteroid::Draw(sf::RenderWindow& _window)
{
	if (m_isActive)
	{
		_window.draw(m_sprite);
	}
}

Asteroid* Asteroid::split()
{
	switch (m_state) {
	case 0:
		m_state++;
		m_angle += 10.0f;
		return new Asteroid(m_position, m_angle - 10.0f, m_state);

	case 1:
		m_state++;
		m_angle += 10.0f;
		return new Asteroid(m_position, m_angle - 10.0f, m_state);

	case 2:
		m_state++;
		return new Asteroid(m_position, 0.0f, 3);

	default:
		return nullptr;
	}
}

int Asteroid::getState()
{
	return m_state;
}

sf::FloatRect Asteroid::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
}
