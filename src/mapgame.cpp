#include "mapgame.h"

#include <fstream>

#include "Box.h"
#include "Game.h"
#include "find_res.h"

int** MapGame::level0 = nullptr;

void MapGame::preLoadMap() {
    // load the map
    ifstream file(FindRes::getPath("map", "level0.smap"));
    level0 = new int*[Game::GRID_HEIGHT];
    for (int i = 0; i < Game::GRID_HEIGHT; i++) {
        level0[i] = new int[Game::GRID_WIDTH];
        for (int j = 0; j < Game::GRID_WIDTH; j++) {
            file >> level0[i][j];
            if (level0[i][j] == 5) {
                Box::layerBox[i][j] = new Box(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH);
                Box::boxCount++;
            }
        }
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
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 25; j++) {
            switch (level0[i][j]) {
                case 1:
                    wall1.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
                case 2:
                    wall2.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
                case 3:
                    wall3.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
                case 5:
                case 10:
                case 12:
                    nen1.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
                case 0:
                    nen2.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
                case 13:
                    nen3.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
                case 20:
                    gate.render(j * Game::BLOCK_WIDTH, i * Game::BLOCK_WIDTH, nullptr, &des0);
                    break;
            }
        }
    }
}
