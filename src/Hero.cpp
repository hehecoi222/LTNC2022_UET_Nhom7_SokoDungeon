#include "Hero.h"
#include "Box.h"
#include "Game.h"
#include "find_res.h"
#include "mapgame.h"

Hero::Hero() {
    hCurPosX = 4*Game::BLOCK_WIDTH;
    hCurPosY = 2*Game::BLOCK_WIDTH;

    hDesPosX = hCurPosX;
    hDesPoxY = hCurPosY;

    hDestRect = {0, 0, HERO_WIDTH * 2, HERO_HEIGHT * 2};

    playerCurrentTex = new Texture();
    playerCurrentTex = &idleDown;

    cout << "Init Hero" << endl;
}

void Hero::loadHeroIMG() {
    //Load hero idle texture
    idleDown.loadFromFile(FindRes::getPath("img", "idown.png"));
    idleUp.loadFromFile(FindRes::getPath("img", "iup.png"));
    idleLeft.loadFromFile(FindRes::getPath("img", "ileft.png"));
    idleRight.loadFromFile(FindRes::getPath("img", "iright.png"));

    //Load hero walking texture
    walkDown.loadFromFile(FindRes::getPath("img", "wDown.png"));
    walkUp.loadFromFile(FindRes::getPath("img", "wUp.png"));
    walkLeft.loadFromFile(FindRes::getPath("img", "wLeft.png"));
    walkRight.loadFromFile(FindRes::getPath("img", "wRight.png"));


    for (int i = 0; i < PLAYER_FRAMES; i++) {
        playerCurrentFrame[i].x = (i * SPRITE_WIDTH ) + Game::BLOCK_WIDTH/2;
        playerCurrentFrame[i].y = Game::BLOCK_WIDTH/2;
        playerCurrentFrame[i].w = playerCurrentFrame[i].h = Game::BLOCK_WIDTH;
    }
}

int Hero::heroHandleEvent(SDL_Event& e) {
    int hNextDirection;
    // If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Determine hero direction
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                hNextDirection = checkCollisionwithMap(MapGame::level0, *this, MOVE_UP);
                hNextDirection = Box::hitBox(*this, hNextDirection);
                Move(hNextDirection);
                return hNextDirection;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                hNextDirection = checkCollisionwithMap(MapGame::level0, *this, MOVE_DOWN);
                hNextDirection = Box::hitBox(*this, hNextDirection);
                Move(hNextDirection);
                return hNextDirection;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                hNextDirection = checkCollisionwithMap(MapGame::level0, *this, MOVE_LEFT);
                hNextDirection = Box::hitBox(*this, hNextDirection);
                Move(hNextDirection);
                return hNextDirection;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                hNextDirection = checkCollisionwithMap(MapGame::level0, *this, MOVE_RIGHT);
                hNextDirection = Box::hitBox(*this, hNextDirection);
                Move(hNextDirection);
                return hNextDirection;
                break;
            default:
                return NOT_MOVE;
                break;
        }
    }
    return NOT_MOVE;
}

void Hero::Move(int direction) {
    switch (direction) {
        case MOVE_RIGHT:
            hDesPosX += Game::BLOCK_WIDTH;
            playerCurrentTex = &walkRight;
            while (hCurPosX != hDesPosX) {
                hCurPosX += HERO_VEL;
                heroRender();
            }
            playerCurrentTex = &idleRight;
            break;
        case MOVE_LEFT:
            hDesPosX -= Game::BLOCK_WIDTH;
            playerCurrentTex = &walkLeft;
            while (hCurPosX != hDesPosX) {
                hCurPosX -= HERO_VEL;
                heroRender();
            }
            playerCurrentTex = &idleLeft;
            break;
        case MOVE_UP:
            hDesPoxY -= Game::BLOCK_WIDTH;
            playerCurrentTex = &walkUp;
            while (hCurPosY != hDesPoxY) {
                hCurPosY -= HERO_VEL;
                heroRender();
            }
            playerCurrentTex = &idleUp;
            break;
        case MOVE_DOWN:
            hDesPoxY += Game::BLOCK_WIDTH;
            playerCurrentTex = &walkDown;
            while (hCurPosY != hDesPoxY) {
                hCurPosY += HERO_VEL;
                heroRender();
            }
            playerCurrentTex = &idleDown;
            break;
    }
}

void Hero::heroRender() {
    SDL_Rect* currentClip = &playerCurrentFrame[frame / 8];
    playerCurrentTex->render(hCurPosX - 16, hCurPosY - 16, currentClip, &hDestRect);            
    frame++;
    //Reset animation frame
    if (frame / 8 >= PLAYER_FRAMES) frame = 0;
}

Hero::~Hero() {
    cout << "Clear Hero" << endl;
    playerCurrentTex->free();
    playerCurrentTex = nullptr;
}