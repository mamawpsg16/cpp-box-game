#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::RectangleShape shape;
    float speed;

public:
    Enemy(float x, float y, float size, sf::Color color, float speed);
    ~Enemy();

    // Accessors
    const sf::FloatRect getBounds() const;
    const sf::Color getColor() const;

    // Methods
    void update();
    void render(sf::RenderTarget& target);
};
