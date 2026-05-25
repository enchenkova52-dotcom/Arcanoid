#pragma once

#include <SFML/Graphics.hpp>

class Block {
private:
    sf::RectangleShape shape;

    bool destroyed;
    bool unbreakable;
    bool speedUp;
    bool hasBonus;

    int health;

public:
    Block(
        float x,
        float y,
        float width,
        float height,
        int hp,
        bool solid,
        bool speed,
        bool bonus
    );

    void hit();

    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;

    bool isDestroyed() const;

    bool isUnbreakable() const;

    bool isSpeedUp() const;

    bool containsBonus() const;
};