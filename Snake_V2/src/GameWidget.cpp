#include "GameWidget.h"
#include "ResourceManager.h"
#include "GameConstants.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QtMath>

GameWidget::GameWidget(QWidget* parent) 
    : QWidget(parent), m_timerId(startTimer(GameConstants::MOVE_DELAY)) 
{
    setFixedSize(GameConstants::FIELD_WIDTH, GameConstants::FIELD_HEIGHT);
    setStyleSheet("background-color: black;");
}

void GameWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    
    if(m_engine.isGameOver()) {
        drawGameOver(painter);
    } else {
        drawGame(painter);
    }
}

void GameWidget::timerEvent(QTimerEvent* event) {
    if(event->timerId() == m_timerId) {
        m_engine.update();
        update();
    }
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    m_engine.handleInput(static_cast<Qt::Key>(event->key()));
}

void GameWidget::drawGame(QPainter& painter) {
    const auto& res = ResourceManager::instance();
    
    // Draw food
    QRectF foodRect(m_engine.food().position().x() - GameConstants::DOT_SIZE/2,
                    m_engine.food().position().y() - GameConstants::DOT_SIZE/2,
                    GameConstants::DOT_SIZE, GameConstants::DOT_SIZE);
    painter.drawImage(foodRect, res.foodImage());
    
    // Draw snake
    const auto& snakeBody = m_engine.snake().body();
    for(int i = 0; i < snakeBody.size(); ++i) {
        if(i == 0) {
            // Draw head with rotation
            painter.save();
            QPointF headPos = snakeBody[i];
            painter.translate(headPos);
            painter.rotate(qRadiansToDegrees(m_engine.snake().angle()));
            QRectF headRect(-GameConstants::DOT_SIZE/2, -GameConstants::DOT_SIZE/2,
                            GameConstants::DOT_SIZE, GameConstants::DOT_SIZE);
            painter.drawImage(headRect, res.headImage());
            painter.restore();
        } else {
            QRectF bodyRect(snakeBody[i].x() - GameConstants::DOT_SIZE/2,
                            snakeBody[i].y() - GameConstants::DOT_SIZE/2,
                            GameConstants::DOT_SIZE, GameConstants::DOT_SIZE);
            painter.drawImage(bodyRect, res.bodyImage());
        }
    }
}

void GameWidget::drawGameOver(QPainter& painter) {
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 24, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, "Game Over");
}
