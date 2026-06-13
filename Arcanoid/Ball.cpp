#include "Ball.h"
#include "Constants.h"
#include <random>

Ball::Ball(float x, float y) {
    shape.setRadius(BALL_RADIUS);
    shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);

    velocity = sf::Vector2f(BALL_SPEED_X, BALL_SPEED_Y);
}

void Ball::update(float deltaTime) {
    shape.move(velocity * deltaTime);
}

void Ball::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void Ball::reflectX() {
    velocity.x = -velocity.x;
}

void Ball::reflectY() {
    velocity.y = -velocity.y;
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

void Ball::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

void Ball::setVelocity(sf::Vector2f newVelocity) {
    velocity = newVelocity;
}

void Ball::increaseSpeed(float factor)
{
    velocity.x *= factor;
    velocity.y *= factor;
}
void Ball::randomizeDirection()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-300.0f, 300.0f);

    velocity.x = dist(gen);

    if (velocity.y > 0)
    {
        velocity.y = 250.0f;
    }
    else
    {
        velocity.y = -250.0f;
    }
}