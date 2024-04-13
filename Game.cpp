#include "Game.h"

Game::Game() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) cout << "Failed at SDL_Init()" << SDL_GetError() << endl;
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren) < 0) cout << "Failed at SDL_CreateWindowAndRenderer()" << SDL_GetError() << endl;
    SDL_SetWindowTitle(win, "Midnight Retrieval");

    countCoin = new Object();
    countLives = new Object();
    menuBackGround = new Object();
    menuButton = new Object();
    optionButton = new Object();
    quitButton = new Object();
    continueButton = new Object();
    resumeButton = new Object();
    playButton = new Object();
    victoryLogo = new Object();
    gameOverLogo = new Object();


    background = LoadTexture("Assets/background.png", ren);
    CrossfadeTexture(ren, background, 1000);

    (*menuBackGround).setImage("Assets/menuBackGround.png", ren);
    (*menuBackGround).setDest(0, 0, WIDTH, HEIGHT);
    (*menuBackGround).setSource(0, 0, 1808, 1017);

    (*optionButton).setImage("Assets/optionbutton.png", ren);
    (*optionButton).setDest(1216, 0, 64, 64);
    (*optionButton).setSource(0, 0, 479, 479);

    mainMusic.load("Sounds/mainMusic.wav");
    mainMusic.play(-1);
    mainMusic.pause();
    pickCoin.load("Sounds/pickcoin.wav");
    bulletSound.load("Sounds/bulletSound.wav");

    m_Map.loadMap("Assets/1.level", maps, traps, bullets, coins, enemies, pedestals, mushrooms, ren, TILE_SIZE);

    TTF_Init();
    running = true;
    showingMenu = true;
    clickingOptions = false;
    playing = false;
    victory = false;
    defeat = false;
    counts = 0;
    lifeBar = 100;
    font1 = TTF_OpenFont("Fonts/GameName.ttf", 70);
    font2 = TTF_OpenFont("Fonts/GameName.ttf", 70);
    //mapX = mapY = 0;

    (*menuButton).setSource(0, 0, 706, 320);
    (*quitButton).setSource(0, 0, 706, 320);
    (*playButton).setSource(0, 0, 706, 320);
    (*resumeButton).setSource(0, 0, 706, 320);
    (*continueButton).setSource(0, 0, 706, 320);

    (*countCoin).setDest(0, 0, 64, 64);
    (*countCoin).setImage("Assets/coins.png", ren);
    (*countCoin).setSource(0, 0, 512, 512);

    (*countLives).setDest(930, 0, 64, 64);
    (*countLives).setImage("Assets/heart.png", ren);
    (*countLives).setSource(0, 0, 280, 235);

    player.setDest(WIDTH/2, HEIGHT/2, 32, 32);

    player.setImage("Assets/player0.png", ren);
    player.setSource(0, 0, 70, 70);
    stand = player.createCycle(1, 70, 70, 4, 10);
    runr = player.createCycle(2, 70, 70, 4, 4);
    runl = player.createCycle(3, 70, 70, 4, 4);
    injured = player.createCycle(4, 70, 70, 4, 10);
    player.setCurAnimation(stand);

    loop();
}

Game::~Game() {
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    SDL_DestroyTexture(background);
    delete menuButton;
    delete optionButton;
    delete quitButton;
    delete resumeButton;
    delete playButton;
    delete continueButton;
    delete victoryLogo;
    delete gameOverLogo;
    delete menuBackGround;
}

