#include"mapgame.h"
#include "Box.h"

Box **setBox = new Box *[3];

int level0[20][25] = {
    {3, 2, 1, 1, 3, 1, 1, 1, 2, 1, 3, 3, 20, 1, 2, 1, 1, 3, 1, 3, 1, 2, 1, 1, 3},
    {1, 0, 12, 13, 12, 0, 12, 13, 12, 12, 0, 13, 0, 0, 12, 0, 12, 0, 12, 0, 13, 0, 12, 0, 1},
    {1, 0, 12, 0 , 12, 0, 13, 0, 12, 0, 0, 13, 0, 0, 0, 13, 0, 0, 13, 0, 0, 12, 12, 0, 2},
    {3, 0, 0, 13, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 12, 0, 0, 1},
    {1, 0, 12, 0, 12, 0, 13, 0, 0, 13, 0, 0, 0, 12, 0, 12, 0, 0, 12, 0, 13, 0, 13, 0, 1},
    {2, 0, 0, 12, 0, 0, 0, 0, 12, 0, 12, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 13, 0, 0, 3},
    {1, 0, 12, 0, 13, 0, 12, 0, 0, 13, 0, 0, 13, 0, 13, 0, 13, 0, 12, 0, 13, 0, 13, 0, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 13, 0, 10, 0, 13, 0, 0, 0, 0, 0, 2},
    {1, 0, 0, 0, 13, 0, 0, 0, 12, 0, 0, 0, 12, 10, 0, 0, 12, 0, 0, 0, 13, 0, 0, 0, 1},
    {2, 0, 13, 0, 12, 0, 13, 0, 0, 13, 0, 0, 12, 0, 0, 0, 0, 0, 0, 13, 0, 12, 0, 0, 1},
    {1, 0, 0, 0, 0, 12, 0, 13, 0, 0, 12, 0, 0, 13, 0, 12, 0, 0, 13, 0, 0, 12, 0, 0, 1},
    {2, 0, 0, 12, 0, 0, 0, 0, 10, 13, 0, 0, 12, 0, 0, 12, 0, 0, 12, 0, 0, 13, 0, 0, 3},
    {1, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 12, 0, 0, 0, 2},
    {3, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 12, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 13, 0, 13, 0, 0, 0, 0, 0, 12, 0, 13, 0, 0, 0, 0, 13, 0, 0, 12, 0, 0, 2},
    {3, 0, 13, 0, 0, 13, 0, 0, 13, 0, 0, 12, 0, 0, 12, 0, 0, 13, 0, 0, 13, 0, 0, 0, 1},
    {1, 0, 0, 12, 0, 0, 12, 0, 0, 0, 12, 0, 0, 0, 13, 0, 12, 0, 12, 0, 0, 0, 13, 0, 1},
    {3, 0, 12, 0, 12, 0, 0, 0, 0, 13, 0, 12, 0, 13, 0, 13, 0, 12, 0, 13, 0, 13, 0, 0, 2},
    {1, 0, 0, 0, 13, 0, 0, 13, 0, 0, 12, 0, 0, 13, 0, 0, 13, 0, 0, 12, 0, 12, 0, 0, 1},
    {2, 1, 2, 1, 1, 3, 1, 2, 1, 2, 1, 2, 1, 3, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 3},
};


void MapGame::LoadMap()
{
    Box::loadBoxIMG();
    int boxCount = 0;
    //load nen
    des0.x = des0.y = 0;
    des0.w = des0.h = 32;
    wall1.loadFromFile(FindRes::getPath("img","wall1.png"));
    wall2.loadFromFile(FindRes::getPath("img","wall2.png"));
    wall3.loadFromFile(FindRes::getPath("img","wall3.png"));
    nen1.loadFromFile(FindRes::getPath("img","nen1.png"));
    nen2.loadFromFile(FindRes::getPath("img","nen2.png"));
    nen3.loadFromFile(FindRes::getPath("img","nen3.png"));
    gate.loadFromFile(FindRes::getPath("img","gate.png"));
    chest.loadFromFile(FindRes::getPath("img","chest.png"));
	for(int i=0;i<20;i++)
    {
        for(int j=0;j<25;j++)
        {
            switch(level0[i][j])
            {
                case 1:
                wall1.render(j*32,i*32,nullptr, &des0);
                break;
                case 2:
                wall2.render(j*32,i*32, nullptr, &des0);
                break;
                case 3:
                wall3.render(j*32,i*32, nullptr, &des0);
                break;
                case 12:
                nen1.render(j*32,i*32, nullptr, &des0);
                break;
                case 0:
                nen2.render(j*32,i*32, nullptr, &des0);
                break;
                case 13:
                nen3.render(j*32,i*32, nullptr, &des0);
                break;
                case 20:
                gate.render(j*32,i*32, nullptr, &des0);
                break;
                case 10:
                nen2.render(j*32,i*32, nullptr, &des0);
                setBox[boxCount] = new Box(j*32,i*32);
                setBox[boxCount]->boxRender();
                boxCount++;
                break;
            }

        }
    }
}



