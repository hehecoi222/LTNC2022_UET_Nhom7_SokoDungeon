#include "Enemy.h"

#include "Box.h"
#include "Game.h"
#include "find_res.h"
#include "mapgame.h"

Enemy::Enemy() {
    eCurPosX = eCurPosY = 0;
    eRectDest = {0, 0, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    eTexture = new LTexture();
}

Enemy::Enemy(int x, int y) {
    eCurPosX = x;
    eCurPosY = y;
    eRectDest = {x, y, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    eTexture = new LTexture();
}

Enemy::~Enemy() { delete eTexture; }

void Enemy::loadEnemyIMG() {
    eTexture->loadFromFile(FindRes::getPath("img", "eWalk.png"));
    eRectClip = {0, 0, 16, 16};
}

void Enemy::enemyRender() {
    int clipDirection = 0;
    switch (eCurState) {
        case NOT_MOVE:
        case MOVE_DOWN:
            clipDirection = 0;
            break;
        case MOVE_UP:
            clipDirection = 1;
            break;
        case MOVE_LEFT:
            clipDirection = 2;
            break;
        case MOVE_RIGHT:
            clipDirection = 3;
            break;
        default:
            break;
    }
    eRectClip = {16 * clipDirection, 16 * frame, 16, 16};
    eTexture->render(eRectDest.x, eRectDest.y, &eRectClip);
    frameCount++;
    if (frameCount % 12 == 0) {
        frameCount = 0;
        frame++;
        if (frame == 4) {
            frame = 0;
        }
    }
}

int Enemy::findPath(int desireX, int desireY) {
    return NOT_MOVE;
    int disX = desireX - eCurPosX / Game::BLOCK_WIDTH;
    int disY = desireY - eCurPosY / Game::BLOCK_WIDTH;
    if (disX == 0 && disY == 0) {
        return NOT_MOVE;
    }
    if (abs(disX) > abs(disY)) {
        if (disX > 0 &&
            checkCollisionwithMap(MapGame::level0, *this, MOVE_RIGHT) &&
            Box::layerBox[eCurPosY / Game::BLOCK_WIDTH]
                         [eCurPosX / Game::BLOCK_WIDTH + 1] == nullptr) {
            return MOVE_RIGHT;
        } else if (disX < 0 &&
                   checkCollisionwithMap(MapGame::level0, *this, MOVE_LEFT) &&
                   Box::layerBox[eCurPosY / Game::BLOCK_WIDTH]
                                [eCurPosX / Game::BLOCK_WIDTH - 1] == nullptr) {
            return MOVE_LEFT;
        } else if (disY > 0 &&
                   checkCollisionwithMap(MapGame::level0, *this, MOVE_DOWN) &&
                   Box::layerBox[eCurPosY / Game::BLOCK_WIDTH + 1]
                                [eCurPosX / Game::BLOCK_WIDTH] == nullptr) {
            return MOVE_DOWN;
        } else if (disY < 0 &&
                   checkCollisionwithMap(MapGame::level0, *this, MOVE_UP) &&
                   Box::layerBox[eCurPosY / Game::BLOCK_WIDTH - 1]
                                [eCurPosX / Game::BLOCK_WIDTH] == nullptr) {
            return MOVE_UP;
        }
    }
    if (abs(disY) >= abs(disX)) {
        if (disY > 0 &&
            checkCollisionwithMap(MapGame::level0, *this, MOVE_DOWN) &&
            Box::layerBox[eCurPosY / Game::BLOCK_WIDTH + 1]
                         [eCurPosX / Game::BLOCK_WIDTH] == nullptr) {
            return MOVE_DOWN;
        } else if (disY < 0 &&
                   checkCollisionwithMap(MapGame::level0, *this, MOVE_UP) &&
                   Box::layerBox[eCurPosY / Game::BLOCK_WIDTH - 1]
                                [eCurPosX / Game::BLOCK_WIDTH] == nullptr) {
            return MOVE_UP;
        } else if (disX > 0 &&
                   checkCollisionwithMap(MapGame::level0, *this, MOVE_RIGHT) &&
                   Box::layerBox[eCurPosY / Game::BLOCK_WIDTH]
                                [eCurPosX / Game::BLOCK_WIDTH + 1] == nullptr) {
            return MOVE_RIGHT;
        } else if (disX < 0 &&
                   checkCollisionwithMap(MapGame::level0, *this, MOVE_LEFT) &&
                   Box::layerBox[eCurPosY / Game::BLOCK_WIDTH]
                                [eCurPosX / Game::BLOCK_WIDTH - 1] == nullptr) {
            return MOVE_LEFT;
        }
    }
    return NOT_MOVE;
}

int Enemy::Move(int direction, int objX, int objY) {
    objX = abs(objX - eCurPosX);
    objY = abs(objY - eCurPosY);
    if (objX == Game::BLOCK_WIDTH || objY == Game::BLOCK_WIDTH)
        direction = NOT_MOVE;
    switch (direction) {
        case MOVE_UP:
            eCurPosY -= Game::BLOCK_WIDTH;
            break;
        case MOVE_DOWN:
            eCurPosY += Game::BLOCK_WIDTH;
            break;
        case MOVE_LEFT:
            eCurPosX -= Game::BLOCK_WIDTH;
            break;
        case MOVE_RIGHT:
            eCurPosX += Game::BLOCK_WIDTH;
            break;
        default:
            break;
    }
    eRectDest.x = eCurPosX;
    eRectDest.y = eCurPosY;
    eCurState = direction;
    return direction;
}

int Enemy::checkCollisionWithThis(int objX, int objY, int direction) {
    if (direction == NOT_MOVE) return direction;
    objX = objX / Game::BLOCK_WIDTH;
    objY = objY / Game::BLOCK_WIDTH;
    int eTempX = eCurPosX / Game::BLOCK_WIDTH;
    int eTempY = eCurPosY / Game::BLOCK_WIDTH;
    switch (findPath(objX, objY)) {
        case MOVE_LEFT:
            eTempX--;
            break;
        case MOVE_RIGHT:
            eTempX++;
            break;
        case MOVE_UP:
            eTempY--;
            break;
        case MOVE_DOWN:
            eTempY++;
            break;
        default:
            return NOT_MOVE;
    }
    switch (direction) {
        case MOVE_LEFT:
            objX--;
            break;
        case MOVE_RIGHT:
            objX++;
            break;
        case MOVE_UP:
            objY--;
            break;
        case MOVE_DOWN:
            objY++;
            break;
        default:
            return direction;
    }
    if (objX == eTempX && objY == eTempY) return NOT_MOVE;
    return direction;
}