void Game::loop() {
    static int lastTime = 0;
    while(running) {

        lastFrame = SDL_GetTicks();
        if(lastFrame >= (lastTime+1000)) {
          lastTime = lastFrame;
          frameCount = 0;
        }

        if(showingMenu){
            mainMusic.pause();
            showMenu();
        }
        else{
            mainMusic.resume();
        }

        if(!showingMenu && playing && !defeat){
            input();
            update();
        }
        else if(clickingOptions){
            showOptions();
        }
        else if(defeat && !playing){
            showGameOver();
        }

        render();
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(ren,0, 0, 0, 255);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    SDL_RenderFillRect(ren, &rect);

    //draw(menuBackGround);
    if(showingMenu){
        draw(*menuBackGround);
        draw(*playButton);
        draw(*quitButton);
    }
    else if(!showingMenu && playing){
        drawMap();
        draw(player);


        SDL_SetRenderDrawColor(ren,95, 158, 160, 255);
        SDL_Rect nen;
        nen.x = 0;
        nen.y = 0;
        nen.w = WIDTH;
        nen.h = 64;
        SDL_RenderFillRect(ren, &nen);
        draw(*countCoin);
        draw(intToString(counts), 80, 0, 255, 255, 255, font1);
        draw(*countLives);
        draw(intToString(lifeBar), 1000, 0, 255, 255, 255, font2);

        draw(*optionButton);

    }
    else if(clickingOptions && !showingMenu && !playing && !defeat){
        drawMap();
        draw(player);

        draw(*menuButton);
        draw(*continueButton);
        draw(*quitButton);
    }
    else if(defeat){
        drawMap();
        draw(player);

        draw(*menuButton);
    }


    frameCount++;
    int timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS < (defaultFPS)) {
    SDL_Delay((defaultFPS) - timerFPS);
    }

    SDL_RenderPresent(ren);
}

const char* Game::intToString(const int &num) {
    std::stringstream ss;
    ss << num;
    std::string tempString = ss.str();

    char* charArray = new char[tempString.length() + 1];
    strcpy(charArray, tempString.c_str());
    return charArray;
}


void Game::draw(Object o) {
    SDL_Rect dest = o.getDest();
    SDL_Rect src = o.getSource();
    SDL_RenderCopy(ren, o.getTex(), &src, &dest);
}

void Game::draw(const char* msg, const int &x, const int &y, const int &r, const int &g, const int &b, TTF_Font* font) {
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

void Game::showMenu()
{
    SDL_Event e;
    (*playButton).setDest(150, 150, 320, 140);
    (*quitButton).setDest(150, 350, 320, 140);


    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) {running = false; cout << "Quitting" << endl;}
        Uint32 mouseState = SDL_GetMouseState(&mousex, &mousey);

        if(mousex >= (*playButton).getDX() && mousex <= (*playButton).getDX() + (*playButton).getDW()
           && mousey >= (*playButton).getDY() && mousey <= (*playButton).getDY() + (*playButton).getDH())
        {
            (*playButton).setImage("Assets/playbutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                playing = true;
                showingMenu = false;

                counts = 0;
                lifeBar = 100;
                //m_Map.clearMap(maps, traps, bullets, coins, enemies, pedestals, mushrooms);
                //m_Map.loadMap("Assets/1.level", maps, traps, bullets, coins, enemies, pedestals, mushrooms, ren, TILE_SIZE);
            }
        }
        else{
            (*playButton).setImage("Assets/playbutton01.png", ren);
        }

        if(mousex >= (*quitButton).getDX() && mousex <= (*quitButton).getDX() + (*quitButton).getDW()
           && mousey >= (*quitButton).getDY() && mousey <= (*quitButton).getDY() + (*quitButton).getDH())
        {
            (*quitButton).setImage("Assets/quitbutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                running = false;
            }
        }
        else{
            (*quitButton).setImage("Assets/quitbutton01.png", ren);
        }

    }


}

void Game::showGameOver()
{
    SDL_Event e;
    (*menuButton).setDest(480, 350, 320, 140);

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) {running = false; cout << "Quitting" << endl;}
        Uint32 mouseState = SDL_GetMouseState(&mousex, &mousey);

        if(mousex >= (*menuButton).getDX() && mousex <= (*menuButton).getDX() + (*menuButton).getDW()
           && mousey >= (*menuButton).getDY() && mousey <= (*menuButton).getDY() + (*menuButton).getDH())
        {
            (*menuButton).setImage("Assets/menubutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                playing = false;
                defeat = false;
                showingMenu = true;
                clickingOptions = false;
            }
        }
        else{
            (*menuButton).setImage("Assets/menubutton01.png", ren);
        }
    }

}

