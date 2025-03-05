#pragma once
#include <QWidget>
#include "GameEngine.h"
#include <QKeyEvent>
#include <QTimerEvent>

class GameWidget : public QWidget {
    Q_OBJECT
public:
    GameWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    GameEngine m_engine;
    int m_timerId;
    
    void drawGame(QPainter& painter);
    void drawGameOver(QPainter& painter);
};