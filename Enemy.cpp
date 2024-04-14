#include "Enemy.h"

Enemy::Enemy()
{
    canFind = false;
    isMoving = false;
    canShoot = false;
    bulletCanMove = false;
    checkCollisionWithPlayer = false;
    dxB = 0;
    dyB = 0;
}

Enemy::~Enemy()
{

}

void Enemy::check(const Entity &player)
{
    int dis = sqrt((getDX() - player.getDX())*(getDX() - player.getDX()) + (getDY() - player.getDY())*(getDY() - player.getDY()));
    if(dis <= 300){
        canFind = true;
    }
    else{
        canFind = false;
    }

    if(!canShoot || !bulletCanMove){
        int disX = abs(player.getDX() - getDX());
        int disY = abs(player.getDY() - getDY());

        if(disX == 0 || disY == 0 || disX == disY){
            bulletCanMove = true;
            if(disX == 0){
                dxB = 0;
            }
            else{
                dxB = (player.getDX() - getDX()) / disX * 4;
            }
            if(disY == 0){
                dyB = 0;
            }
            else{
                dyB = (player.getDY() - getDY()) / disY * 4;
            }
        }
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
    isMoving = true;
    Collision c;
    if(c.checkCollisionWithMap(*this, maps)){
        setDest(getDX() + dx*64, getDY() + dy*64);
        if(!(c.checkCollisionWithMap(*this, maps))){
            setDest(getDX() - dx*65, getDY() - dy*65);
            if(disX >= disY){
                setDest(getDX() + dx, getDY());
                isMoving = true;
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX() - dx, getDY() + dy);
                    isMoving = true;
                    if(c.checkCollisionWithMap(*this, maps)){
                        setDest(getDX(), getDY() - dy);
                        isMoving = false;
                    }
                }
            }
            else{
                setDest(getDX(), getDY() + dy);
                isMoving = true;
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX() + dx, getDY() - dy);
                    isMoving = true;
                    if(c.checkCollisionWithMap(*this, maps)){
                        setDest(getDX() - dx, getDY());
                        isMoving = false;
                    }
                }
            }
        }
        else{
            setDest(getDX() - dx*65, getDY() - dy*65);
            isMoving = false;
            if(disX*dx > -32 && disX*dx < 64){
                setDest(getDX(), getDY() + dy);
                isMoving = true;
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX(), getDY() - dy);
                    isMoving = false;
                }
            }
            if(disY*dy > -32 && disY*dy < 64){
                setDest(getDX() + dx, getDY());
                isMoving = true;
                if(c.checkCollisionWithMap(*this, maps)){
                    setDest(getDX() - dx, getDY());
                    isMoving = false;
                }
            }
        }
    }
}

void Enemy::updateEnemy(const Entity &player, const vector<Entity> &maps, SDL_Renderer* ren)
{
    check(player);

    if(canFind){
        moveEnemy(player, maps);
    }
    if(canShoot && bulletCanMove){
        shoot(player, maps, ren);
    }
}

void Enemy::shoot(const Entity &player, const vector<Entity> &maps, SDL_Renderer* ren)
{
    if(bullets.size() == 0){
        bullet.setImage("Assets/enemy_bullet.png", ren);
        bullet.setSource(0, 0, 20, 20);
        bullet.setDest(getDX() + 24, getDY() + 24, 16, 16);

        bullets.push_back(bullet);
    }
    if(bulletCanMove){
        bullets[0].setDest(bullets[0].getDX() + dxB, bullets[0].getDY() + dyB);

        Collision c;
        if(c.checkCollisionWithMap(bullets[0], maps) || !isMoving){
            bulletCanMove = false;
            bullets.pop_back();
        }
        else if(c.collision(bullets[0], player)){
            bulletCanMove = false;
            bullets.pop_back();
            setCollisionWithPlayer(true);
        }
    }
}

void Enemy::setDestForBullet(const int &x, const int &y)
{
    if(checkShoot()){
        bullets[0].setDest(bullets[0].getDX() + x, bullets[0].getDY() + y);
    }
}















