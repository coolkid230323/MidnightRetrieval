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
#include "Enemy.h"

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
    void showMenu();
    void showGameOver();
    void showOptions();
    void showWinGame();
    void update();
    void input();
    void render();
    static const char* intToString(const int &num);
    void draw(Object o);
    void draw(const char* msg, const int &x, const int &y, const int &r, const int &g, const int &b, TTF_Font* font);
    void drawMap();
    void scroll(const int &x, const int &y);
    SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
    void CrossfadeTexture(SDL_Renderer* renderer, SDL_Texture* texture, const int &duration);

private:
    SDL_Renderer* ren = nullptr;
    SDL_Window* win = nullptr;
    SDL_Texture* background = nullptr;
    TTF_Font* font1 = nullptr;
    TTF_Font* font2 = nullptr;
    TTF_Font* font3 = nullptr;

    bool running;
    bool showingMenu;
    bool playing;
    bool clickingOptions;
    bool victory;
    bool defeat;
    bool collisionWithEnemy;

    int counts;
    int lifeBar;
    int frameCount, timerFPS, lastFrame;
    int mousex, mousey;
    int level;

    const char* levels[10];

    Entity player;
    Object *countCoin = nullptr;
    Object *countLives = nullptr;
    Map m_Map;

    Object *menuButton = nullptr;
    Object *optionButton = nullptr;
    Object *quitButton = nullptr;
    Object *resumeButton = nullptr;
    Object *playButton = nullptr;
    Object *continueButton = nullptr;

    Object *victoryLogo = nullptr;
    Object *gameOverLogo = nullptr;
    Object *scoreBackground = nullptr;

    Object *menuBackGround = nullptr;

    vector<Entity> maps;
    vector<Obstacle> traps;
    vector<Object> grids;
    vector<Bullet> bullets;
    vector<Entity> coins;
    vector<Enemy> enemies;
    vector<Object> pedestals;
    vector<Entity> mushrooms;

    Audio mainMusic;
    Audio pickCoin;
    Audio bulletSound;
    Audio pickMushRoom;
    Audio mouseClick;

    int mapX, mapY;
    int veloc;
    bool l, r, u, d, rose, blue, yellow, white;
    int idoll, idolr, runl, runr, stand, injured;
};


#endif // GAME_H
