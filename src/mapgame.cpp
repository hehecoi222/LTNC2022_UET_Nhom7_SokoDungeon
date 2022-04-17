#include "mapgame.h"

#include <fstream>

#include "Box.h"
#include "find_res.h"

void MapGame::LoadMap() {
    // load the map
    ifstream file(FindRes::getPath("map", "level0.smap"));
    level0 = new int*[20];
    for (int i = 0; i < 20; i++) {
        level0[i] = new int[25];
        for (int j = 0; j < 25; j++) {
            file >> level0[i][j];
        }
    }
    file.close();
    // load nen
    des0.x = des0.y = 0;
    des0.w = des0.h = 32;
    wall1.loadFromFile(FindRes::getPath("img", "wall1.png"));
    wall2.loadFromFile(FindRes::getPath("img", "wall2.png"));
    wall3.loadFromFile(FindRes::getPath("img", "wall3.png"));
    nen1.loadFromFile(FindRes::getPath("img", "nen1.png"));
    nen2.loadFromFile(FindRes::getPath("img", "nen2.png"));
    nen3.loadFromFile(FindRes::getPath("img", "nen3.png"));
    gate.loadFromFile(FindRes::getPath("img", "gate.png"));
    chest.loadFromFile(FindRes::getPath("img", "chest.png"));
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 25; j++) {
            switch (level0[i][j]) {
                case 1:
                    wall1.render(j * 32, i * 32, nullptr, &des0);
                    break;
                case 2:
                    wall2.render(j * 32, i * 32, nullptr, &des0);
                    break;
                case 3:
                    wall3.render(j * 32, i * 32, nullptr, &des0);
                    break;
                case 12:
                    nen1.render(j * 32, i * 32, nullptr, &des0);
                    break;
                case 0:
                    nen2.render(j * 32, i * 32, nullptr, &des0);
                    break;
                case 13:
                    nen3.render(j * 32, i * 32, nullptr, &des0);
                    break;
                case 20:
                    gate.render(j * 32, i * 32, nullptr, &des0);
                    break;
            }
        }
    }
}
