#ifndef Map_H_INCLUDED
#define Map_H_INCLUDED
#include "find_res.h"
#include "Texture.h"

class Map
{
public:
    Map();
    //load the map
    void LoadMap();
    // set map
    void setMap(int curMap) { current_map = curMap; };
    //Load image, position of box, hero
    void preLoadMap();
    //Map level0
    static char** level0;
    //Change to the Next Map
    void NextMap();
    //Change to the Previous Map
    void PrevMap();
    //Current map of game
    static int current_map;
    //name of the level
    string map;
    // clear map
    void clear();
    
private:    
    //destination x, y and width, height of the floor, wall, Goal
    SDL_Rect des0;
    //Draw the floor 
    Texture floor[3];
    //Draw the wall
    Texture wall[3];
    //Draw goal position of the box to win 
    Texture Goal;
    // Render goal position
    Texture Victory;
    //Render 
    void goalClicked(int gridX, int gridY);
};

template <class T> int checkCollisionwithMap(char** level, T& obj, int direction) {
    if (direction == obj.NOT_MOVE) return direction;
    int objX = obj.getCurX()/Game::BLOCK_WIDTH;
    int objY = obj.getCurY()/Game::BLOCK_WIDTH;
    switch (direction) {
        case obj.MOVE_LEFT:
            objX--;
            break;
        case obj.MOVE_RIGHT:
            objX++;
            break;
        case obj.MOVE_UP:
            objY--;
            break;
        case obj.MOVE_DOWN:
            objY++;
            break;
        default:
            return direction;
    }
    switch (level[objY][objX]) {
        case '#':
            return obj.NOT_MOVE;
            break;
        default:
            return direction;
    }
}

#endif // MAP_H_INCLUDED
