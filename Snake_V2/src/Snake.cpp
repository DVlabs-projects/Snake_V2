#include "Snake.h"
#include "GameConstants.h"
#include <cmath>

Snake::Snake() : 
    m_angle(0.0),
    m_prevTail(0, 0) 
{
    for(int i = 0; i < GameConstants::INITIAL_LENGTH; ++i) {
        m_body.append(QPointF(30 - i * GameConstants::DOT_SIZE, 30));
    }
}

void Snake::move() {
    m_prevTail = m_body.last();
    
    for(int i = m_body.size()-1; i > 0; --i) {
        m_body[i] = m_body[i-1];
    }
    
    QPointF& head = m_body[0];
    qreal dx = GameConstants::DOT_SIZE * cos(m_angle);
    qreal dy = GameConstants::DOT_SIZE * sin(m_angle);
    
    QTransform transform;
    transform.translate(dx, dy);
    QPointF newHead = transform.map(head);
    head = newHead;
}

void Snake::grow() {
    m_body.append(m_prevTail);
}

void Snake::setAngle(qreal newAngle) {
    m_angle = newAngle;
    // Нормализация угла в пределах [0, 2π)
    m_angle = fmod(m_angle, 2 * M_PI);
    if(m_angle < 0) {
        m_angle += 2 * M_PI;
    }
}

bool Snake::checkSelfCollision() const {
    const QPointF& head = m_body.first();
    const qreal collisionRadius = GameConstants::DOT_SIZE * 0.8; // 80% размера сегмента
    
    for(int i = 1; i < m_body.size(); ++i) {
        qreal dx = head.x() - m_body[i].x();
        qreal dy = head.y() - m_body[i].y();
        qreal distance = std::sqrt(dx*dx + dy*dy);
        
        if(distance < collisionRadius) {
            return true;
        }
    }
    return false;
}

const QVector<QPointF>& Snake::body() const { return m_body; }
qreal Snake::angle() const { return m_angle; }