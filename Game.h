#pragma once

#include <deque>
#include "AccelerateShipCommand.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "config.h"
#include "InputManager.h"
#include "RotateShipCommand.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Ship.h"
#include "TeleportShipCommand.h"
#include "UFO.h"

class Game
{
public:
	Game(unsigned int& screenWidth, unsigned int& screenHeight, const char*& title, InputManager& _inputManager);
	~Game();
	/// Return Value
	/// true = Continue to run program
	/// false = Quits program
	bool Update(float deltaTime);
	void Draw(sf::RenderWindow& _window);

	void onKeyPressed(sf::Keyboard::Key& _key);
	void onKeyReleased(sf::Keyboard::Key& _key);
	void handleInput();
	void updateCooldowns();
	void updateBullets();
	void updateAsteroids();
	void checkCollision();
	void increaseLevel();

private:
	enum class GameState {
		PLAYING,
		LOST,
		WON
	};
	sf::Font m_font;
	sf::Text m_scoreText, m_lostText, m_wonText;
	sf::SoundBuffer m_soundPopBuffer, m_soundTeleportBuffer, m_soundThrustBuffer;
	sf::Sound m_soundPop, m_soundShot, m_soundTeleport, m_soundThrust;
	GameState m_gameState;
	Ship m_ship;
	UFO m_ufo;
	std::vector<Bullet*> m_friendlyBullets, m_enemyBullets;
	std::vector<Asteroid*> m_asteroids;
	InputManager* m_inputManager;
	Command *buttonUp, *buttonDown, *buttonLeft, *buttonRight, *buttonQ;
	sf::ConvexShape* m_livesGUI;

	int m_shootingCooldown, m_UFOCooldown;
	int m_playerLives, m_levelCount, m_score, m_breakTime;
	bool m_isIntersecting, m_wasIntersecting;
};