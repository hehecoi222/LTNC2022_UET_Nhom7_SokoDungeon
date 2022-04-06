#include "Hero.h"
#include "find_res.h"

Hero::Hero()
{
    hPosX = 100;
    hPosY = 100;

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
                hVelY -= HERO_VEL;
                playerCurrentTex = &walkUp;
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

void Hero::heroMove(){
    //Move the dot left or right
    if(hVelX != 0){
    SDL_Delay(100);
    hPosX += hVelX;
    }

    //If the dot went too far to the left or right
    if( ( hPosX < 0 ) || ( hPosX - HERO_WIDTH > 800) )
    {
        //Move back
        hPosX -= hVelX;
    }
    //Move the dot up or down
    if(hVelY != 0){
    SDL_Delay(100);
    hPosY += hVelY;
    }

    //If the dot went too far up or down
    if( ( hPosY < 0 ) || ( hPosY + HERO_HEIGHT > 400 ) )
    {
        //Move back
        hPosY -= hVelY;
    }
}

void Hero::heroRender()
{
	SDL_Rect* currentClip = &playerCurrentFrame[frame/8];
    playerCurrentTex->render(hPosX, hPosY, currentClip);
    frame++;
    cout << frame << endl;
	if( frame/8 >= PLAYER_FRAMES ) frame = 0;

}
