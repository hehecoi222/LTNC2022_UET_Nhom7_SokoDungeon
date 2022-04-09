#include "Box.h"
#include <stdio.h>
#include "find_res.h"

Box::Box() {
    //Initialize the variables
    bCurPosX = bDesPosX = 32;
    bCurPosY = bDesPosY = 0;
    bVelX = 0;
    bVelY = 0;
}

void Box::loadBoxIMG() {
    box.loadFromFile(FindRes::getPath("img", "box.png"));
    bRectDest = {0,0,BOX_WIDTH,BOX_HEIGHT};
}

int Box::collision(Hero& hero, int direction) {
    // If the box is colliding with the hero in the left direction
     if (bCurPosX < hero.getCurX() + 16 + Hero::HERO_WIDTH &&
               bCurPosX >= hero.getCurX() + 16 &&
               bCurPosY <= hero.getCurY() + 16 &&
               bCurPosY + BOX_HEIGHT > hero.getCurY() + 16 &&
               direction == MOVE_RIGHT) 
    {
        boxMove(MOVE_RIGHT);
        return MOVE_RIGHT;
    } else if (bCurPosX + BOX_WIDTH > hero.getCurX() + 16 &&
               bCurPosX + BOX_WIDTH <= hero.getCurX() + 16 + Hero::HERO_WIDTH &&
               bCurPosY <= hero.getCurY() + 16 &&
               bCurPosY + BOX_HEIGHT > hero.getCurY() + 16 &&
               direction == MOVE_LEFT) 
    {
        boxMove(MOVE_LEFT);
        return MOVE_LEFT;
    } else if (bCurPosY < hero.getCurY() + 16 + Hero::HERO_HEIGHT &&
               bCurPosY >= hero.getCurY() + 16 &&
               bCurPosX <= hero.getCurX() + 16 &&
               bCurPosX + BOX_WIDTH > hero.getCurX() + 16 &&
               direction == MOVE_DOWN) 
    {
        boxMove(MOVE_DOWN);
        return MOVE_DOWN;
    } else if (bCurPosY + BOX_HEIGHT > hero.getCurY() + 16 &&
               bCurPosY + BOX_HEIGHT <= hero.getCurY() + 16 + Hero::HERO_HEIGHT &&
               bCurPosX <= hero.getCurX() + 16 &&
               bCurPosX + BOX_WIDTH > hero.getCurX() + 16 && 
               direction == MOVE_UP) 
    {
        boxMove(MOVE_UP);
        return MOVE_UP;
    }
}

void Box::boxMove(int direction) {
    switch (direction) {
        case MOVE_LEFT:
            bDesPosX -= BLOCK_WIDTH;
            while (bCurPosX != bDesPosX) {
                bCurPosX -= BOX_VEL;
                boxRender();
            }
            break;
        case MOVE_RIGHT:
            bDesPosX += BLOCK_WIDTH;
            while (bCurPosX != bDesPosX) {
                bCurPosX += BOX_VEL;
                boxRender();
            }
            break;
        case MOVE_UP:
            bDesPosY -= BLOCK_WIDTH;
            while (bCurPosY != bDesPosY) {
                bCurPosY -= BOX_VEL;
                boxRender();
            }
            break;
        case MOVE_DOWN:
            bDesPosY += BLOCK_WIDTH;
            while (bCurPosY != bDesPosY) {
                bCurPosY += BOX_VEL;
                boxRender();
            }
            break;
    }
}

void Box::boxRender() {
    printf("Box: %d, %d\n", bCurPosX, bCurPosY);
    box.render(bCurPosX, bCurPosY, &bRectClip, &bRectDest);
}

Box::~Box() {
    box.free();
}
