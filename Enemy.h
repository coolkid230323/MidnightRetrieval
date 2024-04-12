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
        if(canShoot && bulletCanMove && bullets.size() != 0){
            return true;
        }

        return false;
    }
    void setDestForBullet(const int &x, const int &y);

private:
    bool canFind;
    bool isMoving;
    bool canShoot;
    bool bulletCanMove;
    Object bullet;
    vector<Object> bullets;
    int dxB, dyB;

};


#endif
