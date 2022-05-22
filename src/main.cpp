#include "Game.h"

Game *game = nullptr;

int main( int argc, char* args[] ){
	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	if(!game->init())
	{
		cout << "Failed to init window" << endl;
	}
	else
	{
		if(!game->loadMedia())
		{
			cout << "Failed to load Media" << endl;
		}
		else
		{
			while (game->getGameState())
			{
				frameStart = SDL_GetTicks();

				game->handleEvents();
				game->update();
				game->render();

				frameTime = SDL_GetTicks() - frameStart;

				if(frameDelay > frameTime){
					SDL_Delay(frameDelay - frameTime );
				}
			}
		}

	}
	game->close();
	return 0;
}