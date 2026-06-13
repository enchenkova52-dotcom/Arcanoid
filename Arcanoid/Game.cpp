#include "Game.h"
#include "Constants.h"
#include "Block.h"
#include "Bonus.h"
#include <iostream>
#include <algorithm>
#include <memory>

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arcanoid"),
    ball(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f),
    paddle(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 40.0f),
    misses(0),
    score(0),
    bottomShield(true)
{
    window.setFramerateLimit(60);
    createBlocks();
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::createBlocks() {
    constexpr int rows = 4;
    constexpr int cols = 10;

    constexpr float blockWidth = 70.0f;
    constexpr float blockHeight = 25.0f;
    constexpr float startX = 35.0f;
    constexpr float startY = 50.0f;
    constexpr float gap = 5.0f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * (blockWidth + gap);
            float y = startY + row * (blockHeight + gap);

            if (row == 0) {
                blocks.push_back(std::make_unique<UnbreakableBlock>(x, y, blockWidth, blockHeight));
            }
            else if ((row == 1 || row == 2) && col % 2 == 0) {
                blocks.push_back(std::make_unique<SpeedUpBlock>(x, y, blockWidth, blockHeight));
            }
            else if (row == 3 && col % 3 == 0) {
                blocks.push_back(std::make_unique<BonusBlock>(x, y, blockWidth, blockHeight));
            }
            else {
                blocks.push_back(std::make_unique<Block>(x, y, blockWidth, blockHeight, 2));
            }
        }
    }
}


void Game::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::update(float deltaTime) {
    paddle.update(deltaTime);
    ball.update(deltaTime);

    handleWallCollisions();
    handlePaddleCollision();
    handleBlockCollisions();

    updateBonuses(deltaTime);

    if (ball.getPosition().y - BALL_RADIUS > WINDOW_HEIGHT)
    {
        if (bottomShield)
        {
            bottomShield = false;

            ball.reflectY();

            ball.setPosition(
                ball.getPosition().x,
                WINDOW_HEIGHT - BALL_RADIUS - 20
            );
        }
        else
        {
            ++misses;

            resetBall();
        }
    }
    std::cout << "Score: " << score
        << " | Misses: " << misses
        << " | Shield: " << bottomShield
        << std::endl;
}

void Game::handleBlockCollisions() {
    for (Block& block : blocks) {
        if (block.isDestroyed()) {
            continue;
        }

        if (ball.getBounds().intersects(block.getBounds())) {
            if (block.containsBonus())
            {
                sf::FloatRect bounds = block.getBounds();
                bonuses.emplace_back(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height);
            }
            block.hit();
            score++;
            if (block.isSpeedUp())
            {
                ball.increaseSpeed(1.15f);
            }
            ball.reflectY();
            return;
        }
    }
}

void Game::updateBonuses(float deltaTime)
{
    for (Bonus& bonus : bonuses)
    {
        if (!bonus.isActive())
        {
            continue;
        }

        bonus.update(deltaTime);

        if (bonus.getBounds().intersects(paddle.getBounds()))
        {
            paddle.changeWidth(1.25f);
            bottomShield = true;
            ball.randomizeDirection();
            bonus.deactivate();
        }
    }
}

void Game::handleWallCollisions() {
    sf::Vector2f position = ball.getPosition();

    if (position.x - BALL_RADIUS <= 0.0f) {
        ball.setPosition(BALL_RADIUS, position.y);
        ball.reflectX();
    }

    if (position.x + BALL_RADIUS >= WINDOW_WIDTH) {
        ball.setPosition(WINDOW_WIDTH - BALL_RADIUS, position.y);
        ball.reflectX();
    }

    if (position.y - BALL_RADIUS <= 0.0f) {
        ball.setPosition(position.x, BALL_RADIUS);
        ball.reflectY();
    }
}

void Game::handlePaddleCollision() {
    if (ball.getBounds().intersects(paddle.getBounds()) &&
        ball.getVelocity().y > 0.0f) {
        ball.reflectY();

        sf::Vector2f position = ball.getPosition();
        ball.setPosition(position.x, paddle.getPosition().y - PADDLE_HEIGHT / 2.0f - BALL_RADIUS);
    }
}

void Game::resetBall() {
    ball.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    ball.setVelocity(sf::Vector2f(BALL_SPEED_X, BALL_SPEED_Y));
}

void Game::render() {
    window.clear(sf::Color::Black);

    for (const Block& block : blocks) {
        block.draw(window);
    }

    ball.draw(window);
    paddle.draw(window);

    for (const Bonus& bonus : bonuses)
    {
        bonus.draw(window);
    }

    window.display();
}
