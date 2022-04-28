#include "Hero.h"
#include "Game.h"
#include "find_res.h"

#include "mapgame.h"

Hero::Hero()
{
    hCurPosX = 32;
    hCurPosY = 32;

    hDesPosX = hCurPosX;
    hDesPoxY = hCurPosY;
   
    hVelX = 0;
    hVelY = 0;

    playerRectDest = {0,0,HERO_WIDTH*2,HERO_HEIGHT*2};

    playerCurrentTex = new LTexture();
    playerCurrentTex = &idleDown;
}

void Hero::loadHeroIMG(){
    idleDown.loadFromFile(FindRes::getPath("img", "idown.png"));
    idleDown.loadFromFile(FindRes::getPath("img","idown.png"));
    idleDown.loadFromFile(FindRes::getPath("img","idown.png"));
    idleUp.loadFromFile(FindRes::getPath("img","iup.png"));
    idleLeft.loadFromFile(FindRes::getPath("img","ileft.png"));
    idleRight.loadFromFile(FindRes::getPath("img","iright.png"));

    walkDown.loadFromFile(FindRes::getPath("img","wDown.png"));
    walkUp.loadFromFile(FindRes::getPath("img","wUp.png"));
    walkLeft.loadFromFile(FindRes::getPath("img","wLeft.png"));
    walkRight.loadFromFile(FindRes::getPath("img","wRight.png"));
    for (int i = 0; i < PLAYER_FRAMES; i++)
	{
		playerCurrentFrame[i].x = (i*64)+16;
		playerCurrentFrame[i].y = 16;
		playerCurrentFrame[i].w = playerCurrentFrame[i].h = 32;
	}
}

int Hero::heroHandleEvent( SDL_Event &e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
      
		 {
            case SDLK_w:
            case SDLK_UP:
                Move(MOVE_UP);
                if (checkCollisionwithMap(MapGame::level0, *this)) {
                    Move(MOVE_DOWN);
                    return NOT_MOVE;
                }
                return MOVE_UP;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                Move(MOVE_DOWN);
                if (checkCollisionwithMap(MapGame::level0, *this)) {
                    Move(MOVE_UP);
                    return NOT_MOVE;
                }
                return MOVE_DOWN;
                 break;
            case SDLK_a:
            case SDLK_LEFT:
                Move(MOVE_LEFT);
                if (checkCollisionwithMap(MapGame::level0, *this)) {
                    Move(MOVE_RIGHT);
                    return NOT_MOVE;
                }
                return MOVE_LEFT;
                 break;
            case SDLK_d:
            case SDLK_RIGHT:
                Move(MOVE_RIGHT);
                if (checkCollisionwithMap(MapGame::level0, *this)) {
                    Move(MOVE_LEFT);
                    return NOT_MOVE;
                }
                return MOVE_RIGHT;
                 break;
            default:
                return NOT_MOVE;
                break;
        }
    }
    return NOT_MOVE;
}

void Hero::Move(int direction){
    switch (direction)
    {
    case MOVE_RIGHT:
        hDesPosX+= BLOCK_WIDTH;
        playerCurrentTex = &walkRight;
        while (hCurPosX != hDesPosX)
        {
            hCurPosX += HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleRight;
        break;
    case MOVE_LEFT:
        hDesPosX -= BLOCK_WIDTH;
        playerCurrentTex = &walkLeft;
        while (hCurPosX != hDesPosX)
        {
            hCurPosX -= HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleLeft;
        break;
    case MOVE_UP:
        hDesPoxY -= BLOCK_WIDTH;
        playerCurrentTex = &walkUp;
        while (hCurPosY != hDesPoxY)
        {
            hCurPosY -= HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleUp;
        break;
    case MOVE_DOWN:
        hDesPoxY += BLOCK_WIDTH;
        playerCurrentTex = &walkDown;
        while (hCurPosY != hDesPoxY)
        {
            hCurPosY += HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleDown;
        break;
    }
}

void Hero::heroRender()
{
	// SDL_RenderClear( Game::gRenderer );
	SDL_Rect* currentClip = &playerCurrentFrame[frame/8];
    playerCurrentTex->render(hCurPosX-16, hCurPosY-16, currentClip,&playerRectDest);
	// SDL_RenderPresent( Game::gRenderer );
    frame++;
	if( frame/8 >= PLAYER_FRAMES ) frame = 0;
}

Hero::~Hero(){
    playerCurrentTex->free();
    playerCurrentTex = nullptr;
}