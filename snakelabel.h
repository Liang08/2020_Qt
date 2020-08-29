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
    snakeData snake_0;
    Obstacle ob;
    int status;
    int applePosition[2];
    void addToObstacle(int i, int j);
    void addSnake(int x, int y);
    void setSnake(int x, int y);
    void setSnakeTail(int x, int y);
    bool touchObstacle(int i);
    void snakeGo();
    void snakeEatApple();
    int getAppleNum();
    void setAppleNumber();
    void createApple();
    bool isOK();


protected:
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent *ev) override;

private:
    int appleNum;
    bool appleExit = false;


signals:
    void freshen();
    void freshen_0();
    void wrong();
    void startTime();


public slots:
};

#endif // SNAKELABEL_H
