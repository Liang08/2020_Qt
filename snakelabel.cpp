#include "snakelabel.h"
#include <stdlib.h>
#include <QDebug>

SnakeLabel::SnakeLabel(QWidget *parent) : QLabel(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void SnakeLabel::mousePressEvent(QMouseEvent *event){
    int i = event->x() / 25;
    int j = event->y() / 25 - 2;
    if(i < 40 && j < 40)
        addToObstacle(i, j);
    emit freshen();
}

void SnakeLabel::keyPressEvent(QKeyEvent *ev){
    if (ev->key() == Qt::Key_Left){
        if (snake_0.data[0].x <= snake_0.data[1].x)
            snake_0.setDirection(2);
    }
    else if (ev->key() == Qt::Key_Right){
        if (snake_0.data[0].x >= snake_0.data[1].x)
            snake_0.setDirection(3);
    }
    else if(ev->key() == Qt::Key_Up){
        if (snake_0.data[0].y <= snake_0.data[1].y)
            snake_0.setDirection(0);
    }
    else if (ev->key() == Qt::Key_Down){
        if (snake_0.data[0].y >= snake_0.data[1].y)
            snake_0.setDirection(1);
    }
}

void SnakeLabel::addToObstacle(int i, int j){
    ob.addObstacle(i, j);
}


void SnakeLabel::addSnake(int x_0, int y_0){
    snake_0.data.push_back(Position(x_0, y_0));
    emit freshen();
}

void SnakeLabel::setSnake(int x, int y){
    snake_0.data[0] = Position(x, y);
    emit freshen();
}

void SnakeLabel::setSnakeTail(int x, int y){
    if(snake_0.data.size() == 1)
        snake_0.data.insert(snake_0.data.begin() + 1, Position(x, y));
    else
        snake_0.data[1] = Position(x, y);
    emit freshen();
}

bool SnakeLabel::touchObstacle(int i){
    return ob.obs[snake_0.data[i].x][snake_0.data[i].y] == 1;
}

void SnakeLabel::snakeGo(){
    for(int i = snake_0.data.size() - 1; i > 0; i --){
        snake_0.data[i] = snake_0.data[i - 1];
    }
    switch (snake_0.getDirection()) {
    case 0 :
        snake_0.data[0].y --;
        break;
    case 1 :
        snake_0.data[0].y ++;
        break;
    case 2 :
        snake_0.data[0].x --;
        break;
    default:
        snake_0.data[0].x ++;
        break;
    }
    if (!isOK())
        emit wrong();
    else
        emit freshen();
}

void SnakeLabel::snakeEatApple(){
    switch (snake_0.getDirection()) {
    case 0 :
        snake_0.data.insert(snake_0.data.begin(), Position(snake_0.data[0].x, snake_0.data[0].y - 1));
        break;
    case 1 :
        snake_0.data.insert(snake_0.data.begin(), Position(snake_0.data[0].x, snake_0.data[0].y + 1));
        break;
    case 2 :
        snake_0.data.insert(snake_0.data.begin(), Position(snake_0.data[0].x - 1, snake_0.data[0].y));
        break;
    default:
        snake_0.data.insert(snake_0.data.begin(), Position(snake_0.data[0].x + 1, snake_0.data[0].y));
        break;
    }
    appleNum --;
    if (!isOK())
        emit wrong();
    else
        emit freshen();
}

int SnakeLabel::getAppleNum(){
    return appleNum;
}

void SnakeLabel::setAppleNumber(){
    appleNum = 3;
}

void SnakeLabel::createApple(){
    for (;;) {
        srand((unsigned int)(time(0)));
        applePosition[0] = rand() % 40;
        applePosition[1] = rand() % 40;
        int flag = 0;
        for (auto a : snake_0) {
            if(applePosition[0] == a.x || applePosition[1] == a.y){
                flag = 1;
                break;
            }
        }
        if(ob.obs[applePosition[0]][applePosition[1]] == 1)
            flag = 1;
        if (flag == 0)
            break;
    }
    emit freshen();
}

bool SnakeLabel::isOK(){
    auto a = snake_0.begin();
    a ++;
    for (; a < snake_0.end(); a ++) {
        if(snake_0.data[0].x == a->x && snake_0.data[0].y == a->y){
            return false;
        }
    }
    if(ob.obs[snake_0.data[0].x][snake_0.data[0].y] == 1)
        return false;
    if(snake_0.data[0].x < 0 || snake_0.data[0].x > 39 || snake_0.data[0].y < 0 || snake_0.data[0].y > 39)
        return false;
    return true;
}
