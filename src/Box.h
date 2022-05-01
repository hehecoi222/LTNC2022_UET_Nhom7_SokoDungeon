#ifndef BOX_H
#define BOX_H
#include "Game.h"
#include "Hero.h"
#include "Texture.h"
#include "find_res.h"
#include "mapgame.h"

class Box {
   public:
    // The dimensions of the box
    static const int BOX_WIDTH = 32;
    static const int BOX_HEIGHT = 32;

    // Maximum axis velocity of the BOX
    static const int BLOCK_WIDTH = 32;
    static const int BOX_VEL = 4;

    // Initializes the variables
    Box();
    Box(int x, int y);
    ~Box();

    // Box layer
    static Box*** layerBox;

    // Flush box layer
    static void flushBoxLayer();

    // Box count, Box win count
    static int boxCount, boxWinCount;

    // Winning the level
    static bool winLevel() {return boxWinCount == boxCount;}

    // Load box img
    static void loadBoxIMG();

    // Check chain hit
    template <class T>
    static int hitBox(T& obj, int direction) {
        if (direction == obj.NOT_MOVE) return direction;
        int objX = obj.getCurX() / obj.BLOCK_WIDTH;
        int objY = obj.getCurY() / obj.BLOCK_WIDTH;
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
        if (layerBox[objY][objX]) {
            return layerBox[objY][objX]->collision(direction);
        } else
            return direction;
    }

    // Found the collision between box
    int collision(int direction);

    // Move the box according to collision
    void Move(int direction);

    // Return move to save game
    void saveBoxinsave();

    // Shows the box on the screen
    void boxRender();
    // Bulk show on screen
    static void layerBoxRender();

    // Return box current position
    int getCurX() { return bCurPosX; }
    int getCurY() { return bCurPosY; }

    // Simple Texture
    static LTexture box;

    // Box direction
    enum { NOT_MOVE, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

   private:
    // The X and Y offsets of the box
    int bCurPosX, bCurPosY;

    // The X and Y destination of the box
    int bDesPosX, bDesPosY;

    // The velocity of the box
    int bVelX, bVelY;

    // Winning state
    bool bWin = false;

    // Check winning state
    void checkWin(int**);

    // Add up in boxCount
    void addBoxCount();

    // Rectangle to represent the box
    SDL_Rect bRectDest;
    SDL_Rect bRectClip{2, 8, 17, 16};
};

#endif