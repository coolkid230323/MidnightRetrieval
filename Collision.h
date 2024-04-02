#ifndef COLLISION_H
#define COLLISION_H

#include <bits/stdc++.h>

#include "Object.h"
#include "Entity.h"

class Collision
{
public:
    Collision();
    virtual ~Collision();
    bool collision(Object a, Object b);
    bool checkCollisionWithMap( Object a, vector<Entity> maps);

private:

};

#endif // COLLISION_H
