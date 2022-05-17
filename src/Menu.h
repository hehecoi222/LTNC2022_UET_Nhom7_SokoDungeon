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

    //Game title texture
    Texture gameTitle;
    SDL_Rect gameTitleDest; 
    Texture titleBox;
    SDL_Rect titleBoxDest, titleBoxClip;


    //list of title menu items (3)
    enum {
        NEW_GAME,
        CONTINUE_GAME,
        OPTION_GAME,
        EXIT_GAME,
        TOTAL_ITEMS
    };
    Texture menuItemsTex[TOTAL_ITEMS];
    string itemsLabel[TOTAL_ITEMS] = {"New game", "Continue", "Options", "Exit"}; 
    SDL_Rect itemsPos[TOTAL_ITEMS];

    Texture optionPanel;
    SDL_Rect optionPanelClip, optionPanelDest;

    bool isHovering[TOTAL_ITEMS] = {0};
    bool isClicked[TOTAL_ITEMS] = {0};

    //Menu text color
    SDL_Color defaultTextColor, hoveringTextColor;
    SDL_Color colorWhite;

    // Mouse position
    int curMX, curMY;

    //Menu state
    bool inMenu;
    bool inOptions;
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