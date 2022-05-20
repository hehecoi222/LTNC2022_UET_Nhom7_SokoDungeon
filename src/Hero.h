#ifndef Hero_h
#define Hero_h
#include "Game.h"
#include "Texture.h"
#include "Enemy.h"
#include "find_res.h"
#include <utility>
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
		int heroHandleEvent( SDL_Event& e, Enemy& mainEnemy );

		//Moves the hero according to key
		void Move(int direction);

		//Renders the hero on the screen
		void heroRender();

		//Returns hero current position
		int getCurX(){return hCurPosX;}
		int getCurY(){return hCurPosY;}

		//current hero texture that will be rendered
		Texture *playerCurrentTex = &idleUp;

		//Hero directions
		enum {
			NOT_MOVE, 
			MOVE_UP,
			MOVE_DOWN,
			MOVE_LEFT,
			MOVE_RIGHT
		};


		//Initial Position of Hero
		static std::pair<int, int> pos;
		//set position for each level
		void setpos();
    private:
		//The dimensions of the hero
		const int HERO_WIDTH = Game::BLOCK_WIDTH;
		const int HERO_HEIGHT = Game::BLOCK_WIDTH;

		//Hero animation sprites's size
		const int HERO_CLIP_WIDTH = 64;

		//Maximum axis velocity of the HERO
		const int HERO_VEL = 32;

		//The X and Y offsets of the hero
		int hCurPosX, hCurPosY;

		//The hero destination position after moving
		int hDesPosX, hDesPosY;

		//Idle textures
		Texture idleUp, idleDown, idleRight, idleLeft;

		//Walking textures
		Texture walkUp, walkDown, walkRight, walkLeft;

		//Hero rendered destination rect
		SDL_Rect playerRectDest;

		//Player sprites frames
		static const int PLAYER_FRAMES = 4;
		SDL_Rect playerCurrentFrame[PLAYER_FRAMES];
		int frame = 0;
};

#endif 
