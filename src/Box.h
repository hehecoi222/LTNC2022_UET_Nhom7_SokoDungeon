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

    // Load box img
    static void loadBoxIMG();

    // Found the collision
    template <class T>
    int collision(T& obj, int direction) {
        // If the box is colliding with the obj in the left direction
        if (direction == NOT_MOVE) {
            return NOT_MOVE;
        } else if (bCurPosX < obj.getCurX() + Hero::HERO_WIDTH &&
                   bCurPosX >= obj.getCurX() && bCurPosY <= obj.getCurY() &&
                   bCurPosY + BOX_HEIGHT > obj.getCurY() &&
                   direction == MOVE_RIGHT) {
            int way = checkCollisionwithMap(MapGame::level0, *this, MOVE_RIGHT);
            Move(way);
            return way;
        } else if (bCurPosX + BOX_WIDTH > obj.getCurX() &&
                   bCurPosX + BOX_WIDTH <= obj.getCurX() + Hero::HERO_WIDTH &&
                   bCurPosY <= obj.getCurY() &&
                   bCurPosY + BOX_HEIGHT > obj.getCurY() &&
                   direction == MOVE_LEFT) {
            int way = checkCollisionwithMap(MapGame::level0, *this, MOVE_LEFT);
            Move(way);
            return way;
        } else if (bCurPosY < obj.getCurY() + Hero::HERO_HEIGHT &&
                   bCurPosY >= obj.getCurY() && bCurPosX <= obj.getCurX() &&
                   bCurPosX + BOX_WIDTH > obj.getCurX() &&
                   direction == MOVE_DOWN) {
            int way = checkCollisionwithMap(MapGame::level0, *this, MOVE_DOWN);
            Move(way);
            return way;
        } else if (bCurPosY + BOX_HEIGHT > obj.getCurY() &&
                   bCurPosY + BOX_HEIGHT <= obj.getCurY() + Hero::HERO_HEIGHT &&
                   bCurPosX <= obj.getCurX() &&
                   bCurPosX + BOX_WIDTH > obj.getCurX() &&
                   direction == MOVE_UP) {
            int way = checkCollisionwithMap(MapGame::level0, *this, MOVE_UP);
            Move(way);
            return way;
        }
        return NOT_MOVE;
    }

    // Move the box according to collision
    void Move(int direction);

    // Shows the box on the screen
    void boxRender();

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

    // Rectangle to represent the box
    SDL_Rect bRectDest;
    SDL_Rect bRectClip{2, 8, 17, 16};
};

#endif