#ifndef BULLET_H
#define BULLET_H

#include <bits/stdc++.h>

#include "Entity.h"
#include "Collision.h"
#include "Object.h"

class Bullet : public Object
{
public:
    Bullet();
    ~Bullet();

    void setVelocity(int x, int y) {velocity_x = x; velocity_y = y;}
    void loadBullet(vector<Bullet> &bullets, int dir);
    void setStartPos(int x, int y);
    void updateBullet(vector<Entity> maps);

    int getStartPosX() const {return startPosX;}
    int getStartPosY() const {return startPosY;}
    int getVelocity_x() const {return velocity_x;}
    int getVelocity_y() const {return velocity_y;}

private:
    int startPosX;
    int startPosY;
    int velocity_x = 0;
    int velocity_y = 0;
};

#endif // BULLET_H
