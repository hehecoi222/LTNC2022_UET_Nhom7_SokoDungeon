#include "Game.h"
#include "Texture.h"

class Box {
public:
    //The dimensions of the box
    static const int BOX_WIDTH = 800/12;
    static const int BOX_HEIGHT = 640/12;

    //Maximum axis velocity of the box
    static const int BOX_VEL = 10;

    //Initializes the variables
    Box();

    //Moves the box
    void boxMove();

    //Shows the box on the screen
    void boxRender(LTexture &box, SDL_Rect *clip);

    int getX(){return mPosX;}
    int getY(){return mPosY;}

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};