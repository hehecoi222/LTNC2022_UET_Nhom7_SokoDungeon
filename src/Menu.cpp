
#include "Menu.h"

Menu::Menu() {
    curMX = 0;
    curMY = 0;

    defaultTextColor = {0, 0, 0, 255}; //Black
    hoveringTextColor = {255, 0, 0, 255}; //Red
    colorWhite = {255, 255, 255, 255};

    isClicked = TOTAL_ITEMS;

    inMenu = true;
    inOptions = false;
    inWinOptions = false;
    inWinPanel = true;
    cout << "init successful";
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
        labelVertSpace += 48;
    }

    //Load option panel
    optPanel.loadFromFile(FindRes::getPath("img", "GUI.png"));
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
    for (int i = RETURN_HOME; i < TOTAL_OPTION_BUTTONS; i++) {
        ButClip[i].w = ButClip[i].h = 16;
        ButDes[i]. w = ButDes[i].h = optPanelDest.w/10;
    }
    ButClip[PAUSE_GAME].w = ButClip[PAUSE_GAME].h = 16;
    ButDes[PAUSE_GAME].w = ButDes[PAUSE_GAME].h = optPanelDest.w/10;
    ButDes[PAUSE_GAME].x = ButDes[PAUSE_GAME].y = ButDes[PAUSE_GAME].w/8;
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

    // Load tutorial item
    menuTutorialItemsLabelTex[0].loadFromRenderText(menuTutorialItemsLabel[0], colorWhite);
    menuTutorialItemsLabelTex[1].loadFromRenderText(menuTutorialItemsLabel[1], colorWhite);
    ButTutorialClip[MOVE_UP] = {48, 0, 16, 16};
    ButTutorialClip[MOVE_DOWN] = {48, 0, 16, 16};
    ButTutorialClip[MOVE_RIGHT] = {32, 0, 16, 16};
    ButTutorialClip[MOVE_LEFT] = {0, 16, 16, 16};
    ButTutorialClip[UNDO] = {32, 64, 16, 16};
    ButTutorialClip[RESTART] = {0, 48, 16, 16};
    int alignmentOfLeftBar = ((Game::WINDOW_WIDTH/2) - (Game::BLOCK_WIDTH * Game::GRID_WIDTH / 2))/2;
    ButTutorialDes[MOVE_UP] = {alignmentOfLeftBar - Game::BLOCK_WIDTH / 4, Game::BLOCK_WIDTH*2, Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2};
    ButTutorialDes[MOVE_DOWN] = {alignmentOfLeftBar - Game::BLOCK_WIDTH / 4, Game::BLOCK_WIDTH*2 + (Game::BLOCK_WIDTH/2), Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2};
    ButTutorialDes[MOVE_LEFT] = {(alignmentOfLeftBar - Game::BLOCK_WIDTH / 4) - Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH*2 + Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2};
    ButTutorialDes[MOVE_RIGHT] = {(alignmentOfLeftBar - Game::BLOCK_WIDTH / 4) + Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH*2 + Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2};
    ButTutorialDes[UNDO] = {(alignmentOfLeftBar - Game::BLOCK_WIDTH / 4) - Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH*3 + Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2};
    ButTutorialDes[RESTART] = {(alignmentOfLeftBar - Game::BLOCK_WIDTH / 4) - Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH*3 + Game::BLOCK_WIDTH, Game::BLOCK_WIDTH/2, Game::BLOCK_WIDTH/2};
    ButTutorialDes[UNDO_TEXT] = {alignmentOfLeftBar - Game::BLOCK_WIDTH / 4 + Game::BLOCK_WIDTH/8, Game::BLOCK_WIDTH*3 + Game::BLOCK_WIDTH/2 + Game::BLOCK_WIDTH/8, menuTutorialItemsLabelTex[0].getWidth()/2, menuTutorialItemsLabelTex[0].getHeight()/2 + Game::BLOCK_WIDTH/8};
    ButTutorialDes[RESTART_TEXT] = {alignmentOfLeftBar - Game::BLOCK_WIDTH / 4 + Game::BLOCK_WIDTH/8, Game::BLOCK_WIDTH*3 + Game::BLOCK_WIDTH + Game::BLOCK_WIDTH/8, menuTutorialItemsLabelTex[1].getWidth()/2, menuTutorialItemsLabelTex[1].getHeight()/2 + Game::BLOCK_WIDTH/8};
}

