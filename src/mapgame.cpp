#include "mapgame.h"
#include <fstream>
#include "Box.h"
#include "find_res.h"
using namespace std;
#include<iostream>

char** MapGame::level0 = nullptr;
MapGame::MapGame()
{
    currentmap = 0;
    map = "level0.smap";
    des0.x = des0.y = 0;
    des0.w = des0.h = GRID_BLOCK_WIDTH;
}

MapGame::~MapGame()
{};
void MapGame::preLoadMap()
{
    ifstream file(FindRes::getPath("map", "level0.smap"));
    level0 = new char*[15];
    for (int i = 0; i < 15; i++) {
        level0[i] = new char[15];
        for (int j = 0; j < 15; j++) {
            file >> level0[i][j];
            if (level0[i][j] == '$') {
                Box::layerBox[i][j] = new Box(j * Box::BLOCK_WIDTH, i * Box::BLOCK_WIDTH);
                Box::boxCount++;
            }
        }
    }
}


void MapGame::LoadMap()
{
    for(int i = 0;i<15;i++)
    {
        for(int j = 0 ;j<15;j++)
        {
            switch(level0[i][j])
            {
            case '#':
                wall1.render(j*GRID_BLOCK_WIDTH,i*GRID_BLOCK_WIDTH,nullptr, &des0);
                break;
            case ' ':
                floor.render(j*GRID_BLOCK_WIDTH, i*GRID_BLOCK_WIDTH,nullptr, &des0);
                break;
            case '.':
                Goal.render(j*GRID_BLOCK_WIDTH, i*GRID_BLOCK_WIDTH,nullptr, &des0);
                break;
            
            }
        }
    }
}
