#include "Game.h"

#include "Box.h"
#include "Hero.h"
#include "Texture.h"
#include "find_res.h"
#include "mapgame.h"
#include "Savegame.h"
#include "Menu.h"

SDL_Renderer* Game::gRenderer = nullptr;
TTF_Font* Game::gFont = nullptr;

//Create different render viewport
const SDL_Rect fullSizeViewPort = {0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT};
const SDL_Rect subViewport = {Game::WINDOW_WIDTH/2 - Game::BLOCK_WIDTH*Game::GRID_WIDTH/2, Game::WINDOW_HEIGHT/2 - Game::BLOCK_WIDTH*Game::GRID_HEIGHT/2, 480, 480};

//Menu
Menu gMenu;

//Main character
Hero mainHero;

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

    //Load Hero img
    mainHero.loadHeroIMG();

    // load Box img
    Box::loadBoxIMG();

    //Initialize save function
    save.saveHeroPosition(mainHero.getCurX(), mainHero.getCurY());

    //Load map
    Game0.preLoadMap();
    save.loadSavefile(FindRes::getPath("savefile","level0.skbsf"), mainHero);

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
        else if(gMenu.getMenuState()){
            gMenu.menuHandleEvent(e, isRunning);
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r && e.key.repeat == 0) {
            save.undoMove(mainHero);
        } 
        else {
            save.recordMove(mainHero.heroHandleEvent(e));
        }
    }
}
void Game::update() {
    if (Box::winLevel()) {
        isRunning = false;
        save.clear();
    }
}

void Game::render() {
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    SDL_RenderClear(gRenderer);

    //Change render viewport
    SDL_RenderSetViewport(gRenderer, &subViewport);

    // Load Mapgame0
    Game0.LoadMap();
    // Render player
    mainHero.heroRender();

    // Render box
    Box::layerBoxRender();

    //set renderer to menu viewport
    SDL_RenderSetViewport(gRenderer, &fullSizeViewPort);

    //render menu
    gMenu.menuRender();

    // Update Screen
    SDL_RenderPresent(gRenderer);
}

void Game::close() {
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
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
    save.toFile(FindRes::getPath("savefile", "level0.skbsf"));
    // Quit SDL subsystems
    SDL_Quit();
    cout << "Game clear" << endl;
}
