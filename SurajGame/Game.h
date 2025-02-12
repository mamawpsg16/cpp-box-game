#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

class Game
{
private:
    sf::RenderWindow* window;
    sf::Vector2i mouseWindowPosition;
    sf::Vector2f mouseViewPosition;

    /* Resources */
    sf::Font font;

    /* Text */
    sf::Text* text;

    /* Game Logic */
    unsigned points;
    int health;
    bool endGame;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;

    /* Game Objects */
    std::vector<Enemy> enemies;

private:
    void initializeVariables();
    void initializeWindow();
    void initializeFonts();
    void initializeTexts();

public:
    Game();

    // Accessors
    const bool isRunning() const;
    const bool isEndGame() const;

    // Methods
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
