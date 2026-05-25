#pragma once

#include <SFML/Graphics.hpp>

class Bonus {
private:
    sf::RectangleShape shape;
    float speed;
    bool active;

public:
    Bonus(float x, float y);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;

    bool isActive() const;
    void deactivate();
};