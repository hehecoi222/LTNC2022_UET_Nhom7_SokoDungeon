#include "mapgame.h"

#include <fstream>

#include "Box.h"
#include "Game.h"
#include "find_res.h"

char** MapGame::level0 = nullptr;

void MapGame::preLoadMap() {
    // load the map
    ifstream file(FindRes::getPath("map", "level0.smap"));
    level0 = new char*[Game::GRID_HEIGHT];
    for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        level0[i] = new char[Game::GRID_WIDTH];
        for (int j = 0; j < Game::GRID_WIDTH; j++) {
            file.read(&level0[i][j],1);
            if (level0[i][j] == '$') {
                Box::layerBox[i][j] = new Box(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH);
                Box::boxCount++;
            }
        }
        char temp;
        file.read(&temp, 1);
    }
    file.close();
    // load nen
    des0.x = des0.y = 0;
    des0.w = des0.h = Game::BLOCK_WIDTH;
    wall1.loadFromFile(FindRes::getPath("img", "wall1.png"));
    wall2.loadFromFile(FindRes::getPath("img", "wall2.png"));
    wall3.loadFromFile(FindRes::getPath("img", "wall3.png"));
    nen1.loadFromFile(FindRes::getPath("img", "nen1.png"));
    nen2.loadFromFile(FindRes::getPath("img", "nen2.png"));
    nen3.loadFromFile(FindRes::getPath("img", "nen3.png"));
    gate.loadFromFile(FindRes::getPath("img", "gate.png"));
    chest.loadFromFile(FindRes::getPath("img", "chest.png"));
}

void MapGame::LoadMap() {
    for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        for (int j = 0; j < Game::GRID_WIDTH; j++) {
            switch (level0[i][j]) {
                case '#':
                    wall1.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
                case '$':
                case ' ':
                    nen1.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
            }
        }
    }
}
