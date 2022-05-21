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

    //list of title menu items (3)
    enum {
        NEW_GAME,
        CONTINUE_GAME,
        OPTION_GAME,
        EXIT_GAME,
        TOTAL_MENU_ITEMS,
        RETURN_HOME,
        CREDIT,
        MUSIC_OFF,
        SOUND_EFFECT_OFF,
        MUSIC,
        SOUND_EFFECT,
        CLOSE_OPTION,
        PAUSE_GAME,
        TOTAL_OPTION_BUTTONS,
        NEXT_LEVEL,
        RESTART_LEVEL,
        TOTAL_WINNING_BUTTONS,
        TOTAL_ITEMS
    };
    Texture menuItemsTex[TOTAL_MENU_ITEMS];
    string menuItemsLabel[TOTAL_MENU_ITEMS] = {"New game", "Continue", "Options", "Exit"}; 
    SDL_Rect menuItemsDes[TOTAL_MENU_ITEMS];
    SDL_Rect pauseGame;

    //Text color
    SDL_Color defaultTextColor, hoveringTextColor;
    SDL_Color colorWhite;

    Texture panelTex;
    SDL_Rect optPanelClip, optPanelDest;

    SDL_Rect winPanelClip, winPanelDest;
    

    Texture buttonsTex, buttonsPresTex;
    SDL_Rect ButClip[TOTAL_ITEMS], ButDes[TOTAL_ITEMS];


    // Mouse position
    int curMX, curMY;

    //Menu state
    bool inMenu;
    bool inOptPanel;
    bool inWinPanel;
public:
    Menu();
    ~Menu();

    void loadMenu();
    void menuHandleEvent(SDL_Event& e, bool &gameIsRunning);
    void itemClickFunct(int item);
    void menuRender();

    int checkClicked(SDL_Rect itemDes[], int item);

    bool getMenuState();
    bool getOptPanelState();
    bool getWinPanelState();
    
};

#endif