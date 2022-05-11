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
    static char** level0;
private:    
    //destination to render
    SDL_Rect des0;

    //ve nen
    Texture nen1;
    Texture nen2;
    Texture nen3;


    //ve tuong
    Texture wall1;
    Texture wall2;
    Texture wall3;

    //ve cong
    Texture gate;

    //ve chest
    Texture chest;
};

#endif // MAP_H_INCLUDED
