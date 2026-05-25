#include "Paddle.h"
#include "Constants.h"

Paddle::Paddle(float x, float y) {
    shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    shape.setOrigin(PADDLE_WIDTH / 2.0f, PADDLE_HEIGHT / 2.0f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Cyan);

    speed = PADDLE_SPEED;
}

void Paddle::update(float deltaTime) {
    sf::Vector2f position = shape.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.x -= speed * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.x += speed * deltaTime;
    }

    float halfWidth = shape.getSize().x / 2.0f;

    if (position.x - halfWidth < 0.0f) {
        position.x = halfWidth;
    }

    if (position.x + halfWidth > WINDOW_WIDTH) {
        position.x = WINDOW_WIDTH - halfWidth;
    }

    shape.setPosition(position);
}

void Paddle::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}

void Paddle::changeWidth(float factor)
{
    sf::Vector2f size = shape.getSize();

    size.x *= factor;

    if (size.x < 60.0f)
    {
        size.x = 60.0f;
    }

    if (size.x > 200.0f)
    {
        size.x = 200.0f;
    }

    shape.setSize(size);
    shape.setOrigin(size.x / 2.0f, size.y / 2.0f);
}