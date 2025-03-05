#pragma once
#include "Snake.h"
#include "Food.h"
#include "GameConstants.h"

class GameEngine {
public:
    GameEngine();
    
    void update();
    void handleInput(Qt::Key key);
    bool isGameOver() const;
    
    const Snake& snake() const;
    const Food& food() const;

private:
    Snake m_snake;
    Food m_food;
    bool m_gameOver;
    
    void checkCollisions();
    void checkFood();
    void checkBoundaries();
};