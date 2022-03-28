#include "Box.h"

Box::Box() {
    mPosX = 100;
    mPosY = 100;

    mVelX = 0;
    mVelY = 0;
}

void Box::boxMove() {
    //Move the box left or right
    mPosX += mVelX;

    //If the box went too far to the left or right
    if( mPosX < 0 || mPosX > 800 )
    {
        //Move back
        mPosX -= mVelX;
    }

    //Move the box up or down
    mPosY += mVelY;

    //If the box went too far up or down
    if( mPosY < 0 || mPosY > 640 )
    {
        //Move back
        mPosY -= mVelY;
    }
}

void Box::boxRender(LTexture &box, SDL_Rect *clip) {
    box.render( mPosX, mPosY, clip );
}
