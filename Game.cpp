#include "Game.h"

Game::Game() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) cout << "Failed at SDL_Init()" << SDL_GetError() << endl;
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren) < 0) cout << "Failed at SDL_CreateWindowAndRenderer()" << SDL_GetError() << endl;
    SDL_SetWindowTitle(win, "Midnight Retrieval");
    m_Map.loadMap("Assets/1.level", maps, traps, ren, TILE_SIZE);
    TTF_Init();
    running = true;
    count = 0;
    //font = TTF_OpenFont("Asset/font.ttf", 24);
    //mapX = mapY = 0;
    j = 0;
    player.setDest(WIDTH/2, HEIGHT/2, 64, 64);
    player.setImage("Assets/player.png", ren);
    player.setSource(0, 0, 24, 32);
    idoll = player.createCycle(2, 24, 32, 2, 20);
    idolr = player.createCycle(1, 24, 32, 2, 20);
    runl = player.createCycle(4, 24, 32, 4, 4);
    runr = player.createCycle(3, 24, 32, 4, 4);
    player.setCurAnimation(idolr);
    loop();
}

Game::~Game() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::loop() {
    static int lastTime = 0;
    while(running) {

        lastFrame = SDL_GetTicks();
        if(lastFrame >= (lastTime+1000)) {
          lastTime = lastFrame;
          frameCount = 0;
        }

        //render();
        input();
        update();
        render();
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(ren, 100, 55, 50, 255);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    SDL_RenderFillRect(ren, &rect);

    drawMap();
    draw(player);

    frameCount++;
    int timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS < (defaultFPS)) {
    SDL_Delay((defaultFPS) - timerFPS);
    }

    SDL_RenderPresent(ren);
}


void Game::draw(Object o) {
    SDL_Rect dest = o.getDest();
    SDL_Rect src = o.getSource();
    //SDL_RenderCopyEx(ren, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopy(ren, o.getTex(), &src, &dest);
}

void Game::draw(const char* msg, int x, int y, int r, int g, int b) {
    SDL_Surface* surf;
    SDL_Texture* tex;
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;
    SDL_Rect rect;
    surf = TTF_RenderText_Solid(font, msg, color);
    tex = SDL_CreateTextureFromSurface(ren, surf);
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;
    SDL_FreeSurface(surf);
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

void Game::input() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {running = false; cout << "Quitting" << endl;}
        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
            if(e.key.keysym.sym == SDLK_LEFT) {
                l = 1;
                r = 0;
                //cout << "left" << endl;
            }
            if(e.key.keysym.sym == SDLK_RIGHT) {
                r = 1;
                l = 0;
                //cout << "right" << endl;
            }
            if(e.key.keysym.sym == SDLK_UP) {
                u = 1;
                d = 0;
                //cout << "up" << endl;
            }
            if(e.key.keysym.sym == SDLK_DOWN) {
                d = 1;
                u = 0;
                //cout << "down" << endl;
            }

        }
        if(e.type == SDL_KEYUP) {
            if(e.key.keysym.sym == SDLK_LEFT) {l = 0; player.setCurAnimation(idoll);}
            if(e.key.keysym.sym == SDLK_RIGHT) {r = 0; player.setCurAnimation(idolr);}
            if(e.key.keysym.sym == SDLK_UP) {
                u = 0;
                if(player.getCurAnimation() == runl){player.setCurAnimation(idoll);}
                else{player.setCurAnimation(idolr);}
            }
            if(e.key.keysym.sym == SDLK_DOWN) {
                d = 0;
                if(player.getCurAnimation() == runl){player.setCurAnimation(idoll);}
                else{player.setCurAnimation(idolr);}
            }

        }

        SDL_GetMouseState(&mousex, &mousey);
    }


    //const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

}