void Game::showOptions()
{
    SDL_Event e;
    (*continueButton).setDest(480, 150, 320, 140);
    (*menuButton).setDest(480, 350, 320, 140);
    (*quitButton).setDest(480, 550, 320, 140);

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) {running = false; cout << "Quitting" << endl;}
        Uint32 mouseState = SDL_GetMouseState(&mousex, &mousey);

        if(mousex >= (*continueButton).getDX() && mousex <= (*continueButton).getDX() + (*continueButton).getDW()
           && mousey >= (*continueButton).getDY() && mousey <= (*continueButton).getDY() + (*continueButton).getDH())
        {
            (*continueButton).setImage("Assets/continuebutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                playing = true;
                clickingOptions = false;
            }
        }
        else{
            (*continueButton).setImage("Assets/continuebutton01.png", ren);
        }

        if(mousex >= (*menuButton).getDX() && mousex <= (*menuButton).getDX() + (*menuButton).getDW()
           && mousey >= (*menuButton).getDY() && mousey <= (*menuButton).getDY() + (*menuButton).getDH())
        {
            (*menuButton).setImage("Assets/menubutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                playing = false;
                clickingOptions = false;
                showingMenu = true;
            }
        }
        else{
            (*menuButton).setImage("Assets/menubutton01.png", ren);
        }

        if(mousex >= (*quitButton).getDX() && mousex <= (*quitButton).getDX() + (*quitButton).getDW()
           && mousey >= (*quitButton).getDY() && mousey <= (*quitButton).getDY() + (*quitButton).getDH())
        {
            (*quitButton).setImage("Assets/quitbutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                running = false;
            }
        }
        else{
            (*quitButton).setImage("Assets/quitbutton01.png", ren);
        }

    }
}

void Game::showWinGame()
{

}

void Game::input() {
    SDL_Event e;


    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {running = false; cout << "Quitting" << endl;}
        Uint32 mouseState = SDL_GetMouseState(&mousex, &mousey);

        if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_ESCAPE) running=false;
            if(e.key.keysym.sym == SDLK_LEFT) {
                l = 1;
                r = 0;
            }
            if(e.key.keysym.sym == SDLK_RIGHT) {
                r = 1;
                l = 0;
            }
            if(e.key.keysym.sym == SDLK_UP) {
                u = 1;
                d = 0;
            }
            if(e.key.keysym.sym == SDLK_DOWN) {
                d = 1;
                u = 0;
            }
            if(e.key.keysym.sym == SDLK_j){
                blue = 1;
                white = 0;
                rose = 0;
            }
            if(e.key.keysym.sym == SDLK_i){
                rose = 1;
                white = 0;
                blue = 0;
            }
            if(e.key.keysym.sym == SDLK_l){
                yellow = 1;
                white = 0;
            }
            if(e.key.keysym.sym == SDLK_o){
                white = 1;
                blue = 0;
                rose = 0;
            }

        }
        if(e.type == SDL_KEYUP) {
            if(e.key.keysym.sym == SDLK_LEFT) {l = 0; player.setCurAnimation(stand);}
            if(e.key.keysym.sym == SDLK_RIGHT) {r = 0; player.setCurAnimation(stand);}
            if(e.key.keysym.sym == SDLK_UP) {
                u = 0;
                /*if(player.getCurAnimation() == runl){player.setCurAnimation(idoll);}
                else{player.setCurAnimation(idolr);}*/
                player.setCurAnimation(stand);
            }
            if(e.key.keysym.sym == SDLK_DOWN) {
                d = 0;
                /*if(player.getCurAnimation() == runl){player.setCurAnimation(idoll);}
                else{player.setCurAnimation(idolr);}*/
                player.setCurAnimation(stand);
            }
            if(e.key.keysym.sym == SDLK_j){
                blue = 0;
            }
            if(e.key.keysym.sym == SDLK_i){
                rose = 0;
            }
            if(e.key.keysym.sym == SDLK_l){
                yellow = 0;
            }
            /*if(e.key.keysym.sym == SDLK_o){
                white = 0;
            }*/

        }

        if(mousex >= (*optionButton).getDX() && mousex <= (*optionButton).getDX() + (*optionButton).getDW()
           && mousey >= (*optionButton).getDY() && mousey <= (*optionButton).getDY() + (*optionButton).getDH())
        {
            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                clickingOptions = true;
                playing = false;
            }
        }

    }


    //const Uint8 *keyState = SDL_GetKeyboardState(nullptr);

}