void Menu::setInWinOptions(bool _inWinOptions) {
    inWinOptions = _inWinOptions;
}

void Menu::setInWinMusicPlayed(bool _inWinMusicPlayed) {
    inWinMusicPlayed = _inWinMusicPlayed;
}

void Menu::menuHandleEvent(SDL_Event& e, bool &gameIsRunning) {
    if(inMenu && !inOptions && !inWinPanel) {
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = 0; i < TOTAL_MENU_ITEMS; i++) {
                if(curMX >= menuItemsDes[i].x  && curMY >= menuItemsDes[i].y && curMX <= menuItemsDes[i].x + menuItemsDes[i].w &&  curMY <= menuItemsDes[i].y + menuItemsDes[i].h) {
                    isHovering[i] = 1;
                    menuItemsTex[i].loadFromRenderText(menuItemsLabel[i], hoveringTextColor);
                }
                else {
                    isHovering[i] = 0;
                    menuItemsTex[i].loadFromRenderText(menuItemsLabel[i], defaultTextColor);
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = 0; i < TOTAL_MENU_ITEMS; i++) {
                if(curMX >= menuItemsDes[i].x  && curMY >= menuItemsDes[i].y && curMX <= menuItemsDes[i].x + menuItemsDes[i].w &&  curMY <= menuItemsDes[i].y + menuItemsDes[i].h) {
                    isClicked = i;
                    cout << "Press menu" << endl;
                    if(itemsFunction(isClicked) == EXIT_GAME ) gameIsRunning = false;
                    else if (itemsFunction(isClicked) == NEW_GAME) {
                        Game::restartGame();
                    }
                }
                else {
                    isClicked = TOTAL_ITEMS;
                    cout << "not press menu " << endl;
                }
                //thay cả cụm trong for bằng dòng dưới sẽ lỗi click không làm gì cả
                //checkClicked(i); 
            }
            break; 
        default:
            break;
        }
    }
    else if(inOptions && !inWinPanel) {    
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = RETURN_HOME; i < TOTAL_OPTION_BUTTONS; i++) {
                if(curMX >= ButDes[i].x  && curMY >= ButDes[i].y && curMX <= ButDes[i].x + ButDes[i].w &&  curMY <= ButDes[i].y + ButDes[i].h) {
                    isHovering[i] = 1;
                }
                else {
                    isHovering[i] = 0;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = RETURN_HOME; i < TOTAL_OPTION_BUTTONS; i++) {
                if(curMX >= ButDes[i].x  && curMY >= ButDes[i].y && curMX <= ButDes[i].x + ButDes[i].w &&  curMY <= ButDes[i].y + ButDes[i].h) {
                    isClicked = i;
                    if(itemsFunction(isClicked) == EXIT_GAME) gameIsRunning = false;
                }
                else {
                    isClicked = TOTAL_ITEMS;
                }
            }
            break; 
        default:
            break;
        }
    }
    if(!inMenu && !inOptions && !inWinPanel) {
        if(e.type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState(&curMX, &curMY);
            if(curMX >= ButDes[PAUSE_GAME].x  && curMY >= ButDes[PAUSE_GAME].y && curMX <= ButDes[PAUSE_GAME].y + ButDes[PAUSE_GAME].w &&  curMY <= ButDes[PAUSE_GAME].y + ButDes[PAUSE_GAME].h) {
                isClicked = PAUSE_GAME;
                if(itemsFunction(isClicked) == EXIT_GAME) gameIsRunning = false;
            }
            else {
                isClicked = TOTAL_ITEMS;
            }
        }
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w){
            inWinPanel = true;
        }
    }
    if(inWinPanel) {
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = RETURN_HOME; i < TOTAL_OPTION_BUTTONS; i++) {
                if(curMX >= ButDes[i].x  && curMY >= ButDes[i].y && curMX <= ButDes[i].x + ButDes[i].w &&  curMY <= ButDes[i].y + ButDes[i].h) {
                    isHovering[i] = 1;
                    cout << 1;
                }
                else {
                    isHovering[i] = 0;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = NEXT_LEVEL; i < TOTAL_WINNING_BUTTONS; i++) {
                if(curMX >= ButDes[i].x  && curMY >= ButDes[i].y && curMX <= ButDes[i].x + ButDes[i].w &&  curMY <= ButDes[i].y + ButDes[i].h) {
                    isClicked = i;
                    if(itemsFunction(isClicked) == EXIT_GAME) gameIsRunning = false;
                    cout << "winning click" << endl;
                }
            }
            if(curMX >= ButDes[RETURN_HOME].x  && curMY >= ButDes[RETURN_HOME].y && curMX <= ButDes[RETURN_HOME].x + ButDes[RETURN_HOME].w &&  curMY <= ButDes[RETURN_HOME].y + ButDes[RETURN_HOME].h) {
                isClicked = RETURN_HOME;
                cout << "click return home win";
                if(itemsFunction(isClicked) == EXIT_GAME) gameIsRunning = false;
            }
            checkClicked(CLOSE_OPTION);
            break; 
        default:
            break;
        }
    }
    
}


