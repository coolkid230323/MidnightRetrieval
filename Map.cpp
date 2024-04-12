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

void Map::loadMap(const char* filename,
                  vector<Entity> &maps, vector<Obstacle> &traps, vector<Bullet> &bullets, vector<Entity> &coins,
                  vector<Enemy> &enemies, vector<Object> &pedestals, vector<Entity> &mushrooms,
                  SDL_Renderer *ren, int TILE_SIZE) {
    Entity tmp;
    Obstacle trap;
    Bullet bullet;
    Enemy enemy;
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
            case 0:
                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 16, 16);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 1:
                tmp.setImage("Assets/wall03.png", ren);
                tmp.setSolid(1);
                tmp.setSource(0, 0, 50, 50);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 5:
                tmp.setImage("Assets/trapspike.png", ren);
                tmp.setSolid(1);
                tmp.setSource(0, 0, 128, 128);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 2:
                tmp.setImage("Assets/grid02.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 128, 128);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);


                maps.push_back(tmp);
                break;
            case 3:
                tmp.setImage("Assets/health.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 400, 400);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 35:
                trap.setImage("Assets/trap01.png", ren);
                trap.setSolid(0);
                trap.setSource(0, 0, 128, 128);
                trap.setCurAnimation(trap.createCycle(1, 32, 32, 8, 1));
                trap.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                trap.setId(current);
                trap.setVelocity(3, 0);
                trap.setBoundl(trap.getDX() - 32*3);
                trap.setBoundr(trap.getDX() + 32*3);
                trap.setBoundu(trap.getDY() - 32*3);
                trap.setBoundd(trap.getDY() + 32*3);

                traps.push_back(trap);

                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 16, 16);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 36:
                trap.setImage("Assets/trap01.png", ren);
                trap.setSolid(0);
                trap.setSource(0, 0, 128, 128);
                trap.setCurAnimation(trap.createCycle(1, 32, 32, 8, 1));
                trap.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                trap.setId(current);
                trap.setVelocity(0, 3);
                trap.setBoundl(trap.getDX() - 32*5);
                trap.setBoundr(trap.getDX() + 32*5);
                trap.setBoundu(trap.getDY() - 32*5);
                trap.setBoundd(trap.getDY() + 32*5);

                traps.push_back(trap);

                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 16, 16);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 37:
                trap.setImage("Assets/trap01.png", ren);
                trap.setSolid(0);
                trap.setSource(0, 0, 128, 128);
                trap.setCurAnimation(trap.createCycle(1, 32, 32, 8, 1));
                trap.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                trap.setId(current);
                trap.setVelocity(-3, 0);
                trap.setBoundl(trap.getDX() - 32*3);
                trap.setBoundr(trap.getDX() + 32*3);
                trap.setBoundu(trap.getDY() - 32*3);
                trap.setBoundd(trap.getDY() + 32*3);

                traps.push_back(trap);

                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 16, 16);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 34:
                trap.setImage("Assets/trap01.png", ren);
                trap.setSolid(0);
                trap.setSource(0, 0, 128, 128);
                trap.setCurAnimation(trap.createCycle(1, 32, 32, 8, 1));
                trap.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                trap.setId(current);
                trap.setVelocity(0, -3);
                trap.setBoundl(trap.getDX() - 32*5);
                trap.setBoundr(trap.getDX() + 32*5);
                trap.setBoundu(trap.getDY() - 32*5);
                trap.setBoundd(trap.getDY() + 32*5);

                traps.push_back(trap);

                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 16, 16);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 44:
                bullet.setImage("Assets/bullet.png", ren);
                bullet.setSolid(0);
                bullet.setSource(0, 0, 20, 20);
                bullet.setDest((j*TILE_SIZE)+mx+8, (i*TILE_SIZE)+my+8, TILE_SIZE/2, TILE_SIZE/2);
                bullet.setStartPos((j*TILE_SIZE)+mx+8, (i*TILE_SIZE)+my+8);
                bullet.loadBullet(bullets, 4);
                bullet.setId(current);

                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 32, 32);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);

                tmp.setImage("Assets/pedestal.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 32, 32);
                tmp.setDest((j*TILE_SIZE)+mx-16, (i*TILE_SIZE)+my-16, TILE_SIZE*2, TILE_SIZE*2);
                tmp.setId(current);

                pedestals.push_back(tmp);
                break;
            case 48:
                bullet.setImage("Assets/bullet.png", ren);
                bullet.setSolid(0);
                bullet.setSource(0, 0, 20, 20);
                bullet.setDest((j*TILE_SIZE)+mx+8, (i*TILE_SIZE)+my+8, TILE_SIZE/2, TILE_SIZE/2);
                bullet.setStartPos((j*TILE_SIZE)+mx+8, (i*TILE_SIZE)+my+8);
                bullet.loadBullet(bullets, 8);
                bullet.setId(current);

                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 32, 32);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);

                tmp.setImage("Assets/pedestal.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 32, 32);
                tmp.setDest((j*TILE_SIZE)+mx-16, (i*TILE_SIZE)+my-16, TILE_SIZE*2, TILE_SIZE*2);
                tmp.setId(current);

                pedestals.push_back(tmp);
                break;
            case 55:
                tmp.setImage("Assets/coin.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 48, 8);
                tmp.setCurAnimation(tmp.createCycle(1, 8, 8, 6, 6));
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                coins.push_back(tmp);

                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 32, 32);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 66:
                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 32, 32);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);

                enemy.setImage("Assets/enemy02.png", ren);
                enemy.setSource(0, 0, 576, 36);
                enemy.setCurAnimation(enemy.createCycle(1, 64, 36, 9, 10));
                enemy.setCanShoot(1);
                enemy.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE*2, TILE_SIZE*2);
                enemy.setId(current);

                enemies.push_back(enemy);
                break;
            case 88:
                tmp.setImage("Assets/mushroom.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 96, 13);
                tmp.setCurAnimation(tmp.createCycle(1, 16, 13, 6, 10));
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                mushrooms.push_back(tmp);

                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 32, 32);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);
                break;
            case 99:
                tmp.setImage("Assets/nen2.png", ren);
                tmp.setSolid(0);
                tmp.setSource(0, 0, 32, 32);
                tmp.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE, TILE_SIZE);
                tmp.setId(current);

                maps.push_back(tmp);

                enemy.setImage("Assets/enemy01.png", ren);
                enemy.setSource(0, 0, 128, 20);
                enemy.setCurAnimation(enemy.createCycle(1, 32, 20, 4, 10));
                enemy.setCanShoot(0);
                enemy.setDest((j*TILE_SIZE)+mx, (i*TILE_SIZE)+my, TILE_SIZE*2, TILE_SIZE*2);
                enemy.setId(current);

                enemies.push_back(enemy);
                break;
            default:
                break;
            }

        }
    }
    in.close();
}
