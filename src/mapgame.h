#ifndef mapgame_H_INCLUDED
#define mapgame_H_INCLUDED
#include "find_res.h"
#include "Texture.h"

class MapGame
{
public:
    //The dimensions of the map
    static const int GRID_BLOCK_WIDTH = 32;
    MapGame();
    //load the map
    void LoadMap();
    //Load image, position of box, hero
    void preLoadMap();
    //Map level0
    static char** level0;
    //Change to the Next Map
    void NextMap();
    //Change to the previous Map
    void PrevMap();
    //Current map of game
    int currentmap;
    //name of the level
    string map;
    
private:    
    //destination to render
    SDL_Rect des0;

    //Draw the floor 
    LTexture floor;

    //Draw the wall
    LTexture wall;

    //Draw goal position of the box to win 
    LTexture Goal;

    
};

#endif // MAP_H_INCLUDED
