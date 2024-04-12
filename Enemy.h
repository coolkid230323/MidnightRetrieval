#ifndef ENEMY_H
#define ENEMY_H

#include <bits/stdc++.h>

#include "Entity.h"
#include "Collision.h"


class Enemy : public Entity
{
public:
    Enemy();
    ~Enemy();

    void check(const Entity &player);
    void moveEnemy(const Entity &player, const vector<Entity> &maps);
    void updateEnemy(const Entity &player, const vector<Entity> &maps, SDL_Renderer* ren);
    Object getBullet() const {return bullets[0];};
    void setCanShoot(const bool &b) {canShoot = b;};
    void shoot(const Entity &player, const vector<Entity> &maps, SDL_Renderer* ren);
    bool checkShoot() const
    {
        if(canShoot && bulletCanMove && !isEmpty()){
            return true;
        }

        return false;
    }
    void setDestForBullet(const int &x, const int &y);
    bool isEmpty() const
    {
        return bullets.size() == 0;
    }
    bool getCollisionWithPlayer() const
    {
        return checkCollisionWithPlayer;
    }
    void setCollisionWithPlayer(const bool &b)
    {
        checkCollisionWithPlayer = b;
    }

private:
    bool canFind;
    bool isMoving;
    bool canShoot;
    bool bulletCanMove;
    bool checkCollisionWithPlayer;
    Object bullet;
    vector<Object> bullets;
    int dxB, dyB;

};


#endif
