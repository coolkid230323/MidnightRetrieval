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
    bool collision(const Object &a, const Object &b);
    bool checkCollisionWithMap(const Object &a, const vector<Entity> &maps);

private:

};

#endif // COLLISION_H
