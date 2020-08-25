#include "snakedata.h"

snakeData::snakeData()
{
    data.push_back(Position(0, 0));
    data.push_back(Position(0, 1));
    setDirection(3);
}

void snakeData::setDirection(int i){
    direction = i;
}

int snakeData::getDirection(){
    return direction;
}

