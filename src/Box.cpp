#include "Box.h"

#include <stdio.h>

#include "find_res.h"
#include "mapgame.h"
#include "Game.h"
#include "Savegame.h"

LTexture Box::box;
Box*** Box::layerBox = nullptr;
int Box::boxCount = 0, Box::boxWinCount = 0;
extern Savegame save;

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

void Box::flushBoxLayer() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 25; j++) {
            if (layerBox[i][j] != nullptr) {
                delete layerBox[i][j];
                layerBox[i][j] = nullptr;
            }
        }
    }
}

int Box::collision(int direction) {
    // If the box is colliding with the obj in the left direction
    if (direction == NOT_MOVE) return direction;
    int way = checkCollisionwithMap(MapGame::level0, *this, direction);
    way = hitBox(*this, way);
    Move(way);
    if (way) saveBoxinsave();
    return way;
}

void Box::saveBoxinsave() {
    save.boxPush(bDesPosX/BLOCK_WIDTH, bDesPosY/BLOCK_WIDTH);
}

void Box::Move(int direction) {
    switch (direction) {
        case MOVE_LEFT:
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH) - 1] =
                layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)];
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] =
                nullptr;
            bDesPosX -= BLOCK_WIDTH;
            while (bCurPosX != bDesPosX) {
                bCurPosX -= BOX_VEL;
                boxRender();
            }
            addBoxCount();
            break;
        case MOVE_RIGHT:
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH) + 1] =
                layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)];
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] =
                nullptr;
            bDesPosX += BLOCK_WIDTH;
            while (bCurPosX != bDesPosX) {
                bCurPosX += BOX_VEL;
                boxRender();
            }
            addBoxCount();
            break;
        case MOVE_UP:
            layerBox[(bDesPosY / BLOCK_WIDTH) - 1][(bDesPosX / BLOCK_WIDTH)] =
                layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)];
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] =
                nullptr;
            bDesPosY -= BLOCK_WIDTH;
            while (bCurPosY != bDesPosY) {
                bCurPosY -= BOX_VEL;
                boxRender();
            }
            addBoxCount();
            break;
        case MOVE_DOWN:
            layerBox[(bDesPosY / BLOCK_WIDTH) + 1][(bDesPosX / BLOCK_WIDTH)] =
                layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)];
            layerBox[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] =
                nullptr;
            bDesPosY += BLOCK_WIDTH;
            while (bCurPosY != bDesPosY) {
                bCurPosY += BOX_VEL;
                boxRender();
            }
            addBoxCount();
            break;
    }
}

void Box::checkWin(char** level) {
    if (level[(bDesPosY / BLOCK_WIDTH)][(bDesPosX / BLOCK_WIDTH)] == 10) {
        bWin = true;
    } else {
        bWin = false;
    }
}

void Box::addBoxCount() {
    bool temp = bWin;
    checkWin(MapGame::level0);
    if (temp != bWin && bWin) {
        boxWinCount++;
    } else if (temp != bWin && !bWin) {
        boxWinCount--;
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
