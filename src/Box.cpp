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
    bRectDest = {0,0,BOX_WIDTH,BOX_HEIGHT};
}

int Box::collision(Hero& hero) {
    // If the box is colliding with the hero in the left direction
    if (bCurPosX + BOX_WIDTH - 8 > hero.getCurX() + 32 &&
        bCurPosX + BOX_WIDTH - 8 < hero.getCurX() + 48 &&
        bCurPosY + BOX_HEIGHT > hero.getCurY() + 24 &&
        bCurPosY < hero.getCurY() + 40)
    {
        boxMove(MOVE_LEFT);
        return MOVE_LEFT;
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
