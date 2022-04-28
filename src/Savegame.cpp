#include "Savegame.h"

#include "Box.h"
#include "Hero.h"
#include "mapgame.h"

Savegame::Savegame() { movesStack = nullptr; }

Savegame::~Savegame() {
    while (movesStack) {
        Node* tmp = movesStack;
        movesStack = movesStack->next;
        delete tmp;
    }
}

void Savegame::push(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = movesStack;
    movesStack = newNode;
}

int Savegame::pop() {
    if (movesStack == nullptr) return 0;
    int data = movesStack->data;
    Node* temp = movesStack;
    movesStack = movesStack->next;
    delete temp;
    return data;
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
    int direction = pop();
    switch (direction) {
        case NOT_MOVE:
            break;
        case MOVE_UP:
            direction = MOVE_DOWN;
            shiftDown(hero);
            break;
        case MOVE_DOWN:
            direction = MOVE_UP;
            shiftUp(hero);
            break;
        case MOVE_LEFT:
            direction = MOVE_RIGHT;
            shiftRight(hero);
            break;
        case MOVE_RIGHT:
            direction = MOVE_LEFT;
            shiftLeft(hero);
            break;
    }
}

void Savegame::shiftUp(Hero& hero) {
    hero.Move(MOVE_UP);
    int i;
    for (i = heroY + 1; i < 20; i++) {
        if (!Box::layerBox[i][heroX]) {
            break;
        }
    }
    for (int j = heroY + 1; j < i; j++) {
        Box::layerBox[j][heroX]->Move(MOVE_UP);
    }
    heroY--;
}

void Savegame::shiftDown(Hero& hero) {
    hero.Move(MOVE_DOWN);
    int i;
    for (i = heroY - 1; i >= 0; i--) {
        if (!Box::layerBox[i][heroX]) {
            break;
        }
    }
    for (int j = heroY - 1; j > i; j--) {
        Box::layerBox[j][heroX]->Move(MOVE_DOWN);
    }
    heroY++;
}

void Savegame::shiftLeft(Hero& hero) {
    hero.Move(MOVE_LEFT);
    int i;
    for (i = heroX + 1; i < 20; i++) {
        if (!Box::layerBox[heroY][i]) {
            break;
        }
    }
    for (int j = heroX + 1; j < i; j++) {
        Box::layerBox[heroY][j]->Move(MOVE_LEFT);
    }
    heroX--;
}

void Savegame::shiftRight(Hero& hero) {
    hero.Move(MOVE_RIGHT);
    int i;
    for (i = heroX - 1; i >= 0; i--) {
        if (!Box::layerBox[heroY][i]) {
            break;
        }
    }
    for (int j = heroX - 1; j > i; j--) {
        Box::layerBox[heroY][j]->Move(MOVE_RIGHT);
    }
    heroX++;
}