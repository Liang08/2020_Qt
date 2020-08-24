#include "obstacle.h"
#include <memory.h>

Obstacle::Obstacle()
{
    memset(obs, 0, sizeof (obs));
}

void Obstacle::addObstical(int i, int j){
    obs[i][j] = 1 - obs[i][j];
}
