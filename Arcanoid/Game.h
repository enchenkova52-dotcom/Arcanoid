#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include <vector>
#include "Block.h"
#include "Bonus.h"

class Game {
private:
    sf::RenderWindow window;
    Ball ball;
    Paddle paddle;
    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;

    void updateBonuses(float deltaTime);
   


    void createBlocks();
    void handleBlockCollisions();
    int misses;
    int score;
    bool bottomShield;

    void processEvents();
    void update(float deltaTime);
    void render();

    void handleWallCollisions();
    void handlePaddleCollision();
    void resetBall();

public:
    Game();
    void run();
};