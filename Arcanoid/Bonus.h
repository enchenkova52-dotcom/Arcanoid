#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Paddle;
class Ball;

class Bonus {
protected:
    sf::RectangleShape shape;
    float speed = 150.f;
    bool active = true;

public:
    Bonus(float x, float y);
    virtual ~Bonus() = default;

    virtual void apply(Paddle& paddle, Ball& ball, bool& bottomShield) = 0;

    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    bool isActive() const;
    void deactivate();
};

class PaddleSizeBonus : public Bonus {
public:
    PaddleSizeBonus(float x, float y);
    void apply(Paddle& paddle, Ball& ball, bool& bottomShield) override;
};

class BottomShieldBonus : public Bonus {
public:
    BottomShieldBonus(float x, float y);
    void apply(Paddle& paddle, Ball& ball, bool& bottomShield) override;
};

class RandomDirectionBonus : public Bonus {
public:
    RandomDirectionBonus(float x, float y);
    void apply(Paddle& paddle, Ball& ball, bool& bottomShield) override;
};
