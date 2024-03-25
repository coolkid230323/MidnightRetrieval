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
