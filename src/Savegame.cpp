#include "Savegame.h"

#include <fstream>

#include "Box.h"
#include "Enemy.h"
#include "Game.h"
#include "Hero.h"
#include "Map.h"

int Savegame::currentHighScore = 0;

    // Count how many moves
int Savegame::movesCount = 0;

Savegame::Savegame() {
    movesStack = nullptr;
    enemyStack = nullptr;
    mapSave = 0;
    tempBoxes = nullptr;
    heroX = heroY = 0;
}

Savegame::~Savegame() { clear(); }

// Function reverse print stack to file
void reversePrintStack(Node* stack, std::ostream& file) {
    if (stack == nullptr) return;
    reversePrintStack(stack->next, file);
    file << stack->direction << " ";
}

void Savegame::toFile(const char* filename) {
    std::ofstream fileSaveOut(filename);
    if (fileSaveOut.is_open()) {
        fileSaveOut << mapSave << " ";
        reversePrintStack(movesStack, fileSaveOut);
    }
    fileSaveOut.close();
}

void Savegame::setMap(Hero& hero, Enemy& enemy, Map& map) {
    map.setMap(mapSave);
    map.preLoadMap();
    hero.setpos();
    enemy.setCurX(Enemy::enemyGlobalPos.first);
    enemy.setCurY(Enemy::enemyGlobalPos.second);
}

void Savegame::loadSavefile(const char* filename, Hero& hero, Enemy& enemy,
                            Map& map) {
    std::ifstream fileSaveIn(filename);
    if (fileSaveIn.is_open()) {
        if (fileSaveIn >> mapSave) {
            setMap(hero, enemy, map);
        } else {
            mapSave = 0;
            setMap(hero, enemy, map);
        }
        while (!fileSaveIn.eof()) {
            int direction;
            if (fileSaveIn >> direction) {
                direction = checkCollisionwithMap(Map::level0, hero, direction);
                direction = enemy.checkCollisionWithThis(
                    hero.getCurX(), hero.getCurY(), direction);
                direction = Box::hitBox(hero, direction);
                hero.Move(direction);
                recordMove(direction);
                recordEnemyMove(enemy.Move(
                    enemy.findPathToHero(hero.getCurX(), hero.getCurY())));
            }
        }
    } else {
        mapSave = 0;
        setMap(hero, enemy, map);
    }
}

void Savegame::loadHighScore(const char* filename) {
    bool changed = false;
    std::ifstream fileHighScoreIn(filename);
    if (fileHighScoreIn.is_open()) {
        std::string map = "level" + std::to_string(mapSave) + ".smap";
        while (!fileHighScoreIn.eof()) {
            std::string temp;
            fileHighScoreIn >> temp;
            if (temp == map) {
                fileHighScoreIn >> currentHighScore;
                changed = true;
                break;
            }
        }
    }
    fileHighScoreIn.close();
    if (!changed) currentHighScore = 0;
}

void Savegame::compareHighScore(const char* filename) {
    if (currentHighScore > movesCount || currentHighScore == 0) {
        currentHighScore = movesCount;
    }
    std::ifstream fileHighScoreIn(filename);
    std::ofstream fileHighScoreOut(
        FindRes::getPath("savefile", "fileHighScoreNew.skbhsf"));
    std::string map = "level" + std::to_string(mapSave) + ".smap";
    bool isWritten = false;
    if (fileHighScoreIn.is_open()) {
        while (!fileHighScoreIn.eof()) {
            std::string mapName;
            int highScore;
            if (fileHighScoreIn >> mapName >> highScore) {
                if (mapName == map) {
                    fileHighScoreOut << mapName << " " << currentHighScore
                                     << std::endl;
                    isWritten = true;
                } else {
                    fileHighScoreOut << mapName << " " << highScore
                                     << std::endl;
                }
            }
        }
        if (!isWritten) {
            fileHighScoreOut << map << " " << currentHighScore << std::endl;
        }
    }
    fileHighScoreIn.close();
    fileHighScoreOut.close();
    remove(filename);
    rename(FindRes::getPath("savefile", "fileHighScoreNew.skbhsf"), filename);
}

