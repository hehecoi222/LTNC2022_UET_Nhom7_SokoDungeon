#ifndef mapgame_H_INCLUDED
#define mapgame_H_INCLUDED
#include<SDL.h>
#include "Texture.h"
#include<vector>
#include<utility>
using namespace std;
class MapGame
{
    private:
        SDL_Rect des0;//destination x and y to render following by map
        LTexture wall1;//texture of wall
        LTexture floor;//texture of floor
        LTexture Goal;//texture of Goal to win the map
        
        //bool checkwin;
        int currentmap;
        string map;


    public:
        //The dimensions of the map
        static const int GRID_BLOCK_WIDTH = 32;
        
        //load the map
        void LoadMap();
        void preLoadMap();
        //Map level0
        static char** level0;
        MapGame();
        ~MapGame();
};
#endif