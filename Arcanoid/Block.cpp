#include "Block.h"

Block::Block(
    float x,
    float y,
    float width,
    float height,
    int hp,
    bool solid,
    bool speed,
    bool bonus
)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::White);

    destroyed = false;
    health = hp;
    unbreakable = solid;
    speedUp = speed;
    hasBonus = bonus;

    if (unbreakable)
    {
        shape.setFillColor(sf::Color(120, 120, 120));
    }
    else if (speedUp)
    {
        shape.setFillColor(sf::Color(255, 20, 147));
    }
    else
    {
        shape.setFillColor(sf::Color(255, 105, 180));
    }
}

void Block::hit()
{
    if (unbreakable)
    {
        return;
    }

    health--;

    if (health == 1)
    {
        shape.setFillColor(sf::Color(255, 180, 220));
    }

    if (health <= 0)
    {
        destroyed = true;
    }
}

void Block::draw(sf::RenderWindow& window) const
{
    if (!destroyed)
    {
        window.draw(shape);
    }
}

sf::FloatRect Block::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Block::isDestroyed() const
{
    return destroyed;
}

bool Block::isUnbreakable() const
{
    return unbreakable;
}

bool Block::isSpeedUp() const
{
    return speedUp;
}
bool Block::containsBonus() const
{
    return hasBonus;
}