void Savegame::clear() {
    while (movesStack) {
        while (movesStack->boxes) {
            NodeBox* temp = movesStack->boxes;
            movesStack->boxes = movesStack->boxes->next;
            delete temp;
        }
        Node* tmp = movesStack;
        movesStack = movesStack->next;
        delete tmp;
    }
    while (tempBoxes) {
        NodeBox* temp = tempBoxes;
        tempBoxes = tempBoxes->next;
        delete temp;
    }
    while (enemyStack) {
        Node* tmp = enemyStack;
        enemyStack = enemyStack->next;
        delete tmp;
    }
    movesStack = nullptr;
    tempBoxes = nullptr;
    enemyStack = nullptr;
    movesCount = 0;
}

void Savegame::boxPush(int x, int y) {
    NodeBox* box = new NodeBox;
    box->x = x;
    box->y = y;
    box->next = tempBoxes;
    tempBoxes = box;
}

void Savegame::push(int direction) {
    addMovesCount();
    Node* newNode = new Node;
    newNode->direction = direction;
    newNode->boxes = tempBoxes;
    tempBoxes = nullptr;
    newNode->next = movesStack;
    movesStack = newNode;
}

int Savegame::pop() {
    if (movesStack == nullptr) return 0;
    int direction = movesStack->direction;
    Node* temp = movesStack;
    movesStack = movesStack->next;
    delete temp;
    return direction;
}

void Savegame::popBoxes() {
    if (movesStack->boxes == nullptr) return;
    NodeBox* temp = movesStack->boxes;
    movesStack->boxes = movesStack->boxes->next;
    delete temp;
}

void Savegame::pushEnemy(int direction) {
    Node* newNode = new Node;
    newNode->direction = direction;
    newNode->boxes = nullptr;
    newNode->next = enemyStack;
    enemyStack = newNode;
}

int Savegame::popEnemy() {
    if (enemyStack == nullptr) return 0;
    int direction = enemyStack->direction;
    Node* temp = enemyStack;
    enemyStack = enemyStack->next;
    delete temp;
    return direction;
}

int Savegame::enemyUndoDirection(int direction) {
    switch (direction) {
        case NOT_MOVE:
            break;
        case MOVE_UP:
            return MOVE_DOWN;
        case MOVE_DOWN:
            return MOVE_UP;
        case MOVE_LEFT:
            return MOVE_RIGHT;
        case MOVE_RIGHT:
            return MOVE_LEFT;
    }
    return NOT_MOVE;
}

void Savegame::recordEnemyMove(int direction) {
    pushEnemy(direction);
}

void Savegame::recordMove(int direction) {
    currentHeroMove = direction;
    switch (direction) {
        case NOT_MOVE:
            break;
        case MOVE_UP:
            push(MOVE_UP);
            heroY--;
            break;
        case MOVE_DOWN:
            push(MOVE_DOWN);
            heroY++;
            break;
        case MOVE_LEFT:
            push(MOVE_LEFT);
            heroX--;
            break;
        case MOVE_RIGHT:
            push(MOVE_RIGHT);
            heroX++;
            break;
    }
}

void Savegame::undoMove(Hero& hero, Enemy& enemy) {
    int direction = (movesStack ? movesStack->direction : -1);
    switch (direction) {
        case NOT_MOVE:
            shift(hero, enemy, direction);
            break;
        case MOVE_UP:
            direction = MOVE_DOWN;
            shift(hero, enemy, direction);
            heroY++;
            break;
        case MOVE_DOWN:
            direction = MOVE_UP;
            shift(hero, enemy, direction);
            heroY--;
            break;
        case MOVE_LEFT:
            direction = MOVE_RIGHT;
            shift(hero, enemy, direction);
            heroX++;
            break;
        case MOVE_RIGHT:
            direction = MOVE_LEFT;
            shift(hero, enemy, direction);
            heroX--;
            break;
    }
    pop();
}

void Savegame::shift(Hero& hero, Enemy& enemy, int direction) {
    hero.Move(direction);
    if(direction != NOT_MOVE)
        subMovesCount();
    while (movesStack->boxes) {
        int boxX = movesStack->boxes->x;
        int boxY = movesStack->boxes->y;
        Box::layerBox[boxY][boxX]->Move(direction);
        popBoxes();
    }
    int enemyDirection = popEnemy();
    enemy.Move(enemyUndoDirection(enemyDirection));
    enemy.setState(enemyDirection);
}