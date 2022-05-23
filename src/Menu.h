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

    //list of title menu items
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

    //Panel item
    Texture panelTex;
    SDL_Rect optPanelClip, optPanelDest;

    SDL_Rect winPanelClip, winPanelDest;
    
    Texture keyboardTex;
    Texture buttonsTex, buttonsPresTex;
    SDL_Rect ButClip[TOTAL_ITEMS], ButDes[TOTAL_ITEMS];

     // List of tutorial items
    enum {
        MOVE_UP,
        MOVE_DOWN,
        MOVE_RIGHT,
        MOVE_LEFT,
        UNDO,
        UNDO_TEXT,
        RESTART,
        RESTART_TEXT,
        PREV_LVL_TUT,
        NEXT_LVL_TUT,
        CHANGE_LVL_TEXT,
        TOTAL_TUTORIAL_ITEMS
    };
    static const int TOTAL_TUTORIAL_TEXT_ITEMS = 3;
    Texture menuTutorialItemsLabelTex[TOTAL_TUTORIAL_TEXT_ITEMS];
    string menuTutorialItemsLabel[TOTAL_TUTORIAL_TEXT_ITEMS] = {"Undo", "Restart","Change level"};
    SDL_Rect ButTutorialClip[TOTAL_TUTORIAL_ITEMS], ButTutorialDes[TOTAL_TUTORIAL_ITEMS];

    //Highscore items
    enum { SCORE_TEXT, HIGH_SCORE_TEXT, TOTAL_SCORE_TEXT_ITEMS };
    Texture winPanelHighScoreTextTex[TOTAL_SCORE_TEXT_ITEMS];
    string winPanelHighScoreText[TOTAL_SCORE_TEXT_ITEMS] = {"Moves: ", "High Score: "};
    SDL_Rect HighScoreDes[TOTAL_SCORE_TEXT_ITEMS];

    //Message to player
    Texture messTextFirst, messTextSec;

    //Text color
    SDL_Color defaultTextColor, hoveringTextColor;
    SDL_Color colorWhite;

    // Mouse position
    int curMX, curMY;

    //Menu state
    bool inMenu;
    bool inOptPanel;
    bool inWinPanel;
    bool inWinMusicPlayed;

   public:
    Menu();
    ~Menu();

    void loadMenu();
    void menuHandleEvent(SDL_Event& e, bool &gameIsRunning);
    void itemClickFunct(int item);
    void menuRender();

    int checkClicked(SDL_Rect itemDes[], int item);

    void renderHighScoreText();

    bool getMenuState();
    bool getOptPanelState();
    bool getWinPanelState();
    bool getWinMusicPlayed();

    void setWinPanelState(bool state);
    void setWinMusicPlayed(bool state);
};

#endif