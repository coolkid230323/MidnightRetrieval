#include "Entity.h"

Entity::Entity()
{

}

int Entity::createCycle(const int &r, const int &w, const int &h, const int &amount, const int &speed) {
    cycle tmp;
    tmp.row = r - 1;
    tmp.w = w;
    tmp.h = h;
    tmp.amount = amount;
    tmp.speed = speed;
    tmp.tick = 0;
    animations.push_back(tmp);
    return animations.size() - 1;
}

void Entity::updateAnimation() {
    if(!animations.empty()) {
        setSource(animations[curAnim].w * animations[curAnim].tick, animations[curAnim].row * animations[curAnim].h, animations[curAnim].w, animations[curAnim].h);
        if(begin > animations[curAnim].speed){
            animations[curAnim].tick++;
            begin = 0;
        }
        begin++;
        if(animations[curAnim].tick >= animations[curAnim].amount) {animations[curAnim].tick = 0;}
        if(animations[curAnim].tick <= 0 ) {
            animations[curAnim].tick = 0;
        }
    }
}











