#ifndef GAME_H
#define GAME_H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Object.h"
#include "Entity.h"
#include "Collision.h"
#include "Map.h"
#include "Obstacle.h"
#include "Grid.h"

#define WIDTH 1280
#define HEIGHT 720
#define defaultFPS 1000/60
#define TILE_SIZE 64
#define VELOC 6


class Game {
public:
    Game();
    ~Game();
    void loop();
    void update();
    void input();
    void render();
    void draw(Object o);
    void draw(const char* msg, int x, int y, int r, int g, int b);
    //void loadMap(const char* filename);
    void drawMap();
    void scroll(int x, int y);

private:
    SDL_Renderer* ren;
    SDL_Window* win;
    TTF_Font *font;
    bool running;
    int count;
    int frameCount, timerFPS, lastFrame;
    int mousex, mousey;
    Entity player;
    Map m_Map;
    vector<Entity> maps;
    vector<Obstacle> traps;
    vector<Object> grids;
    int mapX, mapY;
    int veloc;
    bool l, r, u, d, j;
    int idoll, idolr, runl, runr;
};


#endif // GAME_H
