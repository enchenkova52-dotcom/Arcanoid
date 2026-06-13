#pragma once

#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape;
    float speed;

public:
    Paddle(float x, float y);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    void changeWidth(float factor);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
};