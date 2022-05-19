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
        TOTAL_MENU_ITEMS,
        RETURN_HOME,
        CREDIT,
        MUSIC_OFF,
        SOUND_EFFECT_OFF,
        MUSIC,
        SOUND_EFFECT,
        CLOSE_OPTION,
        TOTAL_OPTION_BUTTONS,
        PAUSE_GAME,
        TOTAL_ITEMS
    };
    Texture menuItemsTex[TOTAL_MENU_ITEMS];
    string menuItemsLabel[TOTAL_MENU_ITEMS] = {"New game", "Continue", "Options", "Exit"}; 
    SDL_Rect menuItemsDes[TOTAL_MENU_ITEMS];

    bool isHovering[TOTAL_ITEMS] = {0};
    int isClicked;

    //Text color
    SDL_Color defaultTextColor, hoveringTextColor;
    SDL_Color colorWhite;

    Texture optPanel;
    SDL_Rect optPanelClip, optPanelDest;

    Texture optTex, optPresTex;
    SDL_Rect optButClip[TOTAL_OPTION_BUTTONS], optButDes[TOTAL_OPTION_BUTTONS];


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
    int itemsFunction(int isClicked);
    void menuRender();

    bool getMenuState();
    bool getOptionState();
};

#endif