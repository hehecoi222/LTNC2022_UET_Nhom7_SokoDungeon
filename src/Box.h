#ifndef BOX_H
#define BOX_H
#include "Game.h"
#include "Texture.h"
#include "find_res.h"
#include "Hero.h"

class Box {
public:
    //The dimensions of the box
    static const int BOX_WIDTH = 32;
    static const int BOX_HEIGHT = 32;

    //Maximum axis velocity of the BOX
    static const int BLOCK_WIDTH = 32;
    static const int BOX_VEL = 4;

    //Initializes the variables
    Box();
    ~Box();

    //Load box img
    void loadBoxIMG();

    //Found the collision
    int collision(Hero& hero, int direction);

    //Move the box according to collision
    void boxMove(int direction);

    //Shows the box on the screen
    void boxRender();

    //Return box current position
    int getCurX(){return bCurPosX;}
    int getCurY(){return bCurPosY;}

    //Simple Texture
    LTexture box;

    //Box direction
    enum {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT
    };

private:
    //The X and Y offsets of the box
    int bCurPosX, bCurPosY;

    //The X and Y destination of the box
    int bDesPosX, bDesPosY;

    //The velocity of the box
    int bVelX, bVelY;

    //Rectangle to represent the box
    SDL_Rect bRectDest;
    SDL_Rect bRectClip{2,8,17,16};
};

#endif