#include "Map.h"
#include <fstream>

#include "Box.h"
#include "find_res.h"
#include "Hero.h"


char** Map::level0 = nullptr;
Map::Map()
{
    //Initialize variable of the level0
    current_map = 0;
    map = "level0.smap";
    //destination x, y position of the image to render
    des0.x = des0.y = 0;
    des0.w = des0.h = GRID_BLOCK_WIDTH;    
}
void Map::preLoadMap() {
    // load the current map
    switch(current_map)
    {
        case 0:
            map[5] = '0';
            break;
        case 1:
            map[5] = '1';
            break;
        case 2:
            map[5] = '2';
            break;
        case 3:
            map[5] = '3';
            break;
        case 4:
            map[5] = '4';
            break;
        case 5:
            map[5] = '5';
            break;
    }
    //using file operation to load
    ifstream file(FindRes::getPath("map", map));
    level0 = new char*[15];
    for (int i = 0; i < 15; i++) {
        level0[i] = new char[15];
        for (int j = 0; j < 15; j++) {
            file.read(&level0[i][j], 1);
            if (level0[i][j] == '$') {
                Box::layerBox[i][j] = new Box(j * Box::BOX_WIDTH, i * Box::BOX_WIDTH);
                Box::boxCount++;
            }
            else if(level0[i][j] == '@')
            {
                Hero::pos.first = j * GRID_BLOCK_WIDTH;
                Hero::pos.second = i * GRID_BLOCK_WIDTH;
            }
        }
        char temp;
        file.read(&temp, 1);
    }
    file.close();
    //load image from folder img
    wall.loadFromFile(FindRes::getPath("img", "wall1.png"));
    floor.loadFromFile(FindRes::getPath("img", "nen1.png"));
    Goal.loadFromFile(FindRes::getPath("img", "Goal.png"));
}

void Map::LoadMap() {
   
   for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            switch (level0[i][j]) {
                case '#': 
                    wall.render(j * GRID_BLOCK_WIDTH, i * GRID_BLOCK_WIDTH, nullptr, &des0);
                    break;
                case ' ': case '$': case '@':
                    floor.render(j * GRID_BLOCK_WIDTH, i * GRID_BLOCK_WIDTH, nullptr, &des0);
                    break;
                case '.':
                    Goal.render(j*GRID_BLOCK_WIDTH, i*GRID_BLOCK_WIDTH, nullptr, &des0);
                    break;
            }
        }
    }
}

void Map::NextMap()
{
    //increase the map level
    current_map++;
    cout<<current_map;
}

void Map::PresVic()
{
    des1.x = des1.y = 0;
    des1.w = des1.h = GRID_BLOCK_WIDTH * 15;
    Victory.loadFromFile(FindRes::getPath("img", "Victory.png"));
    Victory.render(0, 0, nullptr, &des1);
}