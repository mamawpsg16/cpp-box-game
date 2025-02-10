#include "Game.h"
#include <iostream>
/* CONSTRUCTOR */
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
    this->initializeFonts();
    this->initializeTexts();
    this->initializeEnemies();

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

void Game::initializeEnemies()
{
    this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
    this->enemy.setFillColor(sf::Color::Cyan);
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
    /*
        @return void

        Spawn enemies and  sets their types, colors and spawn them position randomly
        - sets a random position.
        - sets a random color.
        - adds enemy to the vector.
    */

    this->enemy.setPosition(
        sf::Vector2f(
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            0.0f
        )
    );

    //Randomize enemy type;
    int type = rand() % 5;

    switch (type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(15.0f, 15.0f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.0f, 30.0f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.0f, 50.0f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.0f, 70.0f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(90.0f, 90.0f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    default:
        this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    }

    /* Spawn the enemy */
    this->enemies.emplace_back(enemy);
}


void Game::handleEnemyClick()
{
    // We use an iterator to go through the enemies in the list
    auto it = this->enemies.begin();
    while (it != this->enemies.end())  // Loop through the list of enemies
    {
        const sf::FloatRect bounds = it->getGlobalBounds();  // Get the boundaries of the enemy
        if (bounds.contains(this->mouseViewPosition))  // Check if the enemy was clicked
        {
            if (it->getFillColor() == sf::Color::Magenta)  // If the enemy is Magenta
            {
                this->points += 10;  // Add 10 points to the score
            }else if (it->getFillColor() == sf::Color::Blue)  // If the enemy is Magenta
            {
                this->points += 7;  // Add 10 points to the score
            }else if (it->getFillColor() == sf::Color::Cyan)  // If the enemy is Magenta
            {
                this->points += 5;  // Add 10 points to the score
            }else if (it->getFillColor() == sf::Color::Red)  // If the enemy is Magenta
            {
                this->points += 3;  // Add 10 points to the score
            }else if (it->getFillColor() == sf::Color::Green)  // If the enemy is Magenta
            {
                this->points += 2;  // Add 10 points to the score
            }
            else if (it->getFillColor() == sf::Color::Yellow)  // If the enemy is Magenta
            {
                this->points += 1;  // Add 10 points to the score
            }

            it = this->enemies.erase(it);  // Remove the clicked enemy from the list
        }
        else
        {
            ++it;  // Move to the next enemy in the list
        }
    }
}

void Game::updateEnemies()
{
    /*
        @return void

        Update the enemy spawn timer and spawn enemies
        when the total amount  of enemies is smaller than
        the maximum number of enemies
        - Remove the enemies at the edge of the screen
    */

    //Updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= enemySpawnTimerMax) {

            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.0f;
        }
        else {
            this->enemySpawnTimer += 1.0f;
        }
    }

    /* Move the enemies */
    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].move(sf::Vector2f(0.0f, 2.0f));

        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            i--; // Decrement i to account for the shift
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
    /* Render all the enemies */
    for (auto& e : this->enemies)
    {
        target.draw(e);
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
