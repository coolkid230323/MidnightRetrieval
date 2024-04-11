#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"

#include <bits/stdc++.h>

class Obstacle : public Entity
{
public:
    Obstacle();
    virtual ~Obstacle();

    void updateObstacle();

    void setBoundl(const int &b) {boundary_l = b;}
    void setBoundr(const int &b) {boundary_r = b;}
    void setBoundu(const int &b) {boundary_u = b;}
    void setBoundd(const int &b) {boundary_d = b;}
    void setVelocity(const int &x, const int &y) {velocity_x = x; velocity_y = y;}

    int getVelocity_x() const {return velocity_x;}
    int getVelocity_y() const {return velocity_y;}
    int getBoundl() const {return boundary_l;}
    int getBoundr() const {return boundary_r;}
    int getBoundu() const {return boundary_u;}
    int getBoundd() const {return boundary_d;}

private:
    int boundary_l = 0;
    int boundary_r = 0;
    int boundary_u = 0;
    int boundary_d = 0;

    int velocity_x = 0;
    int velocity_y = 0;
};


#endif // OBSTACLE_H
