#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include "find_res.h"
#include "Texture.h"
static LTexture Map00;
class MapGame
{
public:
    //load the map
    void LoadMap();
    //destination of walls,...
    SDL_Rect Getdes0();

private:
    SDL_Rect des0;
};


#endif // MAP_H_INCLUDED
