#include "Dot.h"

Dot::Dot()
{
    mPosX = 100;
    mPosY = 100;

    mVelX = 0;
    mVelY = 0;
}

void Dot::dotHandleEvent( SDL_Event &e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::dotMove(){
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if( mPosX < 0 || mPosX > 800 )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( mPosY < 0 || mPosY > 640 )
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Dot::dotRender(LTexture &dot, SDL_Rect *clip)
{
    dot.render(mPosX, mPosY, clip);
    cout << "Rendering..." <<endl;
}
