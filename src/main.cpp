#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <find_res.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        return 1;
    }
    if (TTF_Init() != 0) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 2;
    }
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    if (screenSurface == NULL) {
        printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 2;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 2;
    }
    // SDL_Surface *image = IMG_Load((*imgPath + "preview.png").c_str());
    SDL_Surface *image = IMG_Load(FindRes::getPath("img", "preview.png"));
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect imageRect = {WINDOW_WIDTH/4,WINDOW_HEIGHT/4,WINDOW_WIDTH/2,WINDOW_HEIGHT/2};
    if (imageTexture == NULL) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }
    TTF_Font* font = TTF_OpenFont(FindRes::getPath("font","lazy.ttf"), 24);
    SDL_Color textcolor = {0,0,0,0xFF};
    SDL_Surface* text = TTF_RenderText_Solid(font, "Hello World!", textcolor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect rect = {0, 0, text->w, text->h};
    SDL_FreeSurface(text);
    if (texture == NULL) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 4;
    }

    bool isQuit = false;
    SDL_Event event;
   
    while (!isQuit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderCopy(renderer,imageTexture,NULL,&imageRect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}