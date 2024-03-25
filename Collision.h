#ifndef COLLISION_H
#define COLLISION_H

#include "Object.h"
#include "Entity.h"

class Collision
{
public:
    Collision();
    virtual ~Collision();
    bool collision(Object a, Object b);

private:

};

#endif // COLLISION_H
