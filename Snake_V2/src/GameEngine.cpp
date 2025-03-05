#define _USE_MATH_DEFINES
#include <cmath>
#include "GameEngine.h"

GameEngine::GameEngine() : m_gameOver(false) {
    m_food.respawn(m_snake.body());
}

bool GameEngine::isGameOver() const { // Добавить const
    return m_gameOver;
}

const Snake& GameEngine::snake() const { // Добавить const
    return m_snake;
}

const Food& GameEngine::food() const { // Добавить const
    return m_food;
}

void GameEngine::update() {
    if(m_gameOver) return;
    
    m_snake.move();
    checkCollisions();
}

void GameEngine::handleInput(Qt::Key key) {
    qreal angleStep = M_PI / 12; // Шаг поворота 15 градусов
    
    switch(key) {
        case Qt::Key_Right: 
            m_snake.setAngle(m_snake.angle() + angleStep);
            break;
        case Qt::Key_Left: 
            m_snake.setAngle(m_snake.angle() - angleStep);
            break;
        default: 
            return;
    }
}

void GameEngine::checkCollisions() {
    checkBoundaries();
    checkFood();
    if(m_snake.checkSelfCollision()) {
        m_gameOver = true;
    }
}

void GameEngine::checkFood() {
    const QPointF& head = m_snake.body().first();
    const QPointF& foodPos = m_food.position();
    qreal dx = head.x() - foodPos.x();
    qreal dy = head.y() - foodPos.y();
    qreal distanceSquared = dx*dx + dy*dy;
    
    if(distanceSquared < (GameConstants::DOT_SIZE * GameConstants::DOT_SIZE)) {
        m_snake.grow();
        m_food.respawn(m_snake.body());
    }
}

void GameEngine::checkBoundaries() {
    const QPointF& head = m_snake.body().first();
    if(head.x() < 0 || head.x() >= GameConstants::FIELD_WIDTH 
       || head.y() < 0 || head.y() >= GameConstants::FIELD_HEIGHT) 
    {
        m_gameOver = true;
    }
}