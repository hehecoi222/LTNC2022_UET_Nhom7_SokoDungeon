// TODO: collision (block) hero, move arcording to hero

#ifndef ENEMY_H
#define ENEMY_H

#include "Texture.h"
class Enemy {
   public:
    // Initializer
    Enemy();
    Enemy(int x, int y);
    ~Enemy();

    // load enemy img
    void loadEnemyIMG();

    // render enemy
    void enemyRender();

    // Return base information
    int getCurX() { return eCurPosX; }
    int getCurY() { return eCurPosY; }
    // Set base information
    void setCurX(int x) { eCurPosX = x; }
    void setCurY(int y) { eCurPosY = y; }

    // Find path to object
    int findPathToHero(int desireX, int desireY);

    // Move enemy
    int Move(int direction);

    // Check collision
    int checkCollisionWithThis(int objX, int objY, int direction);

    // Set enemy direction
    enum { NOT_MOVE, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

   private:
    // X, Y position
    int eCurPosX, eCurPosY;

    // Enemy current state
    int eCurState = NOT_MOVE;

    // Enemy texture idle
    Texture* eTexture;

    // Enemy rectangle in screen
    SDL_Rect eRectDest;
    // Enemy rectangle in texture
    SDL_Rect eRectClip;

    // frame count
    int frame = 0;
    int frameCount = 0;

    // Set of move
    int nextMove =  NOT_MOVE;
};

#endif