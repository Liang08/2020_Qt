#include "snakelabel.h"
#include <QDebug>

SnakeLabel::SnakeLabel(QWidget *parent) : QLabel(parent)
{

}

void SnakeLabel::mousePressEvent(QMouseEvent *event){
    int i = event->x() / 25;
    int j = event->y() / 25 - 2;
    if(i < 40 && j < 40)
        addToObstacle(i, j);
    emit freshen();
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
