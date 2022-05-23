#include <stdio.h>
#include "Box.h"
#include "find_res.h"
#include "Map.h"
#include "Game.h"
#include "Savegame.h"

Texture Box::box;
Box*** Box::layerBox = nullptr;
int Box::boxCount = 0, Box::boxWinCount = 0;
extern Savegame save;
extern Enemy mainEnemy;

Box::Box() {
    // Initialize the variables
    bCurPosX = bDesPosX = 0;
    bCurPosY = bDesPosY = 0;
    bVelX = 0;
    bVelY = 0;
    bRectDest = {0, 0, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
}

Box::Box(int x, int y) {
    // Initialize the variables
    bCurPosX = bDesPosX = x;
    bCurPosY = bDesPosY = y;
    bVelX = 0;
    bVelY = 0;
    bRectDest = {0, 0, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
}

void Box::loadBoxIMG() {
    Box::box.loadFromFile(FindRes::getPath("img", "box.png"));
    layerBox = new Box**[Game::GRID_HEIGHT];
    for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        layerBox[i] = new Box*[Game::GRID_WIDTH];
        for (int j = 0; j < Game::GRID_WIDTH; j++) {
            layerBox[i][j] = nullptr;
        }
    }
}

void Box::flushBoxLayer() {
    for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        for (int j = 0; j < Game::GRID_WIDTH; j++) {
            if (layerBox[i][j] != nullptr) {
                delete layerBox[i][j];
                layerBox[i][j] = nullptr;
            }
        }
    }
    boxCount = boxWinCount = 0;  
}

int Box::collision(int direction) {
    // If the box is colliding with the obj in the left direction
    if (direction == NOT_MOVE) return direction;
    int way = checkCollisionwithMap(Map::level0, *this, direction);
    way = mainEnemy.checkCollisionWithThis(bCurPosX, bCurPosY, way);
    way = hitBox(*this, way);
    Move(way);
    if (way) {
        saveBoxinsave();
    }
    return way;
}

void Box::saveBoxinsave() {
    save.boxPush(bDesPosX/Game::BLOCK_WIDTH, bDesPosY/Game::BLOCK_WIDTH);
}

void Box::Move(int direction) {
    switch (direction) {
        case MOVE_LEFT:
            layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH) - 1] =
                layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)];
            layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)] =
                nullptr;
            bDesPosX -= Game::BLOCK_WIDTH;
            while (bCurPosX != bDesPosX) {
                bCurPosX -= BOX_VEL;
                if(Game::effectOn)
                    Mix_PlayChannel(-1, Game::gBox, 0);
                boxRender();
            }
            addBoxCount();
            break;
        case MOVE_RIGHT:
            layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH) + 1] =
                layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)];
            layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)] =
                nullptr;
            bDesPosX += Game::BLOCK_WIDTH;
            while (bCurPosX != bDesPosX) {
                bCurPosX += BOX_VEL;
                if(Game::effectOn)
                    Mix_PlayChannel(-1, Game::gBox, 0);
                boxRender();
            }
            addBoxCount();
            break;
        case MOVE_UP:
            layerBox[(bDesPosY / Game::BLOCK_WIDTH) - 1][(bDesPosX / Game::BLOCK_WIDTH)] =
                layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)];
            layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)] =
                nullptr;
            bDesPosY -= Game::BLOCK_WIDTH;
            while (bCurPosY != bDesPosY) {
                bCurPosY -= BOX_VEL;
                if(Game::effectOn)
                    Mix_PlayChannel(-1, Game::gBox, 0);
                boxRender();
            }
            addBoxCount();
            break;
        case MOVE_DOWN:
            layerBox[(bDesPosY / Game::BLOCK_WIDTH) + 1][(bDesPosX / Game::BLOCK_WIDTH)] =
                layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)];
            layerBox[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)] =
                nullptr;
            bDesPosY += Game::BLOCK_WIDTH;
            while (bCurPosY != bDesPosY) {
                bCurPosY += BOX_VEL;
                if(Game::effectOn)
                    Mix_PlayChannel(-1, Game::gBox, 0);
                boxRender();
            }
            addBoxCount();
            break;
    }
}

void Box::checkWin(char** level) {
    if (level[(bDesPosY / Game::BLOCK_WIDTH)][(bDesPosX / Game::BLOCK_WIDTH)] == '.') {
        bWin = true;
    } else {
        bWin = false;
    }
}

void Box::addBoxCount() {
    bool temp = bWin;
    checkWin(Map::level0);
    if (temp != bWin && bWin) {
        boxWinCount++;
    } else if (temp != bWin && !bWin) {
        boxWinCount--;
    }
}

void Box::boxRender() {
    if (bWin) {
        Box::box.setColor(127, 127, 255);
        Box::box.render(bCurPosX, bCurPosY, &bRectClip, &bRectDest);
        Box::box.setColor(255, 255, 255);
    } else {
        Box::box.render(bCurPosX, bCurPosY, &bRectClip, &bRectDest);
    }
}

void Box::layerBoxRender() {
    for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        for (int j = 0; j < Game::GRID_WIDTH; j++) {
            if (layerBox[i][j]) layerBox[i][j]->boxRender();
        }
    }
}

Box::~Box() {}