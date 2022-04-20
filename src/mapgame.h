#ifndef mapgame_H_INCLUDED
#define mapgame_H_INCLUDED
#include "find_res.h"
#include "Texture.h"

class MapGame
{
public:
    //load the map
    void LoadMap();
    void preLoadMap();
    //Map level0
    static int** level0;
private:    
    //destination to render
    SDL_Rect des0;

    //ve nen
    LTexture nen1;
    LTexture nen2;
    LTexture nen3;


    //ve tuong
    LTexture wall1;
    LTexture wall2;
    LTexture wall3;

    //ve cong
    LTexture gate;

    //ve chest
    LTexture chest;
};

#endif // MAP_H_INCLUDED
