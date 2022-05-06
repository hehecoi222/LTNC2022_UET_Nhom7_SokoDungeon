#ifndef Game_h
#define Game_h

#include <bits/stdc++.h>
using namespace std;
//Using SDL, SDL_image, standard IO, and strings

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
class Game {
   private:
    int cnt = 0;
    bool isRunning = true;
    SDL_Window* gWindow = NULL;

public:
    Game();
    ~Game();

    bool init();
    bool loadMedia();

    void handleEvents();
    void update();
    void render();

    void close();

    bool getGameState(){ return isRunning; }

    static SDL_Renderer* gRenderer;

    static TTF_Font* gFont;

    int getScreenW(){return WINDOW_WIDTH;}
    int getScreenH() {return WINDOW_HEIGHT;}

    static const int GRID_WIDTH = 15;
    static const int GRID_HEIGHT = 15;
    static const int BLOCK_WIDTH = 32;
    static const int WINDOW_WIDTH = GRID_WIDTH*BLOCK_WIDTH;
    static const int WINDOW_HEIGHT = GRID_HEIGHT*BLOCK_WIDTH;
};

template <class T> int checkCollisionwithMap(char** level, T& obj, int direction) {
    if (direction == obj.NOT_MOVE) return direction;
    int objX = obj.getCurX()/Game::BLOCK_WIDTH;
    int objY = obj.getCurY()/Game::BLOCK_WIDTH;
    switch (direction) {
        case obj.MOVE_LEFT:
            objX--;
            break;
        case obj.MOVE_RIGHT:
            objX++;
            break;
        case obj.MOVE_UP:
            objY--;
            break;
        case obj.MOVE_DOWN:
            objY++;
            break;
        default:
            return direction;
    }
    switch (level[objY][objX]) {
        case '#':
            return obj.NOT_MOVE;
            break;
        default:
            return direction;
    }
}

#endif /* Game_hpp */
