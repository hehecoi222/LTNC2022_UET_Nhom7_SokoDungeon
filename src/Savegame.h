#ifndef SAVE_GAME_H
#define SAVE_GAME_H

#include "Hero.h"
#include "mapgame.h"
#include "Game.h"

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
    // Initialize the stack
    Savegame();
    ~Savegame();

    // To file all moves
    void toFile(const char* filename);

    // Load savefile
    void loadSavefile(const char* filename, Hero& hero, MapGame& map);

    // Load high score
    void loadHighScore(const char* filename);

    // Compare high score and rewrite
    void compareHighScore(const char* filename);

    // Set current map
    void setMap(Hero& hero, MapGame& map);
    void setMapInt(int currentMap) { mapSave = currentMap; };

    // Clear save game
    void clear();

    // Get hero position to save
    void saveHeroPosition(int x, int y) {
        heroX = x/Game::BLOCK_WIDTH;
        heroY = y/Game::BLOCK_WIDTH;
    }

    // Record move
    void recordMove(int direction);

    // Push to stack boxes
    void boxPush(int x, int y);

    // Undo move
    void undoMove(Hero& hero);

    // Get Move count:
    int getMovesCount() { return movesCount; }

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
    // Current map
    int mapSave = 0;

    // Shift position
    void shift(Hero& hero, int direction);

    // Count how many moves
    int movesCount = 0;
    void addMovesCount() { movesCount++; }
    void subMovesCount() { movesCount--; }

    // Current high score
    int currentHighScore = 0;
};

#endif
