#include "Obstacle.h"

Obstacle::Obstacle()
{

}

Obstacle::~Obstacle()
{

}

void Obstacle::updateObstacle()
{

    setDest(getDX() + velocity_x, getDY());
    setDest(getDX() , getDY() + velocity_y);

    if(getDX() <= boundary_l || getDX() >= boundary_r){
        velocity_x = -velocity_x;
    }

    if(getDY() <= boundary_u || getDY() >= boundary_d){
        velocity_y = -velocity_y;
    }


}
