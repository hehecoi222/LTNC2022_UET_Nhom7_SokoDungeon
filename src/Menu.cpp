
#include "Menu.h"

Menu::Menu() {
    curMX = 0;
    curMY = 0;

    defaultTextColor = {0, 0, 0}; //Black
    hoveringTextColor = {255, 0, 0}; //Red
    colorWhite = {255, 255, 255};

    isClicked = TOTAL_ITEMS;

    inMenu = true;
    inOptions = false;
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
    gameTitleDest.y = 200;
    
    //Load Menu label
    int labelVertSpace = 72; 
    for (int i = 0; i < TOTAL_MENU_ITEMS; i++)
    {
        menuItemsTex[i].loadFromRenderText(menuItemsLabel[i], defaultTextColor);
        menuItemsDes[i].x = Game::WINDOW_WIDTH/2 - menuItemsTex[i].getWidth()/2;
        menuItemsDes[i].y = 300 + labelVertSpace;
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

    //Load option items
    optTex.loadFromFile(FindRes::getPath("img","buttons.png"));
    optPresTex.loadFromFile(FindRes::getPath("img","buttonsPressed.png"));
    optButClip[RETURN_HOME] = {0, 0};
    optButClip[CREDIT] = {64, 16};
    optButClip[SOUND_EFFECT] = {16, 32};
    optButClip[SOUND_EFFECT_OFF] = {32, 32};
    optButClip[MUSIC] = {48, 16};
    optButClip[MUSIC_OFF] = {0, 32};
    optButClip[CLOSE_OPTION] = {16, 48};
    optButClip[PAUSE_GAME] = {16, 16};
    for (int i = RETURN_HOME; i < TOTAL_OPTION_BUTTONS; i++) {
        optButClip[i].w = optButClip[i].h = 16;
        optButDes[i]. w = optButDes[i].h = optPanelDest.w/10;
    }
    optButClip[PAUSE_GAME].w = optButClip[PAUSE_GAME].h = 16;
    optButDes[PAUSE_GAME].w = optButDes[PAUSE_GAME].h = optPanelDest.w/10;
    optButDes[PAUSE_GAME].x = optButDes[PAUSE_GAME].y = optButDes[PAUSE_GAME].w/8;
    optButDes[CLOSE_OPTION].w = optButDes[CLOSE_OPTION].h = optPanelDest.w*6/80;
    optButDes[CLOSE_OPTION].x = optPanelDest.x + optPanelDest.w - optButDes[CLOSE_OPTION].w*5/4;
    optButDes[CLOSE_OPTION].y = optPanelDest.y + optButDes[CLOSE_OPTION].w*1/4;
    optButDes[RETURN_HOME].x = optPanelDest.x + optPanelDest.w*14/80;
    optButDes[RETURN_HOME].y =  optPanelDest.y + optPanelDest.h*15/48;
    optButDes[CREDIT].x = optPanelDest.x + optPanelDest.w*26/80;
    optButDes[CREDIT].y =  optButDes[RETURN_HOME].y;
    optButDes[SOUND_EFFECT].x = optButDes[SOUND_EFFECT_OFF].x = optButDes[RETURN_HOME].x;
    optButDes[SOUND_EFFECT].y = optButDes[SOUND_EFFECT_OFF].y = optPanelDest.y + optPanelDest.h*27/48;
    optButDes[MUSIC].x = optButDes[MUSIC_OFF].x = optButDes[CREDIT].x;
    optButDes[MUSIC].y = optButDes[MUSIC_OFF].y = optButDes[SOUND_EFFECT].y;
    cout << "load media";
}

void Menu::menuHandleEvent(SDL_Event& e, bool &gameIsRunning) {
    cout << optButDes[PAUSE_GAME].x  << " " << optButDes[PAUSE_GAME].y  << " " << optButDes[PAUSE_GAME].w  << " " << optButDes[PAUSE_GAME].h  << " " << endl;
    if(inMenu && !inOptions) {
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
                }
                else {
                    isClicked = TOTAL_ITEMS;
                    cout << "not press menu " << endl;
                }
            }
            break; 
        default:
            break;
        }
    }
    else if(inOptions) {
        switch (e.type)
        {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = RETURN_HOME; i < TOTAL_OPTION_BUTTONS; i++) {
                if(curMX >= optButDes[i].x  && curMY >= optButDes[i].y && curMX <= optButDes[i].x + optButDes[i].w &&  curMY <= optButDes[i].y + optButDes[i].h) {
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
                if(curMX >= optButDes[i].x  && curMY >= optButDes[i].y && curMX <= optButDes[i].x + optButDes[i].w &&  curMY <= optButDes[i].y + optButDes[i].h) {
                    isClicked = i;
                    if(itemsFunction(isClicked) == EXIT_GAME) gameIsRunning = false;
                    cout << "Press buttons " << endl;
                }
            }
            isClicked = TOTAL_ITEMS;
            break; 
        default:
            break;
        }
    }
    if(!inMenu && !inOptions) {
        if(e.type == SDL_MOUSEBUTTONDOWN){
            SDL_GetMouseState(&curMX, &curMY);
            if(curMX >= optButDes[PAUSE_GAME].x  && curMY >= optButDes[PAUSE_GAME].y && curMX <= optButDes[PAUSE_GAME].y + optButDes[PAUSE_GAME].w &&  curMY <= optButDes[PAUSE_GAME].y + optButDes[PAUSE_GAME].h) {
                isClicked = PAUSE_GAME;
                if(itemsFunction(isClicked) == EXIT_GAME) gameIsRunning = false;
            }
        }
    }
    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE){
        inOptions = true;
    }
}


int Menu::itemsFunction(int isCLicked){
    cout << "menu function ";
    switch (isClicked)
    {
    case NEW_GAME:
        inMenu = false;
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
        cout << "close option" << endl;
        break;

    case RETURN_HOME:
        inMenu = true;
        inOptions = false;
        cout << "return home" << endl << endl;
        break;
    case MUSIC:
        swap(optButClip[MUSIC],optButClip[MUSIC_OFF]);
        break;
    case SOUND_EFFECT:
        swap(optButClip[SOUND_EFFECT],optButClip[SOUND_EFFECT_OFF]);
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
        // titleBox.render(titleBoxDest.x, titleBoxDest.y, &titleBoxClip, &titleBoxDest);
        gameTitle.render(gameTitleDest.x, gameTitleDest.y, nullptr, &gameTitleDest);
    }
    if(inOptions) {
        optPanel.render(optPanelDest.x, optPanelDest.y, &optPanelClip, &optPanelDest);
        for (int i = RETURN_HOME; i < PAUSE_GAME; i++) {
            optTex.render(optButDes[i].x, optButDes[i].y, &optButClip[i], &optButDes[i]);
        }
    }
    SDL_Rect temp ={0, 0, 48, 48};
    if(!inMenu && !inOptions){
        cout << optButClip[PAUSE_GAME].w << endl;
        optPresTex.render(optButDes[PAUSE_GAME].x, optButDes[PAUSE_GAME].y, &optButClip[PAUSE_GAME], &temp);
    }
    
    
}

bool Menu::getMenuState() {return inMenu;}
bool Menu::getOptionState() {return inOptions;}