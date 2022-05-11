#include "Texture.h"
Texture::Texture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture()
{
	//Deallocate
	free();
}

bool Texture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGBA( loadedSurface->format, 0xFF,0xFF,0xFF,255 ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Game::gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderText( string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(Game::gFont, textureText.c_str(), textColor);
	if( textSurface == NULL )
	{
		printf(" Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface( Game::gRenderer, textSurface);
		if( mTexture == NULL )
		{
			printf("Unable to create texture form rendered text! SDL error: %s\n", SDL_GetError());
		}
		else{
			mWidth = textSurface->w;
			mHeight = textSurface->h;

		}

		//get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	return mTexture!= NULL;
}
#endif

void Texture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::render( int x, int y, SDL_Rect* clip, SDL_Rect* dest, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	if (dest == NULL) dest = new SDL_Rect{x, y, mWidth, mHeight};
	dest->x = x;  
	dest->y = y; 
	//Render to screen
	SDL_RenderCopyEx( Game::gRenderer, mTexture, clip, dest, angle, center, flip );
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}

void Texture::setBlendMode( SDL_BlendMode blending){
	SDL_SetTextureBlendMode( mTexture, blending);
}

void Texture::setAlpha( Uint8 alpha){
	SDL_SetTextureAlphaMod( mTexture, alpha);
}