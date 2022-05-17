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
    // set map
    void setMap(int curMap) { current_map = curMap; };
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
    LTexture floor[3];
    //Draw the wall
    LTexture wall[3];
    //Draw goal position of the box to win 
    LTexture Goal;
    // Render goal position
    void goalClicked(int gridX, int gridY);
    //Draw Victory image
    LTexture Victory;
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
