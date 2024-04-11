#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet:: ~Bullet()
{

}

void Bullet::loadBullet(vector<Bullet> &bullets, const int &dir)
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

void Bullet::setStartPos(const int &x, const int &y)
{
    startPosX = x;
    startPosY = y;
}

void Bullet::updateBullet(const vector<Entity> &maps, const Entity &player)
{
    Collision c;
    if(c.checkCollisionWithMap(*this, maps) || c.collision(*this, player)){
        this->setDest(startPosX, startPosY);
    }

    setDest(getDX() + velocity_x, getDY());
    setDest(getDX() , getDY() + velocity_y);
}
