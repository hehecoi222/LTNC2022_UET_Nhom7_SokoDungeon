#ifndef mapgame_H_INCLUDED
#define mapgame_H_INCLUDED
#include "find_res.h"
#include "Texture.h"

class MapGame
{
public:
    MapGame();
    //load the map
    void LoadMap();
    //Load image, position of box, hero
    void preLoadMap();
    //Map level0
    static char** level0;
    //Change to the Next Map
    void NextMap();
    //Current map of game
    int current_map;
    //name of the level
    string map;
    //Present Victory
    void PresVic();

    // clear map
    void clear();
    
private:    
    //destination x, y and width, height of the floor, wall, Goal
    SDL_Rect des0;
    //destination x, y and width, height of the Victory image
    SDL_Rect des1;
    //Draw the floor 
    LTexture floor;
    //Draw the wall
    LTexture wall;
    //Draw goal position of the box to win 
    LTexture Goal;
    //Draw Victory image
    LTexture Victory;
};

#endif // MAP_H_INCLUDED
