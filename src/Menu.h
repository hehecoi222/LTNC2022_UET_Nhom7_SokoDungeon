#ifndef Menu_h
#define Menu_h

#include "Game.h"
#include "Texture.h"
#include "find_res.h"
class Menu
{
private:

    //Background image
    Texture menuBackground;
    SDL_Rect backgroundClip;
    SDL_Rect backgroundDestRect;

    //list of items (3)
    enum {
        NEW_GAME,
        CONTINUE_GAME,
        EXIT_GAME,
        TOTAL_ITEMS
    };
    Texture menuItemsTex[TOTAL_ITEMS];
    string itemsLabel[TOTAL_ITEMS] = {"NEW GAME", "CONTINUE", "EXIT"}; 
    SDL_Rect itemsPos[TOTAL_ITEMS];

    bool isHovering[TOTAL_ITEMS] = {0};
    bool isClicked[TOTAL_ITEMS] = {0};

    //Menu text color
    SDL_Color defaultTextColor, hoveringTextColor;

    // Mouse position
    int curMX, curMY;

    //Menu state
    bool inMenu;
public:
    Menu();
    ~Menu();

    void loadMenu();
    void menuHandleEvent(SDL_Event& e, bool &gameIsRunning);
    int itemsFunction(bool isClicked[]);
    void menuRender();

    bool getMenuState();
    

};

#endif