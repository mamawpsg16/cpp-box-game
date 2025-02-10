#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <sstream>

class Game
{
private:

	sf::RenderWindow* window;
	sf::Vector2i mouseWindowPosition;
	sf::Vector2f mouseViewPosition;

	/* Resources */
	sf::Font font;

	/* Text */
	sf::Text* text;  // Change to pointer

	/* Game Logic*/
	unsigned points;
	int health;
	bool endGame;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	/* Game Objects */
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;

private:
	void initializeVariables();
	void initializeWindow();
	void initializeEnemies();
	void initializeFonts();
	void initializeTexts();

public:
	Game();

	//Accessors
	const bool isRunning() const;
	const bool isEndGame() const;

	//Methods
	void spawnEnemy();
	void handleEnemyClick();
	void updateEnemies();
	void updateText();
	void updateMousePositions();
	void pollEvents();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();

	virtual ~Game();
};

