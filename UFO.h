#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "GameObject.h"
#include "config.h"
#include "Bullet.h"

class UFO :
    public GameObject
{
public:
    UFO();
    ~UFO();
    void Update();
    void Draw(sf::RenderWindow& _window);

    Bullet* shoot(GameObject& _target);
    sf::Vector2f vectorToTarget(GameObject& _target);
    sf::FloatRect getGlobalBounds();

private:
    sf::Sprite m_sprite;
    sf::Texture m_tileset;
    float m_angle;
};

