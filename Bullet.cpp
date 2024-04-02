#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet:: ~Bullet()
{

}

void Bullet::loadBullet(vector<Bullet> &bullets, int dir)
{
    if(dir == 4 || dir == 8){
        this->setVelocity(2, 0);
        bullets.push_back(*this);

        this->setVelocity(-2, 0);
        bullets.push_back(*this);

        this->setVelocity(0, 2);
        bullets.push_back(*this);

        this->setVelocity(0, -2);
        bullets.push_back(*this);
    }
    if(dir == 8){
        this->setVelocity(2, 2);
        bullets.push_back(*this);

        this->setVelocity(-2, -2);
        bullets.push_back(*this);

        this->setVelocity(-2, 2);
        bullets.push_back(*this);

        this->setVelocity(2, -2);
        bullets.push_back(*this);
    }
}

void Bullet::setStartPos(int x, int y)
{
    startPosX = x;
    startPosY = y;
}

void Bullet::updateBullet(vector<Entity> maps)
{
    Collision c;
    if(c.checkCollisionWithMap(*this, maps)){
        this->setDest(startPosX, startPosY);
    }

    setDest(getDX() + velocity_x, getDY());
    setDest(getDX() , getDY() + velocity_y);
}
