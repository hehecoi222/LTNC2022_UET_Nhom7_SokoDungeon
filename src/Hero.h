#ifndef Hero_h
#define Hero_h
#include "Game.h"
#include "Texture.h"
#include "find_res.h"

class Hero
{
    public:
		//Initializes the variables
		Hero();

		//Deallocates memory
		~Hero();

		//Loads hero image
		void loadHeroIMG();

		//Takes key presses and adjusts the hero's velocity
		int heroHandleEvent( SDL_Event& e );

		//Moves the hero according to key
		void Move(int direction);

		//Renders the hero on the screen
		void heroRender();

		//Returns hero current position
		int getCurX(){return hCurPosX;}
		int getCurY(){return hCurPosY;}

		//Current rendered hero texture 
		Texture *playerCurrentTex;

		//Hero directions
		enum {
			NOT_MOVE, 
			MOVE_UP,
			MOVE_DOWN,
			MOVE_LEFT,
			MOVE_RIGHT
		};

    private:
		//The dimensions of the hero
		static const int HERO_WIDTH = Game::BLOCK_WIDTH;
		static const int HERO_HEIGHT = Game::BLOCK_WIDTH;

		//Hero animation sprites's size
		const int SPRITE_WIDTH = 64;
		const int SPRITE_HEIGHT = 64;

		//Maximum axis velocity of the HERO
		static const int HERO_VEL = 32;

		//The X and Y offsets of the hero
		int hCurPosX, hCurPosY;

		//The hero position after moving
		int hDesPosX, hDesPoxY;

		//Idle textures
		Texture idleUp, idleDown, idleRight, idleLeft;

		//Walking textures
		Texture walkUp, walkDown, walkRight, walkLeft;

		//Hero rendered destination rect
		SDL_Rect hDestRect;

		//Player sprites frames
		static const int PLAYER_FRAMES = 4;
		SDL_Rect playerCurrentFrame[PLAYER_FRAMES];
		int frame = 0;
};

#endif 
