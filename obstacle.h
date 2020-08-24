#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <vector>

class Obstacle
{
public:
    int obs[40][40];
    Obstacle();
    void addObstacle(int i, int j);
};

#endif // OBSTACLE_H
