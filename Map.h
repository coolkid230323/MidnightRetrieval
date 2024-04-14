#ifndef MAP_H
#define MAP_H

#include <bits/stdc++.h>

#include "Object.h"
#include "Obstacle.h"
#include "Grid.h"
#include "Entity.h"
#include "Bullet.h"
#include "Enemy.h"

 //srand(time(NULL));

class Map
{
public:
    Map();
    virtual ~Map();

    //void draw(Object o);
    void loadMap(const char* filename,
                vector<Entity> &maps, vector<Obstacle> &traps, vector<Bullet> &bullets, vector<Entity> &coins,
                vector<Enemy> &enemies, vector<Object> &pedestals, vector<Entity> &mushrooms,
                SDL_Renderer *ren, int TILE_SIZE);
    void clearMap(vector<Entity> &maps, vector<Obstacle> &traps, vector<Bullet> &bullets, vector<Entity> &coins,
                vector<Enemy> &enemies, vector<Object> &pedestals, vector<Entity> &mushrooms);

    int getRandom() const
    {
         //srand(time(NULL));
         return rand() % 3;
    }

private:
    //vector<Object> map;
    int mapX, mapY;
};

#endif // MAP_H
