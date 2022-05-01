#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include "Hero.h"

// NodeBox to save boxes that has collision
struct NodeBox {
    int x, y;
    NodeBox* next;
};

// Struct node to represent in Stack
struct Node {
    int direction;
    NodeBox* boxes;
    Node* next;
};

class Savegame {
   public:
    // Width of a block
    static const int BLOCK_WIDTH = 32;

    // Initialize the stack
    Savegame();
    ~Savegame();

    // Clear save game
    void clear();

    // Get hero position to save
    void saveHeroPosition(int x, int y) {
        heroX = x/BLOCK_WIDTH;
        heroY = y/BLOCK_WIDTH;
    }

    // Record move
    void recordMove(int direction);

    // Push to stack boxes
    void boxPush(int x, int y);

    // Undo move
    void undoMove(Hero& hero);

    // Direction
    enum { NOT_MOVE, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

   private:
    // Stack to save step
    Node* movesStack;
    // Temp boxes
    NodeBox* tempBoxes;
    // Push to stack
    void push(int direction);
    // Pop from stack
    int pop();
    // Pop from stack boxes
    void popBoxes();
    // Position of Hero in grid
    int heroX, heroY;

    // Shift position
    void shift(Hero& hero, int direction);
};

#endif