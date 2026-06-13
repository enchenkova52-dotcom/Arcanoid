#include "Bonus.h"
#include "Paddle.h"
#include "Ball.h"

Bonus::Bonus(float x, float y) {
    shape.setSize(sf::Vector2f(25.f, 25.f));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

void Bonus::update(float dt) {
    shape.move(0.f, speed * dt);
}

void Bonus::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Bonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool Bonus::isActive() const {
    return active;
}

void Bonus::deactivate() {
    active = false;
}

PaddleSizeBonus::PaddleSizeBonus(float x, float y) : Bonus(x, y) {
    shape.setFillColor(sf::Color::Green);
}

void PaddleSizeBonus::apply(Paddle& paddle, Ball& ball, bool& bottomShield) {
    paddle.changeWidth(1.25f);
}

BottomShieldBonus::BottomShieldBonus(float x, float y) : Bonus(x, y) {
    shape.setFillColor(sf::Color::Cyan);
}

void BottomShieldBonus::apply(Paddle& paddle, Ball& ball, bool& bottomShield) {
    bottomShield = true;
}

RandomDirectionBonus::RandomDirectionBonus(float x, float y) : Bonus(x, y) {
    shape.setFillColor(sf::Color::Magenta);
}

void RandomDirectionBonus::apply(Paddle& paddle, Ball& ball, bool& bottomShield) {
    ball.randomizeDirection();
}
