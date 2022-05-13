#include "Game.h"

#include "Box.h"
#include "Hero.h"
#include "Texture.h"
#include "find_res.h"
#include "mapgame.h"
#include "Savegame.h"
#include "Enemy.h"

SDL_Renderer* Game::gRenderer = nullptr;
TTF_Font* Game::gFont = nullptr;
Mix_Music* Game::gVictory = nullptr;
Mix_Music* Game::gMusic = nullptr;
Mix_Chunk* Game::gBox = NULL;
Mix_Chunk* Game::gHero = NULL;
// init main character
Hero mainHero;
Enemy mainEnemy(4*Game::BLOCK_WIDTH, 2*Game::BLOCK_WIDTH);

// Map
MapGame Game0;
SDL_Rect Mapblock;

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
        gWindow = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                   WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! %s\n", SDL_GetError());
            success = false;
        } else {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(
                gWindow, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    Game::gFont = TTF_OpenFont(FindRes::getPath("font", "lazy.ttf"), 28);
    SDL_Color textColor = {0, 0, 0, 255};
    //Load sound
    gVictory = Mix_LoadMUS(FindRes::getPath("audio", "Victory.wav"));
    gHero = Mix_LoadWAV(FindRes::getPath("audio", "Footsteps.wav"));
    gBox = Mix_LoadWAV(FindRes::getPath("audio", "box.wav"));
    gMusic = Mix_LoadMUS(FindRes::getPath("", ""));
    // load Hero img
    mainHero.loadHeroIMG();
    mainEnemy.loadEnemyIMG();
    // load Box img
    Box::loadBoxIMG();

    // Load map
    save.loadSavefile(FindRes::getPath("savefile","level0.skbsf"), mainHero, Game0);
    save.saveHeroPosition(mainHero.getCurX(), mainHero.getCurY());
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
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r && e.key.repeat == 0) {
            save.undoMove(mainHero);
        } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n && e.key.repeat == 0) {
            Game0.NextMap();
            loadMedia();
        } else {
            if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                save.recordMove(mainHero.heroHandleEvent(e));
                mainEnemy.Move(mainEnemy.findPath(mainHero.getCurX()/BLOCK_WIDTH, mainHero.getCurY()/BLOCK_WIDTH));
            }
        }
    }
}
void Game::update() {
    if (Box::winLevel()) {
        Game0.NextMap();
        Game0.PresVic();
        SDL_RenderPresent(gRenderer);
        Mix_PlayMusic(gVictory, -1);
        SDL_Delay(2000);
        Mix_HaltMusic();
        save.clear();
        Game0.preLoadMap();
        mainHero.setpos();
        save.setMapInt(Game0.current_map);
        save.saveHeroPosition(mainHero.getCurX(), mainHero.getCurY());
    }
}

void Game::render() {
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    
    // Load Mapgame0
    Game0.LoadMap();
    // Render player
    mainHero.heroRender();

    mainEnemy.enemyRender();

    // Render box
    Box::layerBoxRender();
    
    // Update Screen
    SDL_RenderPresent(gRenderer);
}

void Game::close() {
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    // Free the sound effects
    Mix_FreeMusic(gVictory);
    Mix_FreeChunk(gHero);
    Mix_FreeChunk(gBox);
    gVictory = NULL;
    gHero = gBox =NULL;
    gWindow = NULL;
    gRenderer = NULL;
    Box::box.free();
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            delete Box::layerBox[i][j];
        }
        delete[] Box::layerBox[i];
        delete[] MapGame::level0[i];
    }
    delete[] Box::layerBox;
    delete[] MapGame::level0;
    save.toFile(FindRes::getPath("savefile","level0.skbsf"));
    // Quit SDL subsystems
    SDL_Quit();
    cout << "Game clear";
}
