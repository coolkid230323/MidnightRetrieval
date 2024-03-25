#ifndef MAP_H
#define MAP_H

#include <bits/stdc++.h>

#include "Object.h"
#include "Obstacle.h"
#include "Grid.h"
#include "Entity.h"

class Map
{
public:
    Map();
    virtual ~Map();

    //void draw(Object o);
    void loadMap(const char* filename, vector<Entity> &maps, vector<Obstacle> &traps, SDL_Renderer *ren, int TILE_SIZE);
    //void drawMap();
    //void scroll(int x, int y);

private:
    //vector<Object> map;
    int mapX, mapY;
};

#endif // MAP_H
