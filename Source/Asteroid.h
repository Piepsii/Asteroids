#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "GameObject.h"
#include "config.h"

class Asteroid :
    public GameObject
{
public:
    Asteroid();
    Asteroid(sf::Vector2f _position, float _angle, int _state);
    ~Asteroid();
    void Update();
    void Draw(sf::RenderWindow& _window);

    Asteroid* split();
    int getState();
    sf::FloatRect getGlobalBounds();

private:
    sf::Sprite m_sprite;
    sf::Texture m_tileset;
    float m_angle;
    int m_state;
};