void Game::update() {

    for(size_t i = 0; i < traps.size(); i++){
        traps[i].updateObstacle();
        traps[i].updateAnimation();
    }

    if(l) {if(player.getCurAnimation() != runl) {player.setCurAnimation(runl);} player.setDest(player.getDX() - VELOC, player.getDY());}
    if(r) {if(player.getCurAnimation() != runr) {player.setCurAnimation(runr);} player.setDest(player.getDX() + VELOC, player.getDY());}
    if(u) {
        if(player.getCurAnimation() == idoll) {
            player.setCurAnimation(runl);
        }
        if(player.getCurAnimation() == idolr) {
            player.setCurAnimation(runr);
        }
        player.setDest(player.getDX(), player.getDY() - VELOC);
    }
    if(d) {
        if(player.getCurAnimation() == idoll) {
            player.setCurAnimation(runl);
        }
        if(player.getCurAnimation() == idolr) {
            player.setCurAnimation(runr);
        }
        player.setDest(player.getDX(), player.getDY() + VELOC);
    }

    player.updateAnimation();

    /*for(size_t i = 0; i < traps.size(); i++) {
        Collision c;
        if(c.collision(player, traps[i])) {
            traps[i].setImage("Assets/wall.png", ren);
            traps[i].setVelocity(0, 0);
        }
    }*/

    for(size_t i = 0; i < maps.size(); i++) {
        Collision c;
        if(c.collision(player, maps[i]) && maps[i].getId() == 03) {
            maps[i].setImage("Assets/wall.png", ren);

            for(size_t j = 0; j < maps.size(); j++){
                if(maps[j].getId() == 02){
                    maps[j].setImage("Assets/opengrid00.png", ren);
                    maps[j].setSolid(0);
                }
            }
        }
        if(c.collision(player, maps[i]) && maps[i].getSolid()) {

            if(l) {if(player.getCurAnimation() != runl) {player.setCurAnimation(runl);} player.setDest(player.getDX() + VELOC, player.getDY());}
            if(r) {if(player.getCurAnimation() != runr) {player.setCurAnimation(runr);} player.setDest(player.getDX() - VELOC, player.getDY());}
            if(u) {player.setDest(player.getDX(), player.getDY() + VELOC);}
            if(d) {player.setDest(player.getDX(), player.getDY() - VELOC);}

        }
    }

    if(player.getDX() < 550) {player.setDest(550, player.getDY()); scroll(VELOC, 0);}
    if(player.getDX() > WIDTH-550) {player.setDest(WIDTH-550, player.getDY()); scroll(-VELOC, 0);}
    if(player.getDY() < 330) {player.setDest(player.getDX(), 330); scroll(0, VELOC);}
    if(player.getDY() > HEIGHT-330) {player.setDest(player.getDX(), HEIGHT-330); scroll(0, -VELOC);}
}

void Game::scroll(int x, int y) {
    for(size_t i = 0; i < maps.size(); i++) {
        maps[i].setDest(maps[i].getDX()+x, maps[i].getDY()+y);
    }
    for(size_t i = 0; i < traps.size(); i++) {
        traps[i].setDest(traps[i].getDX()+x, traps[i].getDY()+y);
        traps[i].setBoundl(traps[i].getBoundl() + x);
        traps[i].setBoundr(traps[i].getBoundr() + x);
        traps[i].setBoundu(traps[i].getBoundu() + y);
        traps[i].setBoundd(traps[i].getBoundd() + y);
    }
}

void Game::drawMap() {
    for(size_t i = 0; i < maps.size(); i++) {
        /*if(map[i].getDX() >= mapX-TILE_SIZE
        & map[i].getDY() >= mapY-TILE_SIZE
        & map[i].getDX() <= mapX+WIDTH+TILE_SIZE
        & map[i].getDY() <= mapY+HEIGHT+TILE_SIZE) */
            draw(maps[i]);
    }

    for(size_t i = 0; i < traps.size(); i++){
        draw(traps[i]);
    }
}










