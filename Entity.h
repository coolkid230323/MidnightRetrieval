#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "Object.h"

class Entity : public Object
{
public:
    Entity();
    int createCycle(const int &r, const int &w, const int &h, const int &amount, const int &speed);
    void setCurAnimation(const int &c) {begin = 0; curAnim = c;}
    int getCurAnimation() const {return curAnim;}
    void updateAnimation();
    //void reverse(bool r) {rev = r;}
    //void reverse(bool r, int nA) {rev = r; nAb = 1; nA = newAnim;}
private:
    struct cycle {
        int row;
        int w;
        int h;
        int amount;
        int speed;
        int tick;
    };
    vector<cycle> animations;
    int curAnim;
    int begin;
    //bool rev, nAb;
    //int newAnim;
};


#endif // ENTITY_H
