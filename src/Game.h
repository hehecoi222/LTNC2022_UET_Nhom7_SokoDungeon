#ifndef Game_h
#define Game_h

#include <iostream>
using namespace std;
//Using SDL, SDL_image, standard IO, and strings

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class Game {
   private:
    int cnt = 0;
    bool isRunning = true;
    SDL_Window* gWindow = NULL;
    bool isThemeMusicPlaying = false;
        
public:
    Game();
    ~Game();

    bool init();
    bool loadMedia();

    void handleEvents();
    void update();
    void render();

    void close();
    
    static void restartGame();

    bool getGameState(){ return isRunning; }

    static SDL_Renderer* gRenderer;

    static TTF_Font* gFont;

    //Sound of Victory
    static Mix_Chunk* gVictory;
    //Soundtrack 
    static Mix_Music* gMusic;
    //Sound effect of Hero
    static Mix_Chunk* gHero;
    //Sound effect of Box
    static Mix_Chunk* gBox;
    //Sound of main theme
    static Mix_Music* gTheme;
    //Sound effect of Mouse Click
    static Mix_Chunk* gMouse;
    
    int getScreenW(){return WINDOW_WIDTH;}
    int getScreenH() {return WINDOW_HEIGHT;}

    static const int GRID_WIDTH = 15;
    static const int GRID_HEIGHT = 15;
    static const int BLOCK_WIDTH = 48;
    static const int WINDOW_HEIGHT = GRID_HEIGHT * BLOCK_WIDTH + BLOCK_WIDTH*2;
    static const int WINDOW_WIDTH = WINDOW_HEIGHT * 16 / 9;
    static bool musicOn;
    static bool isEffect;
};

#endif /* Game_hpp */
