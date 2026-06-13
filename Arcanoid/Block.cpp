#include "Block.h"
#include "Ball.h"
#include "Bonus.h"

Block::Block(float x, float y, float width, float height, int hp)
    : destroyed(false), health(hp)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Yellow);
}

void Block::onHit(Ball& ball, std::vector<std::unique_ptr<Bonus>>& bonuses)
{
    health--;

    if (health <= 0) {
        destroyed = true;
    }
}

void Block::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

sf::FloatRect Block::getBounds() const
{
    return shape.getGlobalBounds();
}

bool Block::isDestroyed() const
{
    return destroyed;
}

UnbreakableBlock::UnbreakableBlock(float x, float y, float width, float height)
    : Block(x, y, width, height, 1)
{
    shape.setFillColor(sf::Color(120, 120, 120));
}

void UnbreakableBlock::onHit(Ball& ball, std::vector<std::unique_ptr<Bonus>>& bonuses)
{
    // Неразрушаемый блок не теряет здоровье
}

SpeedUpBlock::SpeedUpBlock(float x, float y, float width, float height)
    : Block(x, y, width, height, 1)
{
    shape.setFillColor(sf::Color::Red);
}

void SpeedUpBlock::onHit(Ball& ball, std::vector<std::unique_ptr<Bonus>>& bonuses)
{
    ball.increaseSpeed(1.15f);
    destroyed = true;
}

BonusBlock::BonusBlock(float x, float y, float width, float height)
    : Block(x, y, width, height, 1)
{
    shape.setFillColor(sf::Color::Blue);
}

void BonusBlock::onHit(Ball& ball, std::vector<std::unique_ptr<Bonus>>& bonuses)
{
    sf::FloatRect bounds = shape.getGlobalBounds();

    bonuses.push_back(
        std::make_unique<PaddleSizeBonus>(
            bounds.left + bounds.width / 2.0f,
            bounds.top + bounds.height
        )
    );

    destroyed = true;
}
