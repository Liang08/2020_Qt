#ifndef SNAKELABEL_H
#define SNAKELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include "snakedata.h"
#include "obstacle.h"

class SnakeLabel : public QLabel
{
    Q_OBJECT
public:
    explicit SnakeLabel(QWidget *parent = nullptr);
    void addToObstical(int i, int j);
    void addSnake(int x, int y);
    void setSnake(int x, int y);
    void setSnakeTail(int x, int y);
    snakeData snake_0;
    Obstacle ob;

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:


signals:
    void freshen();


public slots:
};

#endif // SNAKELABEL_H
