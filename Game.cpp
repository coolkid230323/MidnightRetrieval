#include "Game.h"

Game::Game() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) cout << "Failed at SDL_Init()" << SDL_GetError() << endl;
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren) < 0) cout << "Failed at SDL_CreateWindowAndRenderer()" << SDL_GetError() << endl;
    SDL_SetWindowTitle(win, "Midnight Retrieval");

    /*countCoin = new Object();
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
    scoreBackground = new Object();*/

    try {

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
        scoreBackground = new Object();
    } catch (std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;

    }

    levels[0] = "Assets/level_1.txt";
    levels[1] = "Assets/level_2.txt";
    levels[2] = "Assets/level_3.txt";
    level = 0;

    background = LoadTexture("Assets/background.png", ren);
    CrossfadeTexture(ren, background, 1000);

    (*menuBackGround).setImage("Assets/menuBackGround.png", ren);
    (*menuBackGround).setDest(0, 0, WIDTH, HEIGHT);
    (*menuBackGround).setSource(0, 0, 1808, 1017);

    (*optionButton).setImage("Assets/optionbutton.png", ren);
    (*optionButton).setDest(1216, 0, 64, 64);
    (*optionButton).setSource(0, 0, 479, 479);

    (*victoryLogo).setImage("Assets/victorylogo.png", ren);
    (*victoryLogo).setDest(480, 50, 300, 140);
    (*victoryLogo).setSource(0, 0, 918, 428);

    (*gameOverLogo).setImage("Assets/gameoverlogo.png", ren);
    (*gameOverLogo).setDest(480, 50, 300, 140);
    (*gameOverLogo).setSource(0, 0, 783, 446);

    (*scoreBackground).setImage("Assets/scorebackground.png", ren);
    (*scoreBackground).setDest(300, 200, 700, 500);
    (*scoreBackground).setSource(0, 0, 1260, 1204);

    mainMusic.load("Sounds/mainMusic.wav");
    mainMusic.play(-1);
    mainMusic.pause();
    pickCoin.load("Sounds/pickcoin.wav");
    bulletSound.load("Sounds/bulletSound.wav");
    pickMushRoom.load("Sounds/pickmushroom.wav");
    mouseClick.load("Sounds/mouseclick.wav");
    soundDeath.load("Sounds/death.wav");

    m_Map.loadMap(levels[level], maps, traps, bullets, coins, enemies, pedestals, mushrooms, ren, TILE_SIZE);

    TTF_Init();
    running = true;
    showingMenu = true;
    clickingOptions = false;
    playing = false;
    victory = false;
    defeat = false;
    collisionWithEnemy = false;
    counts = 0;
    lifeBar = 20;
    saveCoins = 0;
    saveLevel = 0;
    saveLifes = 20;
    highestScore = 0;
    font1 = TTF_OpenFont("Fonts/GameName.ttf", 70);
    font2 = TTF_OpenFont("Fonts/GameName.ttf", 70);
    font3 = TTF_OpenFont("Fonts/GameName.ttf", 200);
    font4 = TTF_OpenFont("Fonts/GameName.ttf", 70);
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

    player.setImage("Assets/main.png", ren);
    player.setSource(0, 0, 324, 348);
    stand = player.createCycle(1, 81, 116, 4, 10);
    runr = player.createCycle(2, 81, 116, 4, 4);
    runl = player.createCycle(3, 81, 116, 4, 4);
    //injured = player.createCycle(4, 70, 70, 4, 10);
    player.setCurAnimation(stand);

    loop();
}

Game::~Game() {
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_CloseFont(font3);
    TTF_CloseFont(font4);
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
    delete scoreBackground;
    delete countCoin;
    delete countLives;


    countCoin = nullptr;
    countLives = nullptr;

    menuButton = nullptr;
    optionButton = nullptr;
    quitButton = nullptr;
    resumeButton = nullptr;
    playButton = nullptr;
    continueButton = nullptr;

    victoryLogo = nullptr;
    gameOverLogo = nullptr;
    scoreBackground = nullptr;

    menuBackGround = nullptr;
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
        else if(victory){
            showWinGame();
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
        draw(*resumeButton);
        draw(intToString(highestScore), 1030, 200, 239, 228, 176, font1);
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

        draw(*scoreBackground);
        draw(*gameOverLogo);
        draw(intToString(counts), 600, 300, 231, 146, 139, font3);
        draw(*menuButton);
    }
    else if(victory){
        drawMap();
        draw(player);

        draw(*scoreBackground);
        draw(*victoryLogo);
        draw(intToString(counts), 600, 300, 231, 146, 139, font3);
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
    (*resumeButton).setDest(150, 550, 320, 140);


    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) {running = false; cout << "Quitting" << endl;}
        Uint32 mouseState = SDL_GetMouseState(&mousex, &mousey);

        if(mousex >= (*playButton).getDX() && mousex <= (*playButton).getDX() + (*playButton).getDW()
           && mousey >= (*playButton).getDY() && mousey <= (*playButton).getDY() + (*playButton).getDH())
        {
            (*playButton).setImage("Assets/playbutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                mouseClick.play(0);
                SDL_Delay(500);
                playing = true;
                showingMenu = false;

                l = r = u = d = false;
                player.setCurAnimation(stand);

                counts = 0;
                lifeBar = 20;
                level = 0;
                saveCoins = counts;
                saveLevel = level;
                saveLifes = lifeBar;
                m_Map.clearMap(maps, traps, bullets, coins, enemies, pedestals, mushrooms);
                m_Map.loadMap(levels[level], maps, traps, bullets, coins, enemies, pedestals, mushrooms, ren, TILE_SIZE);
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
                mouseClick.play(0);
                SDL_Delay(500);
                running = false;
            }
        }
        else{
            (*quitButton).setImage("Assets/quitbutton01.png", ren);
        }

        if(mousex >= (*resumeButton).getDX() && mousex <= (*resumeButton).getDX() + (*resumeButton).getDW()
           && mousey >= (*resumeButton).getDY() && mousey <= (*resumeButton).getDY() + (*resumeButton).getDH())
        {
            (*resumeButton).setImage("Assets/resumebutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                mouseClick.play(0);
                SDL_Delay(500);

                playing = true;
                showingMenu = false;

                l = r = u = d = false;
                player.setCurAnimation(stand);

                counts = saveCoins;
                lifeBar = saveLifes;
                level = saveLevel;
                m_Map.clearMap(maps, traps, bullets, coins, enemies, pedestals, mushrooms);
                m_Map.loadMap(levels[level], maps, traps, bullets, coins, enemies, pedestals, mushrooms, ren, TILE_SIZE);
            }
        }
        else{
            (*resumeButton).setImage("Assets/resumebutton01.png", ren);
        }

    }


}

