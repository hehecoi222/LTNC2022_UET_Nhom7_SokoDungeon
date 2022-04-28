// TODO: Create struct to save position in every step
// Breakdown: What to save: Moves & Map
// How: an 2D Map which save position of hero and boxes, and stack to save step

#ifndef SAVE_GAME_H
#define SAVE_GAME_H

// Struct node to represent in Stack
struct Node {
    int data;
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
    int pop();
    
    // Position of Hero in grid
    int heroX, heroY;

    // Shift position
    void shiftUp(Hero& hero);
    void shiftDown(Hero& hero);
    void shiftLeft(Hero& hero);
    void shiftRight(Hero& hero);
};

#endif