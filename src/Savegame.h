#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include "Hero.h"

// Struct node to represent in Stack
struct Node {
    int data;
    bool isMoved;
    Node* next;
};

class Savegame {
   public:
    // Width of a block
    static const int BLOCK_WIDTH = 32;

    // Initialize the stack
    Savegame();
    ~Savegame();

    // Get hero position to save
    void saveHeroPosition(int x, int y) {
        heroX = x/BLOCK_WIDTH;
        heroY = y/BLOCK_WIDTH;
    }

    // Record move
    void recordMove(int direction);

    // Undo move
    void undoMove(Hero& hero);

    // Direction
    enum { NOT_MOVE, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

   private:
    // Stack to save step
    Node* movesStack;
    // Push to stack
    void push(int data);
    // Pop from stack
    int pop(bool&);
    
    // Position of Hero in grid
    int heroX, heroY;

    // Shift position
    void shiftUp(Hero& hero, bool);
    void shiftDown(Hero& hero, bool);
    void shiftLeft(Hero& hero, bool);
    void shiftRight(Hero& hero, bool);
};

#endif