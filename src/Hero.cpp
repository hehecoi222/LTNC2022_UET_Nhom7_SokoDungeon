#include "Hero.h"
#include "Box.h"
#include "Game.h"
#include "find_res.h"
#include "Map.h"
#include <utility>

std::pair<int, int> Hero::pos = std::make_pair(0, 0);

Hero::Hero() {
    hCurPosX = hDesPosX = pos.first;
    hCurPosY = hDesPosY = pos.second;

    playerRectDest = {0, 0, Game::BLOCK_WIDTH * 2, Game::BLOCK_WIDTH * 2};

    playerCurrentTex = new Texture();
    playerCurrentTex = &idleDown;

    cout << "Init Hero" << endl;
}

Hero::~Hero() {
    cout << "Clear Hero" << endl;
    playerCurrentTex->free();
    playerCurrentTex = nullptr;
}

void Hero::setpos()
{
    hCurPosX = hDesPosX = pos.first;
    hCurPosY = hDesPosY = pos.second;
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
        playerCurrentFrame[i].x = (i * HERO_CLIP_WIDTH ) + Game::BLOCK_WIDTH/2;
        playerCurrentFrame[i].y = Game::BLOCK_WIDTH/2;
        playerCurrentFrame[i].w = playerCurrentFrame[i].h = Game::BLOCK_WIDTH;
    }
}

int Hero::heroHandleEvent(SDL_Event& e, Enemy& mainEnemy) {
    // If a key was pressed
    int way;
    // Adjust the velocity
    switch (e.key.keysym.sym)
    {
        case SDLK_w:
        case SDLK_UP:
            way = checkCollisionwithMap(Map::level0, *this, MOVE_UP);
            way = mainEnemy.checkCollisionWithThis(hDesPosX, hDesPosY, way);
            way = Box::hitBox(*this, way);
            Move(way);
            return way;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            way = checkCollisionwithMap(Map::level0, *this, MOVE_DOWN);
            way = mainEnemy.checkCollisionWithThis(hDesPosX, hDesPosY, way);
            way = Box::hitBox(*this, way);
            Move(way);
            return way;
            break;
        case SDLK_a:
        case SDLK_LEFT:
            way = checkCollisionwithMap(Map::level0, *this, MOVE_LEFT);
            way = mainEnemy.checkCollisionWithThis(hDesPosX, hDesPosY, way);
            way = Box::hitBox(*this, way);
            Move(way);
            return way;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            way = checkCollisionwithMap(Map::level0, *this, MOVE_RIGHT);
            way = mainEnemy.checkCollisionWithThis(hDesPosX, hDesPosY, way);
            way = Box::hitBox(*this, way);
            Move(way);
            return way;
            break;
        default:
            return NOT_MOVE;
            break;
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
                Mix_PlayChannel(-1, Game::gHero, 0);
                heroRender();
            }
            playerCurrentTex = &idleRight;
            break;
        case MOVE_LEFT:
            hDesPosX -= Game::BLOCK_WIDTH;
            playerCurrentTex = &walkLeft;
            while (hCurPosX != hDesPosX) {
                hCurPosX -= HERO_VEL;
                Mix_PlayChannel(-1, Game::gHero, 0);
                heroRender();
            }
            playerCurrentTex = &idleLeft;
            break;
        case MOVE_UP:
            hDesPosY -= Game::BLOCK_WIDTH;
            playerCurrentTex = &walkUp;
            while (hCurPosY != hDesPosY) {
                hCurPosY -= HERO_VEL;
                Mix_PlayChannel(-1, Game::gHero, 0);
                heroRender();
            }
            playerCurrentTex = &idleUp;
            break;
        case MOVE_DOWN:
            hDesPosY += Game::BLOCK_WIDTH;
            playerCurrentTex = &walkDown;
            while (hCurPosY != hDesPosY) {
                hCurPosY += HERO_VEL;
                Mix_PlayChannel(-1, Game::gHero, 0);
                heroRender();
            }
            playerCurrentTex = &idleDown;
            break;
    }
}

void Hero::heroRender() {
    SDL_Rect* currentClip = &playerCurrentFrame[frame / 8];
    playerCurrentTex->render(hCurPosX - Game::BLOCK_WIDTH/2, hCurPosY - Game::BLOCK_WIDTH/2, currentClip,
                             &playerRectDest);
    // SDL_RenderPresent( Game::gRenderer );
    frame++;
    //Reset animation frame
    if (frame / 8 >= PLAYER_FRAMES) frame = 0;
}

