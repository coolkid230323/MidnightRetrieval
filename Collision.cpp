#include "Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::collision(Object a, Object b) {
    if((a.getDX() < (b.getDX()+b.getDW())) && ((a.getDX() + a.getDW()) > b.getDX())
    && (a.getDY() < (b.getDY() + b.getDH())) && ((a.getDY() + a.getDH()) > b.getDY())) {
        return true;
    }
    else {
        return false;
    }
}

bool Collision::checkCollisionWithMap(Object a, vector<Entity> maps)
{
    for(size_t i = 0; i < maps.size(); i++){
        if(collision(a, maps[i]) && maps[i].getSolid()) return true;
    }

    return false;
}
