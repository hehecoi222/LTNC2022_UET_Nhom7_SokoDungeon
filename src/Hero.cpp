#include "Hero.h"
#include "find_res.h"

Hero::Hero()
{
    hCurPosX = 100;
    hCurPosY = 100;

    hDesPosX = hCurPosX;
    hDesPoxY = hCurPosY;

    hVelX = 0;
    hVelY = 0;

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
		playerCurrentFrame[i].x = i*64;
		playerCurrentFrame[i].y = 0;
		playerCurrentFrame[i].w = playerCurrentFrame[i].h = 64;
	}
}

void Hero::heroHandleEvent( SDL_Event &e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                heroMove(MOVE_UP);
                break;
            case SDLK_DOWN:
                heroMove(MOVE_DOWN);
                 break;
            case SDLK_LEFT:
                heroMove(MOVE_LEFT);
                 break;
            case SDLK_RIGHT:
                heroMove(MOVE_RIGHT);
                 break;
        }

    }
}

void Hero::heroMove(int direction){
    switch (direction)
    {
    case 1:
        hDesPosX+= BLOCK_WIDTH;
        playerCurrentTex = &walkRight;
        while (hCurPosX != hDesPosX)
        {
            hCurPosX += HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleRight;
        break;
    case 2:
        hDesPosX -= BLOCK_WIDTH;
        playerCurrentTex = &walkLeft;
        while (hCurPosX != hDesPosX)
        {
            hCurPosX -= HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleLeft;
        break;
    case 3:
        hDesPoxY -= BLOCK_WIDTH;
        playerCurrentTex = &walkUp;
        while (hCurPosY != hDesPoxY)
        {
            hCurPosY -= HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleUp;
        break;
    case 4:
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
	SDL_RenderClear( Game::gRenderer );
	SDL_Rect* currentClip = &playerCurrentFrame[frame/8];
    playerCurrentTex->render(hCurPosX, hCurPosY, currentClip);
	SDL_RenderPresent( Game::gRenderer );
    frame++;
	if( frame/8 >= PLAYER_FRAMES ) frame = 0;
    cout << hCurPosX  << " " << hCurPosY << endl;

}

Hero::~Hero(){
    playerCurrentTex->free();
    playerCurrentTex = nullptr;
}