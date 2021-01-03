#include "Game.h"

Game::Game(unsigned int &screenWidth, unsigned int &screenHeight, const char* &title, InputManager& _inputManager)
{
	srand(static_cast<unsigned int>(time(NULL)));
	screenWidth = static_cast<unsigned int>(config::WIDTH);
	screenHeight = static_cast<unsigned int>(config::HEIGHT);
	title = "The Game";
	if (!m_font.loadFromFile("../Assets/Roboto-Regular.ttf"))
		printf("font not found");
	m_scoreText.setFont(m_font);
	m_scoreText.setString("0");
	m_scoreText.setPosition(24, 40);
	m_scoreText.setCharacterSize(25);
	m_lostText.setFont(m_font);
	m_lostText.setString("You have lost man.");
	m_lostText.setPosition(static_cast<float>(config::WIDTH) / 2, static_cast<float>(config::HEIGHT) / 2);
	m_lostText.setOrigin(m_lostText.getGlobalBounds().width / 2, m_lostText.getGlobalBounds().height / 2);
	m_wonText.setFont(m_font);
	m_wonText.setString("You have won.");
	m_wonText.setPosition(static_cast<float>(config::WIDTH) / 2, static_cast<float>(config::HEIGHT) / 2);
	m_wonText.setOrigin(m_wonText.getGlobalBounds().width / 2, m_wonText.getGlobalBounds().height / 2);
	m_soundPopBuffer.loadFromFile("../Assets/pop.wav");
	m_soundTeleportBuffer.loadFromFile("../Assets/teleport.wav");
	m_soundThrustBuffer.loadFromFile("../Assets/thrust.wav");
	m_soundPop.setBuffer(m_soundPopBuffer);
	m_soundPop.setVolume(20);
	m_soundShot.setBuffer(m_soundPopBuffer);
	m_soundShot.setPitch(2.0f);
	m_soundShot.setVolume(20);
	m_soundTeleport.setBuffer(m_soundTeleportBuffer);
	m_soundTeleport.setVolume(20);
	m_soundThrust.setBuffer(m_soundThrustBuffer);
	m_soundThrust.setVolume(20);
	m_soundThrust.setLoop(true);
	m_gameState = GameState::PLAYING;
	m_asteroids.push_back(new Asteroid());
	m_inputManager = &_inputManager;
	buttonUp = new AccelerateShipCommand();
	buttonDown = new AccelerateShipCommand();
	buttonLeft = new RotateShipCommand();
	buttonRight = new RotateShipCommand();
	buttonQ = new TeleportShipCommand();
	m_livesGUI = new sf::ConvexShape[5];
	for (int i = 0; i < 5; i++)
	{
		m_livesGUI[i].setPointCount(4);
		m_livesGUI[i].setPoint(0, sf::Vector2f(15.5f, 3.0f));
		m_livesGUI[i].setPoint(1, sf::Vector2f(28.0f, 27.0f));
		m_livesGUI[i].setPoint(2, sf::Vector2f(15.5f, 21.0f));
		m_livesGUI[i].setPoint(3, sf::Vector2f(3.0f, 27.0f));
		m_livesGUI[i].setFillColor(sf::Color::Transparent);
		m_livesGUI[i].setOutlineThickness(2);
		m_livesGUI[i].setOutlineColor(sf::Color::White);
		m_livesGUI[i].setOrigin(16.0f, 16.0f);
		m_livesGUI[i].setPosition(sf::Vector2f( 32 + static_cast<float>(i) * 16, 30));
		m_livesGUI[i].setScale(0.5f, 0.5f);
	}
	m_shootingCooldown = 0;
	m_UFOCooldown = 180;
	m_playerLives = 5;
	m_levelCount = 1;
	m_score = 0;
	m_breakTime = 180;
	m_isIntersecting = false;
	m_wasIntersecting = false;
};

