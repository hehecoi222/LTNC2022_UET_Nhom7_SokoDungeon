#include "Game.h"
#include "Texture.h"
#include "Dot.h"

SDL_Renderer* Game::gRenderer = nullptr;
TTF_Font* Game::gFont = nullptr;

LTexture DotTexture;
Dot dot;

//PlayerTexture
LTexture playerIdleDown;
const int PLAYER_FRAMES = 4;
SDL_Rect playerCurrentFrame[PLAYER_FRAMES];
int frame = 0;

//Map
LTexture Map;
SDL_Rect mapBlock;


Game::Game(){}
Game::~Game(){}

bool Game::init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_Mixer
				if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf( "SDL_Mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				}
			}
		}
	}
	return success;
}

bool Game::loadMedia(){

	bool success = true;

	Game::gFont = TTF_OpenFont("font/lazy.ttf", 28);
	SDL_Color textColor = {0, 0, 0, 255};

	DotTexture.loadFromFile("res/dot.bmp");

	playerIdleDown.loadFromFile("res/img/idown.png");
	for (int i = 0; i < PLAYER_FRAMES; i++)
	{
		playerCurrentFrame[i].x = i*64;
		playerCurrentFrame[i].y = 0;
		playerCurrentFrame[i].w = playerCurrentFrame[i].h = 64;
	}
	
	return success;

}

void Game::handleEvents(){

    //Event handler
    SDL_Event e;
	//Handle events on queue


	while( SDL_PollEvent( &e ) != 0 )
	{
		//User requests quit
		if( e.type == SDL_QUIT )
		{
			isRunning = false;
		}

		dot.dotHandleEvent(e);
		
	}
}
void Game::update(){
	dot.dotMove();
}

void Game::render(){
	//Clear screen
	SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );
	SDL_RenderClear( gRenderer );
	
	//render map
	Map.render(300,300, &mapBlock);

	//Render player
	SDL_Rect* currentClip = &playerCurrentFrame[frame/12];
	dot.dotRender(playerIdleDown, currentClip);
	//Update Screen
	SDL_RenderPresent( gRenderer );
	//Update frames
	frame++;
	if( frame/4 > PLAYER_FRAMES ) frame =0;

}
    
void Game::close(){

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	cout << "Game clear";
}
