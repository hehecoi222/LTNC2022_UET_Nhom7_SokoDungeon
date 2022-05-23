
#include "Menu.h"
#include "Map.h"
#include "Savegame.h"
Menu::Menu() {
    curMX = 0;
    curMY = 0;

    defaultTextColor = {0, 0, 0, 255}; //Black
    hoveringTextColor = {255, 0, 0, 255}; //Red
    colorWhite = {255, 255, 255, 255};

    inMenu = true;
    inOptPanel = false;
    inWinPanel = false;
    inWinMusicPlayed = false;
}
Menu::~Menu(){}

void Menu::loadMenu() {
    //Load menu background IMG
    menuBackground.loadFromFile(FindRes::getPath("img","MenuBackground.jpg"));
    backgroundClip.w = 1100;
    backgroundClip.h = backgroundClip.w * 0.8;
    backgroundClip.x = menuBackground.getWidth()/2 - backgroundClip.w/2;
    backgroundClip.y = menuBackground.getHeight()/2 - backgroundClip.h/2 - 100;
    backgroundDestRect = {0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT};

    //load game title
    gameTitle.loadFromRenderText("SoKo Dungeon", colorWhite);
    gameTitleDest.w = gameTitle.getWidth()*2;
    gameTitleDest.h = gameTitle.getHeight()*2;
    gameTitleDest.x = Game::WINDOW_WIDTH/2 - gameTitleDest.w/2;
    gameTitleDest.y = Game::WINDOW_HEIGHT * 2 / 7  ;
    
    //Load Menu label
    int labelVertSpace = Game::BLOCK_WIDTH; 
    for (int i = 0; i < TOTAL_MENU_ITEMS; i++)
    {
        menuItemsTex[i].loadFromRenderText(menuItemsLabel[i], defaultTextColor);
        menuItemsDes[i].x = Game::WINDOW_WIDTH/2 - menuItemsTex[i].getWidth()/2;
        menuItemsDes[i].y = Game::WINDOW_HEIGHT/2 + labelVertSpace;
        menuItemsDes[i].w = menuItemsTex[i].getWidth();
        menuItemsDes[i].h = menuItemsTex[i].getHeight();
        labelVertSpace += 44;
    }

    //Load option panel
    panelTex.loadFromFile(FindRes::getPath("img", "GUI.png"));
    optPanelClip = {112, 256, 80 , 48};
    optPanelDest.w = Game::WINDOW_WIDTH*0.6;
    optPanelDest.h = optPanelDest.w*0.6;
    optPanelDest.x = Game::WINDOW_WIDTH/2 - optPanelDest.w/2;
    optPanelDest.y = Game::WINDOW_HEIGHT/2 - optPanelDest.h/2;

    //Load winning panel
    winPanelDest = optPanelDest;
    winPanelClip = optPanelClip;

    //Load option items
    buttonsTex.loadFromFile(FindRes::getPath("img","buttons.png"));
    buttonsPresTex.loadFromFile(FindRes::getPath("img","buttonsPressed.png"));
    ButClip[RETURN_HOME] = {0, 0};
    ButClip[CREDIT] = {64, 16};
    ButClip[SOUND_EFFECT] = {16, 32};
    ButClip[SOUND_EFFECT_OFF] = {32, 32};
    ButClip[MUSIC] = {48, 16};
    ButClip[MUSIC_OFF] = {0, 32};
    ButClip[CLOSE_OPTION] = {16, 48};
    ButClip[PAUSE_GAME] = {16, 16};
    for (int i = RETURN_HOME; i < PAUSE_GAME; i++) {
        ButClip[i].w = ButClip[i].h = 16;
        ButDes[i]. w = ButDes[i].h = optPanelDest.w/10;
    }
    ButClip[PAUSE_GAME].w = ButClip[PAUSE_GAME].h = 16;
    ButDes[PAUSE_GAME] = {Game::BLOCK_WIDTH, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    ButDes[CLOSE_OPTION].w = ButDes[CLOSE_OPTION].h = optPanelDest.w*6/80;
    ButDes[CLOSE_OPTION].x = optPanelDest.x + optPanelDest.w - ButDes[CLOSE_OPTION].w*5/4;
    ButDes[CLOSE_OPTION].y = optPanelDest.y + ButDes[CLOSE_OPTION].w*1/4;
    ButDes[RETURN_HOME].x = optPanelDest.x + optPanelDest.w*14/80;
    ButDes[RETURN_HOME].y =  optPanelDest.y + optPanelDest.h*15/48;
    ButDes[CREDIT].x = optPanelDest.x + optPanelDest.w*26/80;
    ButDes[CREDIT].y =  ButDes[RETURN_HOME].y;
    ButDes[SOUND_EFFECT].x = ButDes[SOUND_EFFECT_OFF].x = ButDes[RETURN_HOME].x;
    ButDes[SOUND_EFFECT].y = ButDes[SOUND_EFFECT_OFF].y = optPanelDest.y + optPanelDest.h*27/48;
    ButDes[MUSIC].x = ButDes[MUSIC_OFF].x = ButDes[CREDIT].x;
    ButDes[MUSIC].y = ButDes[MUSIC_OFF].y = ButDes[SOUND_EFFECT].y;

    //Load winning buttons from img
    ButClip[RESTART_LEVEL] = {0, 48};
    ButClip[NEXT_LEVEL] = {32, 0};
    for (int i = NEXT_LEVEL; i < TOTAL_WINNING_BUTTONS; i++) {
        ButClip[i].w = ButClip[i].h = 16;
        ButDes[i]. w = ButDes[i].h = optPanelDest.w/10;
    }
    ButDes[RESTART_LEVEL] = ButDes[CREDIT];
    ButDes[NEXT_LEVEL] = ButDes[SOUND_EFFECT];
    ButDes[NEXT_LEVEL].x =  optPanelDest.x + optPanelDest.w * 20 / 80;

    // Load tutorial item
    menuTutorialItemsLabelTex[0].loadFromRenderText(menuTutorialItemsLabel[0], colorWhite);
    menuTutorialItemsLabelTex[1].loadFromRenderText(menuTutorialItemsLabel[1], colorWhite);
    ButTutorialClip[MOVE_UP] = {48, 0, 16, 16};
    ButTutorialClip[MOVE_DOWN] = {48, 0, 16, 16};
    ButTutorialClip[MOVE_RIGHT] = {32, 0, 16, 16};
    ButTutorialClip[MOVE_LEFT] = {0, 16, 16, 16};
    ButTutorialClip[UNDO] = {32, 64, 16, 16};
    ButTutorialClip[RESTART] = {0, 48, 16, 16};
    ButTutorialDes[MOVE_UP] = {Game::BLOCK_WIDTH*2, Game::BLOCK_WIDTH*3, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    ButTutorialDes[MOVE_DOWN] = {Game::BLOCK_WIDTH*2, Game::BLOCK_WIDTH*4, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    ButTutorialDes[MOVE_LEFT] = {Game::BLOCK_WIDTH, Game::BLOCK_WIDTH*4, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    ButTutorialDes[MOVE_RIGHT] = {Game::BLOCK_WIDTH*3, Game::BLOCK_WIDTH*4, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    ButTutorialDes[UNDO] = {Game::BLOCK_WIDTH, Game::BLOCK_WIDTH*6, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    ButTutorialDes[RESTART] = {Game::BLOCK_WIDTH, Game::BLOCK_WIDTH*7, Game::BLOCK_WIDTH, Game::BLOCK_WIDTH};
    ButTutorialDes[UNDO_TEXT] = {Game::BLOCK_WIDTH*2 + Game::BLOCK_WIDTH/8, Game::BLOCK_WIDTH*6 +Game::BLOCK_WIDTH/4 , menuTutorialItemsLabelTex[0].getWidth()/2, menuTutorialItemsLabelTex[0].getHeight()/2 + Game::BLOCK_WIDTH/8};
    ButTutorialDes[RESTART_TEXT] = {Game::BLOCK_WIDTH*2 + Game::BLOCK_WIDTH/8, Game::BLOCK_WIDTH*7 + Game::BLOCK_WIDTH/4, menuTutorialItemsLabelTex[1].getWidth()/2, menuTutorialItemsLabelTex[1].getHeight()/2 + Game::BLOCK_WIDTH/8};
}


void Menu::menuHandleEvent(SDL_Event& e, bool &gameIsRunning) {
    if(inMenu && !inOptPanel && !inWinPanel) {
        if(Game::musicOn && !Mix_PlayingMusic())
        //Play intro sound while being in Menu state
            Mix_PlayMusic(Game::gTheme, -1);
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = 0; i < TOTAL_MENU_ITEMS; i++) {
                if(curMX >= menuItemsDes[i].x  && curMY >= menuItemsDes[i].y && curMX <= menuItemsDes[i].x + menuItemsDes[i].w &&  curMY <= menuItemsDes[i].y + menuItemsDes[i].h) {
                    menuItemsTex[i].loadFromRenderText(menuItemsLabel[i], hoveringTextColor);
                }
                else {
                    menuItemsTex[i].loadFromRenderText(menuItemsLabel[i], defaultTextColor);
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(Game::effectOn)
                    Mix_PlayChannel(-1, Game::gMouse, 0);
            for (int i = 0; i < TOTAL_MENU_ITEMS; i++) {
                if(checkClicked(menuItemsDes, i) == EXIT_GAME) gameIsRunning = false;
            }
            break; 
        default:
            break;
        }
    }
    else if(inOptPanel) {    
        if(e.type == SDL_MOUSEBUTTONDOWN) {
            if(Game::effectOn)
                    Mix_PlayChannel(-1, Game::gMouse, 0);
            for (int i = RETURN_HOME; i < PAUSE_GAME; i++) {
                checkClicked(ButDes, i);
            }
        }
    }
    if(!inMenu && !inOptPanel && !inWinPanel) {
        if(Game::musicOn && !Mix_PlayingMusic())
            Mix_PlayMusic(Game::gMusic, -1);
        if(e.type == SDL_MOUSEBUTTONDOWN) {
            if(Game::effectOn)
                    Mix_PlayChannel(-1, Game::gMouse, 0);
        checkClicked(ButDes, PAUSE_GAME);
        }
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w) {
            inWinPanel = true;
        }
    }
    if(inWinPanel) {
        if(e.type == SDL_MOUSEBUTTONDOWN) {
            if(Game::effectOn)
                    Mix_PlayChannel(-1, Game::gMouse, 0);
            for (int i = NEXT_LEVEL; i < TOTAL_WINNING_BUTTONS; i++) {
                checkClicked(ButDes, i);
            }
            checkClicked(ButDes, RETURN_HOME);
            checkClicked(ButDes, CLOSE_OPTION);
        }
    }
}


void Menu::itemClickFunct(int item){
    switch (item)
    {
    case NEW_GAME:
        inMenu = false;
        Game::newGame();
        break;

    case CONTINUE_GAME:
        inMenu = false;
        break;

    case OPTION_GAME:
        inOptPanel = true;
        inWinPanel = false;
        break;

    case EXIT_GAME:
        return;
        break;

    case PAUSE_GAME:
        inOptPanel = true;
        break;

    case CLOSE_OPTION:
        inOptPanel = false;
        inWinPanel = false;
        break;

    case RETURN_HOME:
        inMenu = true;
        inOptPanel = false;
        inWinPanel = false;
        break;
    case MUSIC:
        swap(ButClip[MUSIC],ButClip[MUSIC_OFF]);
        Game::musicOn = !Game::musicOn;
        if(!Game::musicOn){
            Mix_PauseMusic();
        }
        else
            Mix_ResumeMusic();
        break;
    case SOUND_EFFECT:
        swap(ButClip[SOUND_EFFECT],ButClip[SOUND_EFFECT_OFF]);
        Game::effectOn = !Game::effectOn;
        break;
    case RESTART_LEVEL:
        inWinPanel = false;
        Game::restartGame();
        break;
    case NEXT_LEVEL:
        inWinPanel = false;
        Game::nextMap();
        break;
    default:
    break;
    }
}

void Menu::renderHighScoreText() {
    winPanelHighScoreTextTex[SCORE_TEXT].loadFromRenderText(
        winPanelHighScoreTextLabel[SCORE_TEXT] + to_string(Savegame::movesCount), defaultTextColor);
    winPanelHighScoreTextTex[HIGH_SCORE_TEXT].loadFromRenderText(
        winPanelHighScoreTextLabel[HIGH_SCORE_TEXT] + to_string(Savegame::currentHighScore), defaultTextColor);
    winPanelHighScoreItemsDes[SCORE_TEXT] = {
    optPanelDest.x + (optPanelDest.w * 9 / 16),
    optPanelDest.y + optPanelDest.h * 15 / 48,
    int(winPanelHighScoreTextTex[SCORE_TEXT].getWidth() * 1.5),
    int(winPanelHighScoreTextTex[SCORE_TEXT].getHeight() * 1.5)};

winPanelHighScoreItemsDes[HIGH_SCORE_TEXT] = {
    optPanelDest.x + (optPanelDest.w * 9 / 16),
    optPanelDest.y + optPanelDest.h * 26 / 48,
    int(winPanelHighScoreTextTex[SCORE_TEXT].getWidth() * 1.5),
    int(winPanelHighScoreTextTex[SCORE_TEXT].getHeight() * 1.5)};
    winPanelHighScoreTextTex[SCORE_TEXT].render(
        winPanelHighScoreItemsDes[SCORE_TEXT].x,
        winPanelHighScoreItemsDes[SCORE_TEXT].y, nullptr,
        &winPanelHighScoreItemsDes[SCORE_TEXT]);
    winPanelHighScoreTextTex[HIGH_SCORE_TEXT].render(
        winPanelHighScoreItemsDes[HIGH_SCORE_TEXT].x,
        winPanelHighScoreItemsDes[HIGH_SCORE_TEXT].y, nullptr,
        &winPanelHighScoreItemsDes[HIGH_SCORE_TEXT]);
    winPanelHighScoreTextTex[SCORE_TEXT].free();
    winPanelHighScoreTextTex[HIGH_SCORE_TEXT].free();
}

void Menu::menuRender() {
    if(inMenu) {
        menuBackground.render(0, 0, &backgroundClip, &backgroundDestRect);
        for (int i = 0; i < TOTAL_MENU_ITEMS; i++) {
            menuItemsTex[i].render(menuItemsDes[i].x, menuItemsDes[i].y);
        }      
        gameTitle.render(gameTitleDest.x, gameTitleDest.y, nullptr, &gameTitleDest);
    }
    if(inOptPanel) {
        panelTex.render(optPanelDest.x, optPanelDest.y, &optPanelClip, &optPanelDest);
        for (int i = RETURN_HOME; i < PAUSE_GAME; i++) {
            buttonsTex.render(ButDes[i].x, ButDes[i].y, &ButClip[i], &ButDes[i]);
        }
    }
    if(inWinPanel){
        panelTex.render(winPanelDest.x, winPanelDest.y, &winPanelClip, &winPanelDest);
        for (int i = NEXT_LEVEL; i < TOTAL_WINNING_BUTTONS; i++)
        {
            buttonsTex.render(ButDes[i].x, ButDes[i].y, &ButClip[i], &ButDes[i]);
        }
        buttonsTex.render(ButDes[RETURN_HOME].x,  ButDes[RETURN_HOME].y, &ButClip[RETURN_HOME], &ButDes[RETURN_HOME]);
        renderHighScoreText();
    }
    if(!inMenu && !inOptPanel && !inWinPanel){
        buttonsPresTex.render(ButDes[PAUSE_GAME].x, ButDes[PAUSE_GAME].y, &ButClip[PAUSE_GAME], &ButDes[PAUSE_GAME]);
        for (int i = 0; i < TOTAL_TUTORIAL_ITEMS; i++) {
            if (i == MOVE_DOWN) {
                buttonsPresTex.render(ButTutorialDes[i].x , ButTutorialDes[i].y, &ButTutorialClip[i], &ButTutorialDes[i], 180, NULL);
            } else if (i == UNDO_TEXT) {
                menuTutorialItemsLabelTex[0].render(ButTutorialDes[i].x, ButTutorialDes[i].y, nullptr, &ButTutorialDes[i]);
            } else if (i == RESTART_TEXT) {
                menuTutorialItemsLabelTex[1].render(ButTutorialDes[i].x, ButTutorialDes[i].y, nullptr, &ButTutorialDes[i]);
            } else {
                buttonsPresTex.render(ButTutorialDes[i].x , ButTutorialDes[i].y, &ButTutorialClip[i], &ButTutorialDes[i]);
            }
        } 
    }

    

}
int Menu::checkClicked(SDL_Rect checkItemDes[], int checkItem){
    SDL_GetMouseState(&curMX, &curMY);
    if(curMX >= checkItemDes[checkItem].x  && curMY >= checkItemDes[checkItem].y && curMX <= checkItemDes[checkItem].x + checkItemDes[checkItem].w &&  curMY <= checkItemDes[checkItem].y + checkItemDes[checkItem].h) {
        if(checkItem == EXIT_GAME) {
            cout << "Exit Game\n";
            return EXIT_GAME;
        }
        itemClickFunct(checkItem);
    }
    return TOTAL_ITEMS;
}

bool Menu::getMenuState() {return inMenu;}
bool Menu::getOptPanelState() {return inOptPanel;}
bool Menu::getWinPanelState() {return inWinPanel;}
bool Menu::getWinMusicPlayed() {return inWinMusicPlayed;}

void Menu::setWinPanelState(bool state) {inWinPanel = state;}
void Menu::setWinMusicPlayed(bool state) {inWinMusicPlayed = state;}