Game::~Game()
{
	delete buttonUp;
	delete buttonDown;
	delete buttonLeft;
	delete buttonRight;
	delete buttonQ;
	delete[] m_livesGUI;
	buttonUp = nullptr;
	buttonDown = nullptr;
	buttonLeft = nullptr;
	buttonRight = nullptr;
	buttonQ = nullptr;
	m_livesGUI = nullptr;
}

bool Game::Update(float deltaTime)
{
	switch (m_gameState)
	{
	case GameState::PLAYING:
		handleInput();
		m_ship.Update();
		m_ufo.Update();
		updateAsteroids();
		updateCooldowns();
		updateBullets();
		checkCollision();
		m_scoreText.setString(std::to_string(m_score));
		if (m_asteroids.size() == 0)
		{
			increaseLevel();
		}
		
		if (m_playerLives == 0) 
		{
			m_gameState = GameState::LOST;
			m_soundThrust.stop();
		}
		break;
	case GameState::LOST:
		m_lostText.setString("You have lost.\n   Score: " + std::to_string(m_score));
		break;
	case GameState::WON:
		m_lostText.setString("You have won.\n   Score: " + std::to_string(m_score));
		break;
	}
	return true;
}

void Game::Draw(sf::RenderWindow &_window)
{
	switch(m_gameState)
	{
	case GameState::PLAYING:
		m_ship.Draw(_window);
		m_ufo.Draw(_window);
		_window.draw(m_scoreText);
		for (int i = 0; i < m_friendlyBullets.size(); i++)
			m_friendlyBullets.at(i)->Draw(_window);
		for (int i = 0; i < m_enemyBullets.size(); i++)
			m_enemyBullets.at(i)->Draw(_window);
		for (int i = 0; i < m_playerLives; i++)
			_window.draw(m_livesGUI[i]);
		for (int i = 0; i < m_asteroids.size(); i++)
			m_asteroids.at(i)->Draw(_window);
		break;

	case GameState::LOST:
		_window.draw(m_lostText);
		break;
	case GameState::WON:
		_window.draw(m_wonText);
		break;
	}
}

void Game::onKeyPressed(sf::Keyboard::Key& _key)
{
	m_inputManager->setKey(_key, true);
}

void Game::onKeyReleased(sf::Keyboard::Key& _key)
{
	m_inputManager->setKey(_key, false);
}

void Game::handleInput()
{
	if (m_inputManager->isKeyPressed(sf::Keyboard::Up))
	{
		m_soundThrust.play();
	}
	if (m_inputManager->isKeyReleased(sf::Keyboard::Up))
	{
		m_soundThrust.stop();
	}
	if (m_inputManager->isKeyDown(sf::Keyboard::Up))
	{
		buttonUp->execute(m_ship, 1.0f);
	}
	if (m_inputManager->isKeyDown(sf::Keyboard::Down))
	{
		buttonDown->execute(m_ship, -1.0f);
	}
	if (m_inputManager->isKeyDown(sf::Keyboard::Left))
	{
		buttonLeft->execute(m_ship, -1.0f);
	}
	if (m_inputManager->isKeyDown(sf::Keyboard::Right))
	{
		buttonLeft->execute(m_ship, 1.0f);
	}
	if (m_inputManager->isKeyPressed(sf::Keyboard::Q))
	{
		buttonQ->execute(m_ship, 0);
		m_soundTeleport.play();
	}
	if (m_inputManager->isKeyDown(sf::Keyboard::Space)) 
	{
		if (m_shootingCooldown == 0) 
		{
			m_shootingCooldown = 24;
			m_friendlyBullets.push_back(m_ship.shoot());
			m_soundShot.play();
		}
	}
}

void Game::updateCooldowns()
{
	if (m_shootingCooldown > 0)
		m_shootingCooldown--;
	if (m_UFOCooldown > 0)
		m_UFOCooldown--;
}

