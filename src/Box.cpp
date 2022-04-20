#include "Box.h"

#include <stdio.h>

#include "find_res.h"

LTexture Box::box;
Box*** Box::layerBox = nullptr;

Box::Box() {
    // Initialize the variables
    bCurPosX = bDesPosX = 32;
    bCurPosY = bDesPosY = 0;
    bVelX = 0;
    bVelY = 0;
    bRectDest = {0, 0, BOX_WIDTH, BOX_HEIGHT};
}

Box::Box(int x, int y) {
    // Initialize the variables
    bCurPosX = bDesPosX = x;
    bCurPosY = bDesPosY = y;
    bVelX = 0;
    bVelY = 0;
    bRectDest = {0, 0, BOX_WIDTH, BOX_HEIGHT};
}

void Box::loadBoxIMG() {
    Box::box.loadFromFile(FindRes::getPath("img", "box.png"));
    layerBox = new Box**[20];
    for (int i = 0; i < 20; i++) {
        layerBox[i] = new Box*[25];
        for (int j = 0; j < 25; j++) {
            layerBox[i][j] = nullptr;
        }
    }
}

void Box::Move(int direction) {
    switch (direction) {
        case MOVE_LEFT:
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH) - 1] = layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)];
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] = nullptr;
            bDesPosX -= BLOCK_WIDTH;
            while (bCurPosX != bDesPosX) {
                bCurPosX -= BOX_VEL;
                boxRender();
            }
            break;
        case MOVE_RIGHT:
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH) + 1] = layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)];
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] = nullptr;
            bDesPosX += BLOCK_WIDTH;
            while (bCurPosX != bDesPosX) {
                bCurPosX += BOX_VEL;
                boxRender();
            }
            break;
        case MOVE_UP:
            layerBox[(bDesPosY / BLOCK_WIDTH) - 1][(bDesPosX / BLOCK_WIDTH)] = layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)];
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] = nullptr;
            bDesPosY -= BLOCK_WIDTH;
            while (bCurPosY != bDesPosY) {
                bCurPosY -= BOX_VEL;
                boxRender();
            }
            break;
        case MOVE_DOWN:
            layerBox[(bDesPosY / BLOCK_WIDTH) + 1][(bDesPosX / BLOCK_WIDTH)] = layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)];
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] = nullptr;
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

void Box::layerBoxRender() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 25; j++) {
            if (layerBox[i][j]) layerBox[i][j]->boxRender();
        }
    }
}

Box::~Box() {}
