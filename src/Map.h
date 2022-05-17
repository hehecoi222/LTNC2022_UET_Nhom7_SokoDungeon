#ifndef Map_H_INCLUDED
#define Map_H_INCLUDED
#include "find_res.h"
#include "Texture.h"

class Map
{
public:
    //The dimensions of the map
    static const int GRID_BLOCK_WIDTH = 32;
    Map();
    //load the map
    void LoadMap();
    //Load image, position of box, hero
    void preLoadMap();
    //Map level0
    static char** level0;
    //Change to the Next Map
    void NextMap();
    //Change to the Previous Map
    void PrevMap();
    //Current map of game
    int current_map;
    //name of the level
    string map;
    //Present Victory
    void PresVic();
    
private:    
    //destination x, y and width, height of the floor, wall, Goal
    SDL_Rect des0;
    //destination x, y and width, height of the Victory image
    SDL_Rect des1;
    //Draw the floor 
    Texture floor;
    //Draw the wall
    Texture wall;
    //Draw goal position of the box to win 
    Texture Goal;
    //Draw Victory image
    Texture Victory;
};

#endif // MAP_H_INCLUDED
