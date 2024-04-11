#include "Enemy.h"

Enemy::Enemy()
{
    canFind = false;
}

Enemy::~Enemy()
{

}

void Enemy::check(const Entity &player)
{
    int dis = sqrt((getDX() - player.getDX())*(getDX() - player.getDX()) + (getDY() - player.getDY())*(getDY() - player.getDY()));
    if(dis <= 500){
        canFind = true;
    }
    else{
        canFind = false;
    }
}

void Enemy::moveEnemy(const Entity &player, const vector<Entity> &maps)
{
    int disX = abs(player.getDX() - getDX());
    int disY = abs(player.getDY() - getDY());

    int dx, dy;
    if(disX == 0){
        dx = 0;
    }
    else{
        dx = (player.getDX() - getDX()) / disX;
    }
    if(disY == 0){
        dy = 0;
    }
    else{
        dy = (player.getDY() - getDY()) / disY;
    }


    setDest(getDX() + dx, getDY() + dy);
    Collision c;
    if(c.checkCollisionWithMap(*this, maps)){
        setDest(getDX() + dx*39, getDY() + dy*39);
        if(!(c.checkCollisionWithMap(*this, maps))){
            setDest(getDX() - dx*40, getDY() - dy*40);
            if(disX >= disY){
                setDest(getDX() + dx, getDY());
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX() - dx, getDY() + dy);
                    if(c.checkCollisionWithMap(*this, maps)){
                        setDest(getDX(), getDY() - dy);
                    }
                }
            }
            else{
                setDest(getDX(), getDY() + dy);
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX() + dx, getDY() - dy);
                    if(c.checkCollisionWithMap(*this, maps)){
                        setDest(getDX() - dx, getDY());
                    }
                }
            }
        }
        else{
            setDest(getDX() - dx*40, getDY() - dy*40);
            if(disX < 32){
                setDest(getDX(), getDY() + dy);
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX(), getDY() - dy);
                }
            }
            if(disY < 32){
                setDest(getDX() + dx, getDY());
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX() - dx, getDY());
                }
            }
        }
    }

    /*if(disX >= disY){
        setDest(getDX() + dx, getDY());
        Collision c;

        if(c.checkCollisionWithMap(*this, maps)){
            setDest(getDX(), getDY() + dy);
            if(c.checkCollisionWithMap(*this, maps)){
                setDest(getDX() - dx, getDY());
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX(), getDY() - dy);
                }
            }
        }
    }
    else{
        setDest(getDX(), getDY() + dy);
        Collision c;

        if(c.checkCollisionWithMap(*this, maps)){
            setDest(getDX() + dx, getDY());
            if(c.checkCollisionWithMap(*this, maps)){
                setDest(getDX(), getDY() - dy);
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX() - dx, getDY());
                }
            }
        }
    }*/
}

void Enemy::updateEnemy(const Entity &player, const vector<Entity> &maps)
{
    check(player);

    if(canFind){
        moveEnemy(player, maps);
    }
}















