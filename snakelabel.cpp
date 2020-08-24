#include "snakelabel.h"
#include <QDebug>

SnakeLabel::SnakeLabel(QWidget *parent) : QLabel(parent)
{

}

void SnakeLabel::mousePressEvent(QMouseEvent *event){
    int i = event->x() / 25;
    int j = event->y() / 25 - 2;
    addToObstical(i, j);
    emit labelClick();
}

void SnakeLabel::addToObstical(int i, int j){
    ob.addObstical(i, j);
}
