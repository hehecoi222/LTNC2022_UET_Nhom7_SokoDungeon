#include "Game.h"
#include "Texture.h"


class Dot
{
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void dotHandleEvent( SDL_Event& e );

		//Moves the dot
		void dotMove();

		//Shows the dot on the screen
		void dotRender(LTexture &dot, SDL_Rect *clip);

		int getX(){return mPosX;}
		int getY(){return mPosY;}


    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};