void Game::showGameOver()
{
    SDL_Event e;
    (*menuButton).setDest(480, 500, 320, 140);

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) {running = false; cout << "Quitting" << endl;}
        Uint32 mouseState = SDL_GetMouseState(&mousex, &mousey);

        if(mousex >= (*menuButton).getDX() && mousex <= (*menuButton).getDX() + (*menuButton).getDW()
           && mousey >= (*menuButton).getDY() && mousey <= (*menuButton).getDY() + (*menuButton).getDH())
        {
            (*menuButton).setImage("Assets/menubutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                mouseClick.play(0);
                SDL_Delay(500);
                playing = false;
                highestScore = max(highestScore, counts);
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
                mouseClick.play(0);
                SDL_Delay(500);
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
                mouseClick.play(0);
                SDL_Delay(500);
                highestScore = max(highestScore, counts);
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
                mouseClick.play(0);
                SDL_Delay(500);
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
    SDL_Event e;
    (*menuButton).setDest(480, 500, 320, 140);

    while(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT) {running = false; cout << "Quitting" << endl;}
        Uint32 mouseState = SDL_GetMouseState(&mousex, &mousey);

        if(mousex >= (*menuButton).getDX() && mousex <= (*menuButton).getDX() + (*menuButton).getDW()
           && mousey >= (*menuButton).getDY() && mousey <= (*menuButton).getDY() + (*menuButton).getDH())
        {
            (*menuButton).setImage("Assets/menubutton02.png", ren);

            if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)){
                mouseClick.play(0);
                SDL_Delay(500);
                highestScore = max(highestScore, counts);
                playing = false;
                victory = false;
                showingMenu = true;
                clickingOptions = false;
            }
        }
        else{
            (*menuButton).setImage("Assets/menubutton01.png", ren);
        }
    }
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
                mouseClick.play(0);
                SDL_Delay(500);
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
        highestScore = max(highestScore, counts);
        playing = false;
        defeat = true;
        player.setCurAnimation(stand);
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
        }
        scroll(VELOC, 0);
    }
    if(r){
        if(player.getCurAnimation() != runr){
            player.setCurAnimation(runr);
        }
        scroll(-VELOC, 0);
    }
    if(u) {
        scroll(0, VELOC);
    }
    if(d) {
        scroll(0, -VELOC);
    }
    if(white){
        player.setImage("Assets/player0.png", ren);
    }

    player.updateAnimation();

    /*if(level > 2){
        saveLevel = level--;
        highestScore = max(highestScore, counts);
        playing = false;
        victory = true;
        player.setCurAnimation(stand);
        return;
    }*/

    for(size_t i = 0; i < maps.size(); i++) {
        Collision c;
        if(c.collision(player, maps[i]) && maps[i].getId() == 2){
            level++;
            m_Map.clearMap(maps, traps, bullets, coins, enemies, pedestals, mushrooms);
            m_Map.loadMap(levels[level], maps, traps, bullets, coins, enemies, pedestals, mushrooms, ren, TILE_SIZE);

            saveCoins = counts;
            saveLevel = level;
            saveLifes = lifeBar;
        }
        if(c.collision(player, maps[i]) && maps[i].getId() == 77){
            highestScore = max(highestScore, counts);
            playing = false;
            victory = true;
            player.setCurAnimation(stand);
            return;
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

    for(size_t i = 0; i < traps.size(); i++){
        Collision c;
        if(c.collision(player, traps[i])){
            soundDeath.play(0);
            playing = false;
            defeat = true;
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
            pickMushRoom.play(0);
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
            soundDeath.play(0);
            //player.setCurAnimation(injured);
            draw(intToString(lifeBar), 1200, 0, 95, 158, 160, font2);
            lifeBar--;
            //draw(intToString(lifeBar), 1200, 0, 255, 255, 255, font2);
        }
    }

    for(size_t i = 0; i < enemies.size(); i++){
        Collision c;
        if(enemies[i].getCollisionWithPlayer()){
            bulletSound.play(0);
            soundDeath.play(0);
            draw(intToString(lifeBar), 1200, 0, 95, 158, 160, font2);
            lifeBar--;
            enemies[i].setCollisionWithPlayer(false);
        }
    }

    for(size_t i = 0; i < enemies.size(); i++){
        Collision c;
        if(c.collision(player, enemies[i]) && !collisionWithEnemy){
            collisionWithEnemy = true;
            soundDeath.play(0);
            draw(intToString(lifeBar), 1200, 0, 95, 158, 160, font2);
            lifeBar--;
        }
        if(i == enemies.size() - 1 && !(c.collision(player, enemies[i]))){
            collisionWithEnemy = false;
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



















