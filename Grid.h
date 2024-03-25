#ifndef GRID_H
#define GRID_H

#include "Object.h"


class Grid
{
public:
    Grid();
    virtual ~Grid();

private:
    vector<Object> grids;
};

#endif // GRID_H
