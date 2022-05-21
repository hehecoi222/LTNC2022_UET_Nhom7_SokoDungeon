#include "Game.h"
#include "Box.h"
#include "Hero.h"
#include "Texture.h"
#include "find_res.h"
#include "Map.h"
#include "Savegame.h"
#include "Menu.h"
#include "Enemy.h"

SDL_Renderer* Game::gRenderer = nullptr;
TTF_Font* Game::gFont = nullptr;

//Music and sound effects will be used
Mix_Music* Game::gVictory = NULL, *Game::gMusic = NULL, *Game::gTheme = NULL;
Mix_Chunk* Game::gBox = NULL, *Game::gHero = NULL, *Game::gMouse = NULL;
bool Game::Musicon = true;
bool Game::sEffect = true;

//Create different render viewport
const SDL_Rect fullSizeViewPort = {0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT};
const SDL_Rect subViewport = {Game::WINDOW_WIDTH/2 - Game::BLOCK_WIDTH*Game::GRID_WIDTH/2, Game::WINDOW_HEIGHT/2 - Game::BLOCK_WIDTH*Game::GRID_HEIGHT/2, 480, 480};

//Menu
Menu gMenu;

//Main character
Hero mainHero;
Enemy mainEnemy;

// Map
Map Game0;
Savegame save;

Game::Game() {}
Game::~Game() {}

bool Game::init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        gWindow = SDL_CreateWindow("SoKoDungeon", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! %s\n", SDL_GetError());
            success = false;
        } else {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n",
                       SDL_GetError());
                success = false;
            } else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf(
                        "SDL_image could not initialize! SDL_image Error: %s\n",
                        IMG_GetError());
                    success = false;
                }

                // Initialize SDL_Mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf(
                        "SDL_Mixer could not initialize! SDL_mixer Error: %s\n",
                        Mix_GetError());
                    success = false;
                }

                // Initialize SDL_ttf
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
                           TTF_GetError());
                }
            }
        }
    }
    return success;
}

bool Game::loadMedia() {
    bool success = true;

    gFont = TTF_OpenFont(FindRes::getPath("font","DungeonFont.ttf"), 36);
    if( gFont == NULL )
    {
        cout << "Failed to load gFont" << TTF_GetError() << endl;
        success = false;
    }

    //Load menu texture
    gMenu.loadMenu();
    
    //Load music and sound effect
    gVictory = Mix_LoadMUS(FindRes::getPath("audio", "Victory.wav"));
    gMusic = Mix_LoadMUS(FindRes::getPath("audio", "Soundtrack.wav"));
    gTheme = Mix_LoadMUS(FindRes::getPath("audio", "Theme Song.wav"));
    gHero = Mix_LoadWAV(FindRes::getPath("audio", "Footsteps.wav"));
    gBox = Mix_LoadWAV(FindRes::getPath("audio", "box.wav"));
    gMouse = Mix_LoadWAV(FindRes::getPath("audio", "MouseClick.wav"));    
    //Play intro sound while being in Menu state
    if(gMenu.getMenuState() && Musicon)
        Mix_PlayMusic(gTheme, -1);
    else if (Musicon)
        Mix_PlayMusic(gMusic, -1);
    // load Hero img
    mainHero.loadHeroIMG();
    mainEnemy.loadEnemyIMG();
    // load Box img
    Box::loadBoxIMG();

    // Load map
    save.loadSavefile(FindRes::getPath("savefile","level0.skbsf"), mainHero, mainEnemy, Game0);
    save.saveHeroPosition(mainHero.getCurX(), mainHero.getCurY());
    save.loadHighScore(FindRes::getPath("savefile","fileHighScore.skbhsf"));
    return success;
}

