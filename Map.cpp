#include "Map.h"

Map::Map()
{
    mapX = mapY = 0;
}

Map::~Map()
{

}

/*void Map::draw(Object o)
{
    SDL_Rect dest = o.getDest();
    SDL_Rect src = o.getSource();
    SDL_RenderCopyEx(ren, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}*/

void Map::loadMap(const char* filename, vector<Entity> &maps, vector<Obstacle> &traps, SDL_Renderer *ren, int TILE_SIZE) {
    Entity tmp;
    Obstacle trap;
    int current, mx, my, mw, mh;
    ifstream in(filename);
    if(!in.is_open()) {
    cout << "Failed to open map file." << endl;
    return;
    }
    in >> mw;
    in >> mh;
    in >> mx;
    in >> my;
    for(int i = 0; i < mh; i++) {
        for(int j = 0; j < mw; j++) {
            if(in.eof()) {
            cout << "Reached end of map file too soon." << endl;
            return;
            }
            in >> current;

            switch(current)
            {
            /*case 0:
                tmp.setImage("Assets/floor01.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 128, 128);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;*/
            case 1:
                tmp.setImage("Assets/wall01.png", ren);
                tmp.setSolid(1);
                tmp.setSource(0, 0, 128, 128);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 5:
                tmp.setImage("Assets/trap00.png", ren);
                tmp.setSolid(1);
                tmp.setSource(0, 0, 128, 128);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 2:
                tmp.setImage("Assets/grid02.png", ren);
                tmp.setSolid(1);
                tmp.setSource(0, 0, 128, 128);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);


                maps.push_back(tmp);
                break;
            case 3:
                tmp.setImage("Assets/key01.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 128, 128);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 35:
                trap.setImage("Assets/Trap01.png", ren);
                trap.setSolid(0);
                trap.setSource(0, 0, 128, 128);
                trap.setCurAnimation(trap.createCycle(1, 32, 32, 8, 1));
                trap.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                trap.setId(current);
                trap.setVelocity(6, 0);
                trap.setBoundl(trap.getDX() - 200);
                trap.setBoundr(trap.getDX() + 200);
                trap.setBoundu(trap.getDY() - 200);
                trap.setBoundd(trap.getDY() + 200);

                traps.push_back(trap);
                break;
            default:
                break;


            }

        }
    }
    in.close();
}

/*void Map::scroll(int x, int y) {
    for(auto i = 0; i < map.size(); i++) {
        map[i].setDest(map[i].getDX()+x, map[i].getDY()+y);
    }
}*/

/*void Map::drawMap() {
    for(auto i = 0; i < map.size(); i++) {
        if(map[i].getDX() >= mapX-TILE_SIZE
        & map[i].getDY() >= mapY-TILE_SIZE
        & map[i].getDX() <= mapX+WIDTH+TILE_SIZE
        & map[i].getDY() <= mapY+HEIGHT+TILE_SIZE) {
          draw(map[i]);
        }
    }
*/
