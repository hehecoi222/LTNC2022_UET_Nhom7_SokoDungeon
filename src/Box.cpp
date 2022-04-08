#include "Box.h"
#include <stdio.h>
#include "find_res.h"

Box::Box() {
    //Initialize the variables
    bCurPosX = bDesPosX = 400;
    bCurPosY = bDesPosY = 400;
    bVelX = 0;
    bVelY = 0;
}

void Box::loadBoxIMG() {
    box.loadFromFile(FindRes::getPath("img", "box.png"));
    bRect = {0,0,32,32};
}

bool Box::collision(Hero& hero) {
    // If the box is colliding with the hero in the left direction
    if (bCurPosX < hero.getCurX() + Hero::HERO_WIDTH &&
        bCurPosX + Box::BOX_WIDTH > hero.getCurX() &&
        bCurPosY < hero.getCurY() + Hero::HERO_HEIGHT &&
        bCurPosY + Box::BOX_HEIGHT > hero.getCurY()) {
        boxMove(MOVE_LEFT);
        return true;
    } // Else if the box is colliding with the hero in the right direction
    else if (bCurPosX + Box::BOX_WIDTH > hero.getCurX() &&
             bCurPosX < hero.getCurX() + Hero::HERO_WIDTH &&
             bCurPosY < hero.getCurY() + Hero::HERO_HEIGHT &&
             bCurPosY + Box::BOX_HEIGHT > hero.getCurY()) {
        boxMove(MOVE_RIGHT);
        return true;
    } // Else if the box is colliding with the hero in the up direction
    else if (bCurPosY < hero.getCurY() + Hero::HERO_HEIGHT &&
             bCurPosY + Box::BOX_HEIGHT > hero.getCurY() &&
             bCurPosX < hero.getCurX() + Hero::HERO_WIDTH &&
             bCurPosX + Box::BOX_WIDTH > hero.getCurX()) {
        boxMove(MOVE_UP);
        return true;
    } // Else if the box is colliding with the hero in the down direction
    else if (bCurPosY + Box::BOX_HEIGHT > hero.getCurY() &&
             bCurPosY < hero.getCurY() + Hero::HERO_HEIGHT &&
             bCurPosX < hero.getCurX() + Hero::HERO_WIDTH &&
             bCurPosX + Box::BOX_WIDTH > hero.getCurX()) {
        boxMove(MOVE_DOWN);
        return true;
    }
    return false;
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
    box.render(bCurPosX, bCurPosY,&bRect);
}

Box::~Box() {
    box.free();
}
