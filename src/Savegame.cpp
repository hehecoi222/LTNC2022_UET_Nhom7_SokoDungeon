#include "Savegame.h"

#include "Box.h"
#include "Hero.h"
#include "mapgame.h"

Savegame::Savegame() {
    movesStack = nullptr;
    tempBoxes = nullptr;
    heroX = heroY = 0;
}

Savegame::~Savegame() {
    clear();
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
    movesStack = nullptr;
    tempBoxes = nullptr;
}

void Savegame::boxPush(int x, int y) {
    NodeBox* box = new NodeBox;
    box->x = x;
    box->y = y;
    box->next = tempBoxes;
    tempBoxes = box;
}

void Savegame::push(int direction) {
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

void Savegame::recordMove(int direction) {
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

void Savegame::undoMove(Hero& hero) {
    int direction = (movesStack ? movesStack->direction : 0 );
    switch (direction) {
        case NOT_MOVE:
            break;
        case MOVE_UP:
            direction = MOVE_DOWN;
            shift(hero, direction);
            heroY++;
            break;
        case MOVE_DOWN:
            direction = MOVE_UP;
            shift(hero, direction);
            heroY--;
            break;
        case MOVE_LEFT:
            direction = MOVE_RIGHT;
            shift(hero, direction);
            heroX++;
            break;
        case MOVE_RIGHT:
            direction = MOVE_LEFT;
            shift(hero, direction);
            heroX--;
            break;
    }
    pop();
}

void Savegame::shift(Hero& hero, int direction) {
    hero.Move(direction);
    while (movesStack->boxes) {
        int boxX = movesStack->boxes->x;
        int boxY = movesStack->boxes->y;
        Box::layerBox[boxY][boxX]->Move(direction);
        popBoxes();
    }
}