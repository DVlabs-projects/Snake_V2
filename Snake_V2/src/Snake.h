#pragma once
#include <QVector>
#include <QPointF>
#include <QTransform>
#include "GameConstants.h"

class Snake {
public:
    Snake();
    
    void move();
    void grow();
    void setAngle(qreal newAngle);
    bool checkSelfCollision() const;
    
    const QVector<QPointF>& body() const;
    qreal angle() const;

private:
    QVector<QPointF> m_body;
    qreal m_angle; // Угол в радианах
    QPointF m_prevTail;
};
