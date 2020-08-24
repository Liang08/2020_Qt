#ifndef SNAKEDATA_H
#define SNAKEDATA_H
#include <vector>

struct Position{
    int x, y;
    Position(int a, int b):x(a), y(b){}
};

class snakeData
{
    std::vector<Position> data;
    int direction;
public:
    snakeData();

};

#endif // SNAKEDATA_H
