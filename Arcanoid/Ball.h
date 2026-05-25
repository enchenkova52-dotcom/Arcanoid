#pragma once

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Ball(float x, float y);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    void reflectX();
    void reflectY();

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;

    void setPosition(float x, float y);
    void setVelocity(sf::Vector2f newVelocity);
    void increaseSpeed(float factor);
    void randomizeDirection();
};