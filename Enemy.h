#ifndef ENEMY_H
#define ENEMY_H

#include <bits/stdc++.h>

#include "Map.h"


class Enemy : public Entity
{
public:
    Enemy();
    ~Enemy();

    void check(const Entity &player);
    void moveEnemy(const Entity &player, const vector<Entity> &maps);
    void updateEnemy(const Entity &player, const vector<Entity> &maps);

private:
    bool canFind;

};


#endif
