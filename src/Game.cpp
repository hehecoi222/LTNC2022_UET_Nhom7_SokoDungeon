#include "Game.h"

#include "Box.h"
#include "Hero.h"
#include "Texture.h"
#include "find_res.h"
#include "mapgame.h"
#include "Savegame.h"

SDL_Renderer* Game::gRenderer = nullptr;
TTF_Font* Game::gFont = nullptr;

// init main character
Hero mainHero;

// Map
LTexture Map;
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
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
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

    Game::gFont = TTF_OpenFont("font/AV.ttf", 28);
    SDL_Color textColor = {0, 0, 0, 255};

    // load Hero img
    mainHero.loadHeroIMG();
    // load Box img
    Box::loadBoxIMG();

    // Initialize save function
    save.saveHeroPosition(mainHero.getCurX(), mainHero.getCurY());

    // Load map
    Game0.preLoadMap();

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
        } else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0) {
            Game0.NextMap();
            loadMedia();
            render();
        } else {
            save.recordMove(mainHero.heroHandleEvent(e));
        }
    }
}
void Game::update() {
    if (Box::winLevel()) {
        isRunning = false;
    }
}

void Game::render() {
    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    // render map
    Map.render(300, 300, &Mapblock);
    // Load Mapgame0
    Game0.LoadMap();
    // Render player
    mainHero.heroRender();

    // Render box
    Box::layerBoxRender();

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
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            delete Box::layerBox[i][j];
        }
        delete[] Box::layerBox[i];
        delete[] MapGame::level0[i];
    }
    delete[] Box::layerBox;
    delete[] MapGame::level0;
    // Quit SDL subsystems
    SDL_Quit();
    cout << "Game clear";
}