void Game::handleEvents() {
    // Event handler
    SDL_Event e;
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        // User requests quit
        if (e.type == SDL_QUIT) {
            isRunning = false;
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_u && e.key.repeat == 0) {
            save.undoMove(mainHero, mainEnemy);
        } 
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFTBRACKET)
        {
            Game0.NextMap();
            save.clear();
            Game0.preLoadMap();
            mainHero.setpos();
            mainEnemy.setCurXY(Enemy::enemyGlobalPos.first, Enemy::enemyGlobalPos.second);
            save.setMapInt(Game0.current_map);
            save.saveHeroPosition(mainHero.getCurX(), mainHero.getCurY());
            save.loadHighScore(FindRes::getPath("savefile","fileHighScore.skbhsf"));
        }
        else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHTBRACKET)
        {
            Game0.PrevMap();
            save.clear();
            Game0.preLoadMap();
            mainHero.setpos();
            mainEnemy.setCurXY(Enemy::enemyGlobalPos.first, Enemy::enemyGlobalPos.second);
            save.setMapInt(Game0.current_map);
            save.saveHeroPosition(mainHero.getCurX(), mainHero.getCurY());
            save.loadHighScore(FindRes::getPath("savefile","fileHighScore.skbhsf"));
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
            save.clear();
            Game0.preLoadMap();
            mainHero.setpos();
            mainEnemy.setCurXY(Enemy::enemyGlobalPos.first, Enemy::enemyGlobalPos.second);
        }
        else {
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                save.recordMove(mainHero.heroHandleEvent(e, mainEnemy));
                save.recordEnemyMove(mainEnemy.Move(
                    mainEnemy.findPathToHero(mainHero.getCurX(), mainHero.getCurY())));
            }
        gMenu.menuHandleEvent(e, isRunning);
        }
    }
}
void Game::update() {
    if (Box::winLevel()) {
        save.compareHighScore(FindRes::getPath("savefile", "fileHighScore.skbhsf"));
        Game0.NextMap();
        Game0.PresVic();
        render();
        if(sEffect)
            Mix_PlayMusic(gVictory, -1);
        SDL_Delay(2000);
        Mix_HaltMusic();
        save.clear();
        Game0.preLoadMap();
        mainHero.setpos();
        mainEnemy.setCurXY(Enemy::enemyGlobalPos.first, Enemy::enemyGlobalPos.second);
        save.setMapInt(Game0.current_map);
        save.saveHeroPosition(mainHero.getCurX(), mainHero.getCurY());
        save.loadHighScore(FindRes::getPath("savefile","fileHighScore.skbhsf"));
    }

}

void Game::render() {
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);

    if(!Box::winLevel())
    {
        //Change render viewport
        SDL_RenderSetViewport(gRenderer, &subViewport);
        // Load Map0
        Game0.LoadMap();
        // Render player
        mainHero.heroRender();

        // Render enemy
        mainEnemy.enemyRender();

        // Render box
        Box::layerBoxRender();

        //set renderer to menu viewport
        SDL_RenderSetViewport(gRenderer, &fullSizeViewPort);

        //render menu
        gMenu.menuRender();
    }
    // Update Screen
    SDL_RenderPresent(gRenderer);
}

void Game::close() {
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    // Free the sound effects and sound
    Mix_FreeMusic(gVictory);
    Mix_FreeChunk(gHero);
    Mix_FreeChunk(gBox);
    Mix_FreeMusic(gTheme);
    Mix_FreeMusic(gMusic);
    Mix_FreeChunk(gMouse);
    gVictory = gTheme = gMusic = NULL;
    gHero = gBox = gMouse = NULL;

    gWindow = NULL;
    gRenderer = NULL;
    Box::box.free();
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            delete Box::layerBox[i][j];
        }
        delete[] Box::layerBox[i];
        delete[] Map::level0[i];
    }
    delete[] Box::layerBox;
    delete[] Map::level0;
    save.toFile(FindRes::getPath("savefile", "level0.skbsf"));
    // Quit SDL subsystems
    SDL_Quit();
    cout << "Game clear" << endl;
}
