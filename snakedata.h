#ifndef SNAKEDATA_H
#define SNAKEDATA_H
#include <vector>

struct Position{
    int x, y;
    Position(int a, int b):x(a), y(b){}
};

class snakeData
{
    int direction;
public:
    std::vector<Position> data;
    auto begin(){
        return data.begin();
    }
    auto end(){
        return data.end();
    }
    snakeData();
    void setDirection(int i);
    int getDirection();
    void snakeInit();

};


#endif // SNAKEDATA_H
