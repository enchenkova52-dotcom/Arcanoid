#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Ball;
class Bonus;

class Block {
protected:
    sf::RectangleShape shape;
    bool destroyed;
    int health;

public:
    Block(float x, float y, float width, float height, int hp);
    virtual ~Block() = default;

    virtual void onHit(Ball& ball, std::vector<std::unique_ptr<Bonus>>& bonuses);

    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    bool isDestroyed() const;
};

class UnbreakableBlock : public Block {
public:
    UnbreakableBlock(float x, float y, float width, float height);

    void onHit(Ball& ball, std::vector<std::unique_ptr<Bonus>>& bonuses) override;
};

class SpeedUpBlock : public Block {
public:
    SpeedUpBlock(float x, float y, float width, float height);

    void onHit(Ball& ball, std::vector<std::unique_ptr<Bonus>>& bonuses) override;
};

class BonusBlock : public Block {
public:
    BonusBlock(float x, float y, float width, float height);

    void onHit(Ball& ball, std::vector<std::unique_ptr<Bonus>>& bonuses) override;
};