int Menu::itemsFunction(int isCLicked){
    switch (isClicked)
    {
    case NEW_GAME:
        inMenu = false;
        return NEW_GAME;
        break;

    case CONTINUE_GAME:
        inMenu = false;
        break;
    case OPTION_GAME:
        inOptions = true;
        break;
    case EXIT_GAME:
        return EXIT_GAME;
        break;

    case PAUSE_GAME:
        inOptions = true;
        break;

    case CLOSE_OPTION:
        inOptions = false;
        inWinPanel = false;
        cout << "close option" << endl;
        break;

    case RETURN_HOME:
        inMenu = true;
        inOptions = false;
        inWinOptions = false;
        inWinPanel = false;
        cout << "return home" << endl << endl;
        break;
    case MUSIC:
        swap(ButClip[MUSIC],ButClip[MUSIC_OFF]);
        break;
    case SOUND_EFFECT:
        swap(ButClip[SOUND_EFFECT],ButClip[SOUND_EFFECT_OFF]);
        break;
    case RESTART_LEVEL:
        break;
    case NEXT_LEVEL:
        break;
    default:
    break;
    }
    return TOTAL_ITEMS;
}

void Menu::menuRender() {
    if(inMenu) {
        menuBackground.render(0, 0, &backgroundClip, &backgroundDestRect);
        for (int i = 0; i < TOTAL_MENU_ITEMS; i++) {
            menuItemsTex[i].render(menuItemsDes[i].x, menuItemsDes[i].y);
        }      
        gameTitle.render(gameTitleDest.x, gameTitleDest.y, nullptr, &gameTitleDest);
    }
    if(inOptions) {
        optPanel.render(optPanelDest.x, optPanelDest.y, &optPanelClip, &optPanelDest);
        for (int i = RETURN_HOME; i < PAUSE_GAME; i++) {
            buttonsTex.render(ButDes[i].x, ButDes[i].y, &ButClip[i], &ButDes[i]);
        }
    }
    if(!inMenu && !inOptions){
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
    if(inWinPanel){
        optPanel.render(winPanelDest.x, winPanelDest.y, &winPanelClip, &winPanelDest);
        for (int i = NEXT_LEVEL; i < TOTAL_WINNING_BUTTONS; i++)
        {
            buttonsTex.render(ButDes[i].x, ButDes[i].y, &ButClip[i], &ButDes[i]);
        }
        buttonsTex.render(ButDes[RETURN_HOME].x,  ButDes[RETURN_HOME].y, &ButClip[RETURN_HOME], &ButDes[RETURN_HOME]);
        buttonsTex.render(ButDes[CLOSE_OPTION].x,  ButDes[CLOSE_OPTION].y, &ButClip[CLOSE_OPTION], &ButDes[CLOSE_OPTION]);
    }

    

}
int Menu::checkClicked(int item){
    SDL_GetMouseState(&curMX, &curMY);
    if(curMX >= ButDes[item].x  && curMY >= ButDes[item].y && curMX <= ButDes[item].x + ButDes[item].w &&  curMY <= ButDes[item].y + ButDes[item].h) {
        if(item == EXIT_GAME) return EXIT_GAME;
        isClicked = item;
        cout << item << " is clicked";
        // itemsFunction(item) lỗi trong thực hiện được hàm itemFuction;
        itemsFunction(isClicked);
    }
    else {
        isClicked = TOTAL_ITEMS;
    }
    return item;
}

bool Menu::getMenuState() {return inMenu;}
bool Menu::getOptionState() {return inOptions;}
bool Menu::getWinOptionState() {return inWinOptions;}
bool Menu::getWinMusicPlayed() {return inWinMusicPlayed;}