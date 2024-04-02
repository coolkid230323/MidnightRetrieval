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
#include "Bullet.h"
#include "Audio.h"

#define WIDTH 1280
#define HEIGHT 720
#define defaultFPS 1000/60
#define TILE_SIZE 32
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
    void drawMap();
    void scroll(int x, int y);
    SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
    void CrossfadeTexture(SDL_Renderer* renderer, SDL_Texture* texture, int duration);

private:
    SDL_Renderer* ren;
    SDL_Window* win;
    SDL_Texture* background;
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
    vector<Bullet> bullets;
    vector<Entity> coins;

    Audio mainMusic;

    int mapX, mapY;
    int veloc;
    bool l, r, u, d, rose, blue, yellow, white;
    int idoll, idolr, runl, runr, stand, injured;
};


#endif // GAME_H
