#include "Box.h"
#include <stdio.h>
#include "find_res.h"

LTexture Box::box;

Box::Box() {
    //Initialize the variables
    bCurPosX = bDesPosX = 32;
    bCurPosY = bDesPosY = 0;
    bVelX = 0;
    bVelY = 0;
    bRectDest = {0,0,BOX_WIDTH,BOX_HEIGHT};
}

Box::Box(int x, int y) {
    //Initialize the variables
    bCurPosX = bDesPosX = x;
    bCurPosY = bDesPosY = y;
    bVelX = 0;
    bVelY = 0;
    bRectDest = {0,0,BOX_WIDTH,BOX_HEIGHT};
}

void Box::loadBoxIMG() {
    Box::box.loadFromFile(FindRes::getPath("img", "box.png"));
}

void Box::Move(int direction) {
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
    Box::box.render(bCurPosX, bCurPosY, &bRectClip, &bRectDest);
}

Box::~Box() {
}
