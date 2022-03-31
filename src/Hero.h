#ifndef Hero_h
#define Hero_h
#include "Game.h"
#include "Texture.h"
#include "find_res.h"


class Hero
{
    public:
		//The dimensions of the hero
		static const int HERO_WIDTH = 20;
		static const int HERO_HEIGHT = 20;

		//Maximum axis velocity of the HERO
		static const int HERO_VEL = 16;

		//Initializes the variables
		Hero();
		//load all the hero img
		void loadHeroIMG();

		//Takes key presses and adjusts the hero's velocity
		void heroHandleEvent( SDL_Event& e );

		//Moves the hero
		void heroMove();

		//Shows the hero on the screen
		void heroRender();

		//return hero position
		int getX(){return hPosX;}
		int getY(){return hPosY;}

		//current hero texture that will be rendered
		LTexture *playerCurrentTex = nullptr;
		//idle texture
		LTexture idleUp, idleDown, idleRight, idleLeft;
		//walking texture;
		LTexture walkUp, walkDown, walkRight, walkLeft;

		static const int PLAYER_FRAMES = 4;
		SDL_Rect playerCurrentFrame[PLAYER_FRAMES];
		int frame = 0;

    private:
		//The X and Y offsets of the hero
		int hPosX, hPosY;

		//The velocity of the hero
		int hVelX, hVelY;


};
#endif 