SDL_Texture* Game::LoadTexture(const char* fileName, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(fileName);
    if (!surface) {
        std::cerr << "Failed to load image: " << fileName << ". SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Game::CrossfadeTexture(SDL_Renderer* renderer, SDL_Texture* texture, const int &duration) {
    int steps = 100;
    for (int i = 0; i <= steps; ++i) {
        SDL_RenderClear(renderer);

        // Calculate the alpha for the texture
        int alpha = i * 255 / steps;

        // Set the alpha for the texture
        SDL_SetTextureAlphaMod(texture, alpha);

        // Render the texture
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, nullptr); // Fill with background color
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        // Present renderer
        SDL_RenderPresent(renderer);

        // Delay to control the speed of crossfade
        SDL_Delay(duration / steps);
    }
}



void Game::update() {
    cout << mousex << " " << mousey << endl;

    if(lifeBar <= 0){
        playing = false;
        defeat = true;
    }

    for(size_t i = 0; i < bullets.size(); i++){
        bullets[i].updateBullet(maps, player);
    }

    for(size_t i = 0; i < coins.size(); i++){
        coins[i].updateAnimation();
    }

    for(size_t i = 0; i < traps.size(); i++){
        traps[i].updateObstacle();
        traps[i].updateAnimation();
    }

    for(size_t i = 0; i < enemies.size(); i++){
        enemies[i].updateEnemy(player, maps, ren);
        enemies[i].updateAnimation();
    }

    for(size_t i = 0; i < mushrooms.size(); i++){
        mushrooms[i].updateAnimation();
    }

    if(l){
        if(player.getCurAnimation() != runl){
            player.setCurAnimation(runl);
            //player.setDest(player.getDX() - VELOC, player.getDY());
        }
        //player.setDest(player.getDX() - VELOC, player.getDY());
        scroll(VELOC, 0);
    }
    if(r){
        if(player.getCurAnimation() != runr){
            //player.setCurAnimation(runr);
            //player.setDest(player.getDX() + VELOC, player.getDY());}
        }
        //player.setDest(player.getDX() + VELOC, player.getDY());
        scroll(-VELOC, 0);
    }
    if(u) {
        //player.setDest(player.getDX(), player.getDY() - VELOC);
        scroll(0, VELOC);
    }
    if(d) {
        //player.setDest(player.getDX(), player.getDY() + VELOC);
        scroll(0, -VELOC);
    }
    if(white){
        player.setImage("Assets/player0.png", ren);
    }

    player.updateAnimation();



    for(size_t i = 0; i < maps.size(); i++) {
        Collision c;
        if(c.collision(player, maps[i]) && maps[i].getId() == 03) {
            maps.erase(maps.begin() + i);

            for(size_t j = 0; j < maps.size(); j++){
                if(maps[j].getId() == 02){
                    maps[j].setImage("Assets/nen3.png", ren);
                    maps[j].setSolid(0);
                }
            }
        }
        if(c.collision(player, maps[i]) && maps[i].getSolid()) {

            if(l) {
                if(player.getCurAnimation() != runl){
                    player.setCurAnimation(runl);
                    //player.setDest(player.getDX() + VELOC, player.getDY());}
                }
                //player.setDest(player.getDX() + VELOC, player.getDY());
                scroll(-VELOC, 0);
            }
            if(r) {
                if(player.getCurAnimation() != runr){
                    player.setCurAnimation(runr);
                    //player.setDest(player.getDX() - VELOC, player.getDY());}
                }
                //player.setDest(player.getDX() - VELOC, player.getDY());
                scroll(VELOC, 0);
            }
            if(u) {
                //player.setDest(player.getDX(), player.getDY() + VELOC);
                scroll(0, -VELOC);
            }
            if(d) {
                //player.setDest(player.getDX(), player.getDY() - VELOC);
                scroll(0, VELOC);
            }

        }
    }

    for(size_t i = 0; i < coins.size(); i++){
        Collision c;
        if(c.collision(coins[i], player)){
            pickCoin.play(0);
            coins.erase(coins.begin() + i);
            draw(intToString(counts), 80, 0, 95, 158, 160, font1);
            counts++;
            //draw(intToString(counts), 80, 0, 255, 255, 255, font1);
        }
    }

    for(size_t i = 0; i < mushrooms.size(); i++){
        Collision c;
        if(c.collision(mushrooms[i], player)){
            mushrooms.erase(mushrooms.begin() + i);
            draw(intToString(lifeBar), 1200, 0, 95, 158, 160, font2);
            lifeBar+=1;
            //draw(intToString(lifeBar), 1200, 0, 255, 255, 255, font2);
        }
    }

    for(size_t i = 0; i < bullets.size(); i++){
        Collision c;
        if(c.collision(bullets[i], player)){
            bulletSound.play(0);
            player.setCurAnimation(injured);
            draw(intToString(lifeBar), 1200, 0, 95, 158, 160, font2);
            lifeBar--;
            //draw(intToString(lifeBar), 1200, 0, 255, 255, 255, font2);
        }
    }

    for(size_t i = 0; i < enemies.size(); i++){
        Collision c;
        if(enemies[i].getCollisionWithPlayer()){
            draw(intToString(lifeBar), 1200, 0, 95, 158, 160, font2);
            lifeBar--;
            enemies[i].setCollisionWithPlayer(false);
        }
    }

}

