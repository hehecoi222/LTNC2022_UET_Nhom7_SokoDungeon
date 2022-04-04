#include "Hero.h"
#include "find_res.h"

Hero::Hero()
{
    hPosX = 100;
    hPosY = 100;

    hDesPosX = hPosX;
    hDesPoxY = hPosY;

    hVelX = 0;
    hVelY = 0;

    playerCurrentTex = new LTexture();
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
                 hVelY += HERO_VEL;
                 playerCurrentTex = &walkDown;
                 break;
            case SDLK_LEFT:
                 hVelX -= HERO_VEL;
                playerCurrentTex = &walkLeft;
                 break;
            case SDLK_RIGHT:
                 hVelX += HERO_VEL;
                playerCurrentTex = &walkRight;
                 break;
        }

    }
    // If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                 hVelY +=HERO_VEL;
                playerCurrentTex = &idleUp;
                 break;
            case SDLK_DOWN:
                 hVelY -= HERO_VEL;
                 playerCurrentTex = &idleDown;
                 break;
            case SDLK_LEFT:
                 hVelX += HERO_VEL;
                 playerCurrentTex = &idleLeft;
                 break;
            case SDLK_RIGHT:
                 hVelX -= HERO_VEL;
                 playerCurrentTex = &idleRight;
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
        while (hPosX != hDesPosX)
        {
            hPosX += HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleRight;
        break;
    case 2:
        hDesPosX -= BLOCK_WIDTH;
        playerCurrentTex = &walkLeft;
        while (hPosX != hDesPosX)
        {
            hPosX -= HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleLeft;
        break;
    case 3:
        hDesPoxY -= BLOCK_WIDTH;
        playerCurrentTex = &walkUp;
        while (hPosY != hDesPoxY)
        {
            hPosY -= HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleUp;
        break;
    case 4:
        hDesPoxY += BLOCK_WIDTH;
        playerCurrentTex = &walkDown;
        while (hPosY != hDesPoxY)
        {
            hPosY += HERO_VEL;
            heroRender();
        }
        playerCurrentTex = &idleDown;
        break;
    }
}

void Hero::heroRender()
{
	SDL_RenderClear( Game::gRenderer );
	SDL_Rect* currentClip = &playerCurrentFrame[frame/16];
    playerCurrentTex->render(hPosX, hPosY, currentClip);
	SDL_RenderPresent( Game::gRenderer );
    frame++;
	if( frame/16 >= PLAYER_FRAMES ) frame = 0;
    cout << hPosX  << " " << hPosY << endl;

}

// Hero::~Hero(){
//     playerCurrentTex->free();
//     playerCurrentTex = nullptr;
// }