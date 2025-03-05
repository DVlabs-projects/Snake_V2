#pragma once
#include <QPoint>
#include <QVector>
#include "GameConstants.h"

class Food {
public:
    Food();
    
    void respawn(const QVector<QPointF>& snakeBody);
    const QPointF& position() const;

private:
    QPointF m_position;
    
    bool isValidPosition(const QPointF& pos, const QVector<QPointF>& snakeBody) const;
};