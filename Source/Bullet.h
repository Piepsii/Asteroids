#pragma once
#include "GameObject.h"
#include "config.h"

class Bullet :
    public GameObject
{
public:
    Bullet(sf::Vector2f _position, sf::Vector2f _direction);
    ~Bullet();
    void Update();
    void Draw(sf::RenderWindow& _window);

    int getLifetime();
    sf::FloatRect getGlobalBounds();

private:
    sf::CircleShape m_shape;
    int m_lifetime;
};

