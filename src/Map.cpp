#include "Map.h"
#include <fstream>

#include "Box.h"
#include "Game.h"
#include "Hero.h"
#include "find_res.h"

char** Map::level0 = nullptr;
int Map::current_map = 0;
Map::Map()
{
    //Initialize variable of the level0
    map = "level0.smap";
    // destination x, y position of the image to render
    des0.x = des0.y = 0;
    des0.w = des0.h = Game::BLOCK_WIDTH;
}
void Map::preLoadMap() {
    clear();
    // load the current map
    map[5] = current_map + '0';
    // using file operation to load
    ifstream file(FindRes::getPath("map", map));
    level0 = new char*[Game::GRID_HEIGHT];
    for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        level0[i] = new char[Game::GRID_WIDTH];
        for (int j = 0; j < Game::GRID_WIDTH; j++) {
            file.read(&level0[i][j], 1);
            if (level0[i][j] == '$') {
                Box::layerBox[i][j] =
                    new Box(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH);
                Box::boxCount++;
            }
            else if(level0[i][j] == '@')
            {
                Hero::pos.first = j * Game::BLOCK_WIDTH;
                Hero::pos.second = i * Game::BLOCK_WIDTH;
            } else if(level0[i][j] == '&') {
                Enemy::setEnemyGlobalPos(j * Game::BLOCK_WIDTH,
                                         i * Game::BLOCK_WIDTH);
            }
        }
        char temp;
        file.read(&temp, 1);
        // file.read(&temp, 1);
    }
    file.close();
    // load image from folder img
    wall[0].loadFromFile(FindRes::getPath("img", "wall1.png"));
    wall[1].loadFromFile(FindRes::getPath("img", "wall2.png"));
    wall[2].loadFromFile(FindRes::getPath("img", "wall3.png"));
    floor[0].loadFromFile(FindRes::getPath("img", "nen1.png"));
    floor[1].loadFromFile(FindRes::getPath("img", "nen2.png"));
    floor[2].loadFromFile(FindRes::getPath("img", "nen3.png"));
    Goal.loadFromFile(FindRes::getPath("img", "Goal.png"));
}

void Map::LoadMap() {
   
   for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        for (int j = 0; j < Game::GRID_WIDTH; j++) {
            switch (level0[i][j]) {
                case '#':
                    wall[(i + j) % 3].render(j * Game::BLOCK_WIDTH,
                                              i * Game::BLOCK_WIDTH, nullptr,
                                              &des0);
                    break;
                case ' ':
                case '$':
                case '@':
                case '&':
                    floor[(i + j) % 3].render(j * Game::BLOCK_WIDTH,
                                               i * Game::BLOCK_WIDTH, nullptr,
                                               &des0);
                    break;
                case '.':
                    floor[(i + j) % 3].render(j * Game::BLOCK_WIDTH,
                                               i * Game::BLOCK_WIDTH, nullptr,
                                               &des0);
                    goalClicked(j, i);
                    break;
            }
        }
    }
}

void Map::goalClicked(int gridX, int gridY) {
    SDL_Rect clip{0, 0, 16, 16};
    if (Box::layerBox[gridY][gridX] != nullptr) {
        clip.x = 16;
    }
    Goal.render(gridX * Game::BLOCK_WIDTH, gridY * Game::BLOCK_WIDTH, &clip,
                &des0);
}

void Map::NextMap()
{
    if(current_map < 5)
    //increase the map level
        current_map++;
    clear();
}

void Map::PrevMap()
{
    if(current_map > 0)
    //Decrease the map level
    current_map--;
    clear();
}

void Map::clear() {
    if (!level0) {
        return;
    }
    for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        delete[] level0[i];
    }
    delete[] level0;
    level0 = nullptr;
    Box::flushBoxLayer();
}