#include "Enemy.h"

Enemy::Enemy(float x, float y, float size, sf::Color color, float speed)
{
    this->shape.setSize(sf::Vector2f(size, size));
    this->shape.setFillColor(color);
    this->shape.setPosition(sf::Vector2f(x, y));
    this->speed = speed;
}

Enemy::~Enemy() {}

const sf::FloatRect Enemy::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const sf::Color Enemy::getColor() const
{
    return this->shape.getFillColor();
}


void Enemy::update()
{
    this->shape.move(sf::Vector2f(0.0f, this->speed));
}

void Enemy::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}
