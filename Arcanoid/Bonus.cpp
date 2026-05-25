#include "Bonus.h"

Bonus::Bonus(float x, float y)
{
    shape.setSize(sf::Vector2f(18.0f, 18.0f));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Yellow);

    speed = 160.0f;
    active = true;
}

void Bonus::update(float deltaTime)
{
    shape.move(0.0f, speed * deltaTime);
}

void Bonus::draw(sf::RenderWindow& window) const
{
    if (active)
    {
        window.draw(shape);
    }
}

sf::FloatRect Bonus::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Bonus::isActive() const
{
    return active;
}

void Bonus::deactivate()
{
    active = false;
}