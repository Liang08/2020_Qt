#include "snakedata.h"

snakeData::snakeData(int x_1, int y_1, int x_2, int y_2)
{
    data.push_back(Position(x_1, y_1));
    data.push_back(Position(x_2, y_2));
}