void Game::scroll(const int &x, const int &y) {
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
    for(size_t i = 0; i < bullets.size(); i++) {
        bullets[i].setDest(bullets[i].getDX()+x, bullets[i].getDY()+y);
        bullets[i].setStartPos(bullets[i].getStartPosX() + x, bullets[i].getStartPosY() + y);
    }
    for(size_t i = 0; i < coins.size(); i++) {
        coins[i].setDest(coins[i].getDX()+x, coins[i].getDY()+y);
    }
    for(size_t i = 0; i < pedestals.size(); i++){
        pedestals[i].setDest(pedestals[i].getDX()+x, pedestals[i].getDY()+y);
    }
    for(size_t i = 0; i < enemies.size(); i++){
        enemies[i].setDest(enemies[i].getDX()+x, enemies[i].getDY()+y);
        enemies[i].setDestForBullet(x, y);
    }
    for(size_t i = 0; i < mushrooms.size(); i++){
        mushrooms[i].setDest(mushrooms[i].getDX()+x, mushrooms[i].getDY()+y);
    }
}

void Game::drawMap() {
    for(size_t i = 0; i < maps.size(); i++) {
        draw(maps[i]);
    }

    for(size_t i = 0; i < traps.size(); i++){

        draw(traps[i]);
    }

    for(size_t i = 0; i < bullets.size(); i++){
        draw(bullets[i]);
    }

    for(size_t i = 0; i < coins.size(); i++) {
        draw(coins[i]);
    }

    for(size_t i = 0; i < pedestals.size(); i++){
        draw(pedestals[i]);
    }

    for(size_t i = 0; i < enemies.size(); i++){
        draw(enemies[i]);
        if(enemies[i].checkShoot()){
            draw(enemies[i].getBullet());
        }
    }

    for(size_t i = 0; i < mushrooms.size(); i++){
        draw(mushrooms[i]);
    }
}










