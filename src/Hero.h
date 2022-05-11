#ifndef Hero_h
#define Hero_h
#include "Game.h"
#include "Texture.h"
#include "find_res.h"
#include "utility"
class Hero
{
    public:
		//The dimensions of the hero
		static const int HERO_WIDTH = 32;
		static const int HERO_HEIGHT = 32;

		//Maximum axis velocity of the HERO
		static const int HERO_VEL = 4;

		//Initializes the variables
		Hero();
		~Hero();

		//Load hero img
		void loadHeroIMG();

		//Takes key presses and adjusts the hero's velocity
		int heroHandleEvent( SDL_Event& e );

		//Moves the hero according to key
		void Move(int direction);

		//Shows the hero on the screen
		void heroRender();

		//Return hero current position
		int getCurX(){return hCurPosX;}
		int getCurY(){return hCurPosY;}

		//idle texture
		LTexture idleUp, idleDown, idleRight, idleLeft;

		//walking texture;
		LTexture walkUp, walkDown, walkRight, walkLeft;

		//current hero texture that will be rendered
		LTexture *playerCurrentTex = &idleUp;

		//Hero directions
		enum {
			NOT_MOVE,
			MOVE_UP,
			MOVE_DOWN,
			MOVE_LEFT,
			MOVE_RIGHT
		};

		//player sprites frames
		static const int PLAYER_FRAMES = 4;
		SDL_Rect playerCurrentFrame[PLAYER_FRAMES];
		int frame = 0;

		//Initial Position of Hero
		static int pos_x;
		static int pos_y;
		//set position for each level
		void setpos();
    private:

		//The X and Y offsets of the hero
		int hCurPosX, hCurPosY;

		//The hero destination position after moving
		int hDesPosX, hDesPosY;

		//The velocity of the hero
		int hVelX, hVelY;

		//Hero state;
		bool isMoving = false;
		bool isAlive = true;

		SDL_Rect playerRectDest;

};
#endif 
