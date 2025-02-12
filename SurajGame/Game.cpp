#include "Game.h"
#include <sstream>
#include <iostream>
/* CONSTRUCTOR */
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
    this->initializeFonts();
    this->initializeTexts();

}

/* PRIVATE METHODS */
void Game::initializeVariables()
{
	this->window = nullptr;
    this->endGame = false;
    this->points = 0;
    this->text = nullptr;
    this->health = 10;
    this->enemySpawnTimerMax = 5.0f;
    this->enemySpawnTimer =this->enemySpawnTimerMax;
    this->maxEnemies = 5;
}

void Game::initializeWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600}), "SFML works!");
    this->window->setFramerateLimit(60);
}


void Game::initializeFonts()
{
    if (!this->font.openFromFile("../resources/Fonts/Roboto.ttf")) {
        std::cout << "Current directory: " << std::filesystem::current_path() << std::endl;
        std::cout << "Error Failed to Initialize Font" << '\n';
    }
}

void Game::initializeTexts()
{
    this->text = new sf::Text(this->font);
    this->text->setCharacterSize(24);
    this->text->setFillColor(sf::Color::White);
    this->text->setString("Test");
}

const bool Game::isRunning() const
{
	return this->window->isOpen();
}

const bool Game::isEndGame() const
{
    return this->endGame;
}

void Game::updateMousePositions()
{
    /* @ return void
        Updates the mouse positions:
        - relative to the window (Vector2i)
    */
    this->mouseWindowPosition = sf::Mouse::getPosition(*this->window);
    this->mouseViewPosition = this->window->mapPixelToCoords(this->mouseWindowPosition);
}

void Game::pollEvents()
{
    while (const std::optional event = this->window->pollEvent())
    {
        if (event->is<sf::Event::Closed>()) {
            this->window->close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                this->window->close();
            }
        }
        if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mouseButtonPressed->button == sf::Mouse::Button::Left)
            {
                this->handleEnemyClick();
            }
        }

    }
}

/* PUBLIC METHODS */
void Game::update()
{
    this->pollEvents();
    if (!this->endGame) {
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();
    }

    /* END THE GAME */
    if (this->health <= 0) {
        this->endGame = true;
    }
}

void Game::spawnEnemy()
{
    float x = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - 100));
    float y = 0.0f;

    int type = rand() % 5;
    float size = 0.0f;
    sf::Color color;
    float speed = 2.0f;

    switch (type)
    {
    case 0:
        size = 15.0f;
        color = sf::Color::Magenta;
        speed = 3.0f;
        break;
    case 1:
        size = 30.0f;
        color = sf::Color::Blue;
        speed = 2.8f;
        break;
    case 2:
        size = 50.0f;
        color = sf::Color::Cyan;
        speed = 2.5f;
        break;
    case 3:
        size = 70.0f;
        color = sf::Color::Red;
        speed = 2.2f;
        break;
    case 4:
        size = 90.0f;
        color = sf::Color::Green;
        speed = 2.0f;
        break;
    default:
        size = 100.0f;
        color = sf::Color::Yellow;
        speed = 1.8f;
        break;
    }

    this->enemies.emplace_back(x, y, size, color, speed);
}

void Game::handleEnemyClick()
{
    auto it = this->enemies.begin();
    while (it != this->enemies.end())
    {
        if (it->getBounds().contains(this->mouseViewPosition))
        {
            if (it->getColor() == sf::Color::Magenta) this->points += 10;
            else if (it->getColor() == sf::Color::Blue) this->points += 7;
            else if (it->getColor() == sf::Color::Cyan) this->points += 5;
            else if (it->getColor() == sf::Color::Red) this->points += 3;
            else if (it->getColor() == sf::Color::Green) this->points += 2;
            else if (it->getColor() == sf::Color::Yellow) this->points += 1;

            it = this->enemies.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::updateEnemies()
{
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.0f;
        }
        else
        {
            this->enemySpawnTimer += 1.0f;
        }
    }

    for (int i = enemies.size() - 1; i >= 0; i--)
    {
        enemies[i].update();

        // Calculate when the entire shape is off screen
        if (enemies[i].getBounds().position.y > this->window->getSize().y)
        {
            enemies.erase(enemies.begin() + i);
            health -= 1;
        }

    }
}

void Game::updateText()
{
    std::stringstream ss;
    ss << "Points: " << this->points << '\n' << "Health: " << this->health;
    this->text->setString(ss.str());
}


void Game::renderText(sf::RenderTarget& target)
{
    target.draw(*this->text);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    for (auto& enemy : this->enemies)
    {
        enemy.render(target);
    }
}


void Game::render()
{
    this->window->clear();
    /* DRAW OBJECTS*/
    this->renderEnemies(*this->window);
    this->renderText(*this->window);

    /* DISPLAY OBJECTS*/
    this->window->display();
}

/* DESTRUCTOR */
Game::~Game()
{
	delete this->window;
    delete this->text;
}