void Game::updateBullets()
{
	if (m_UFOCooldown == 0 && m_ufo.m_isActive)
	{
		m_UFOCooldown = rand() % 600 + 20;
		m_enemyBullets.push_back(m_ufo.shoot(m_ship));
	}
	for (int i = 0; i < m_friendlyBullets.size(); i++)
	{
		m_friendlyBullets.at(i)->Update();
		if (m_friendlyBullets.front()->getLifetime() < 0)
			m_friendlyBullets.erase(m_friendlyBullets.begin());
	}
	for (int i = 0; i < m_enemyBullets.size()  ; i++)
	{
		m_enemyBullets.at(i)->Update();
		if (m_enemyBullets.front()->getLifetime() < 0)
			m_enemyBullets.erase(m_enemyBullets.begin());
	}
}

void Game::updateAsteroids()
{
	for (int i = 0; i < m_asteroids.size(); i++)
		m_asteroids.at(i)->Update();
}

void Game::checkCollision()
{
	//update intersection bool
	m_wasIntersecting = m_isIntersecting;

	//ship hits ufo
	if (m_ship.getGlobalBounds().intersects(m_ufo.getGlobalBounds()) && m_ufo.m_isActive)
	{
		m_isIntersecting = true;
	}
	else
	{
		m_isIntersecting = false;
	}

	//ship hits bullets
	for (int i = 0; i < m_enemyBullets.size(); i++)
	{
		if (m_ship.getGlobalBounds().intersects(m_enemyBullets.at(i)->getGlobalBounds()))
		{
			m_playerLives--;
			m_enemyBullets.erase(m_enemyBullets.begin()+i);
		}
	}

	//ship hits asteroids
	for (int i = 0; i < m_asteroids.size(); i++)
	{
		if (m_ship.getGlobalBounds().intersects(m_asteroids.at(i)->getGlobalBounds()))
		{
			m_isIntersecting = true;
		}
		else
		{
			m_isIntersecting = false;
		}
	}

	//bullets hit ufo
	for (int i = 0; i < m_friendlyBullets.size(); i++)
	{
		if (m_ufo.getGlobalBounds().intersects(m_friendlyBullets.at(i)->getGlobalBounds()) && m_ufo.m_isActive)
		{
			m_score += 100;
			m_soundPop.play();
			m_ufo.m_isActive = false;
			m_friendlyBullets.erase(m_friendlyBullets.begin() + i);
		}
	}

	//bullets hit asteroids
	for (int i = 0; i < m_friendlyBullets.size(); i++)
	{
		for (int j = 0; j < m_asteroids.size(); j++)
		{
			if (m_asteroids.at(j)->getGlobalBounds().intersects(m_friendlyBullets.at(i)->getGlobalBounds()))
			{
				m_score += 20;
				m_soundPop.play();
				m_asteroids.push_back(m_asteroids.at(j)->split());
				if (m_asteroids.at(j)->getState() > 2) 
				{
					m_asteroids.erase(m_asteroids.begin() + j);
					m_asteroids.pop_back();
				}
				m_friendlyBullets.erase(m_friendlyBullets.begin() + i);
				break;
			}
		}
	}

	if(m_isIntersecting && !m_wasIntersecting)
		m_playerLives--;
}

void Game::increaseLevel()
{
	m_breakTime--;
	if (m_breakTime < 0) 
	{
		m_breakTime = 180;
		m_levelCount++;
		switch (m_levelCount) 
		{
		case 1:
			for(int i = 0; i < 3; i++)
			m_asteroids.push_back(new Asteroid());
			break;
		case 2:
			for (int i = 0; i < 5; i++)
				m_asteroids.push_back(new Asteroid());
			break;
		case 3:
			for (int i = 0; i < 7; i++)
				m_asteroids.push_back(new Asteroid());
			break;
		case 4:
			for (int i = 0; i < 10; i++)
				m_asteroids.push_back(new Asteroid());
			break;
		case 5:
			m_gameState = GameState::WON;
			m_soundThrust.stop();
			break;
		default:
			break;
		}
		m_ufo.setPosition(sf::Vector2f(static_cast<float>(rand() % config::WIDTH), static_cast<float>(rand() % config::HEIGHT)));
		m_ufo.m_isActive = true;
	}
}



