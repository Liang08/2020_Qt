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
    snakeData snake_0;
    Obstacle ob;

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:


signals:

public slots:
};

#endif // SNAKELABEL_H
