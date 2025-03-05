#include "Food.h"
#include <QRandomGenerator>
#include <QVector>
#include "GameConstants.h"

Food::Food() {
    m_position = QPointF(-100, -100);
}

const QPointF& Food::position() const {
    return m_position;
}

void Food::respawn(const QVector<QPointF>& snakeBody) {
    do {
        m_position.setX(QRandomGenerator::global()->bounded(GameConstants::FIELD_WIDTH));
        m_position.setY(QRandomGenerator::global()->bounded(GameConstants::FIELD_HEIGHT));
    } while(!isValidPosition(m_position, snakeBody));
}

bool Food::isValidPosition(const QPointF& pos, const QVector<QPointF>& snakeBody) const {
    if(pos.x() < 0 || pos.x() >= GameConstants::FIELD_WIDTH ||
        pos.y() < 0 ||  pos.y() >= GameConstants::FIELD_HEIGHT) 
    {
        return false;
    }
    
    for(const QPointF& segment : snakeBody) {
        qreal dx = pos.x() - segment.x();
        qreal dy = pos.y() - segment.y();
        qreal distanceSquared = dx*dx + dy*dy;
        if(distanceSquared < (GameConstants::DOT_SIZE * GameConstants::DOT_SIZE)) {
            return false;
        }
    }
    return true;
}
