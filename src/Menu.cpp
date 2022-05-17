
#include "Menu.h"

Menu::Menu() {

    curMX = 0;
    curMY = 0;

    defaultTextColor = {0, 0, 0}; //Black
    hoveringTextColor = {255, 0, 0}; //Red
    colorWhite = {255, 255, 255};

    inMenu = true;
    inOptions = false;

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

    //Load game title
    titleBox.loadFromFile(FindRes::getPath("img","GUI.png"));
    titleBoxClip.x = 144;
    titleBoxClip.y = 80;
    titleBoxClip.w = 48;
    titleBoxClip.h = 16;

    gameTitle.loadFromRenderText("SoKo Dungeon", colorWhite);
    gameTitleDest.w = gameTitle.getWidth()*2;
    gameTitleDest.h = gameTitle.getHeight()*2;
    gameTitleDest.x = Game::WINDOW_WIDTH/2 - gameTitleDest.w/2;
    gameTitleDest.y = 200;
    
    //Load Menu label
    int labelVertSpace = 72; 
    for (int i = 0; i < TOTAL_ITEMS; i++)
    {
        menuItemsTex[i].loadFromRenderText(itemsLabel[i], defaultTextColor);
        itemsPos[i].x = Game::WINDOW_WIDTH/2 - menuItemsTex[i].getWidth()/2;
        itemsPos[i].y = 300 + labelVertSpace;
        itemsPos[i].w = menuItemsTex[i].getWidth();
        itemsPos[i].h = menuItemsTex[i].getHeight();
        labelVertSpace += 48;
    }

    //Load option panel
    optionPanel.loadFromFile(FindRes::getPath("img", "GUI.png"));
    optionPanelClip = {112, 256, 80 , 48};
    optionPanelDest = {Game::WINDOW_WIDTH/2 - optionPanelClip.w/2*6 , Game::WINDOW_HEIGHT/2 - optionPanelClip.h/2*6, optionPanelClip.w*6 , optionPanelClip.h*6 };
}

void Menu::menuHandleEvent(SDL_Event& e, bool &gameIsRunning) {
    if(inMenu) {
        switch (e.type)
        {
        case SDL_QUIT:
            gameIsRunning = false;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = 0; i < TOTAL_ITEMS; i++) {
                if(curMX >= itemsPos[i].x  && curMY >= itemsPos[i].y && curMX <= itemsPos[i].x + itemsPos[i].w &&  curMY <= itemsPos[i].y + itemsPos[i].h) {
                    isHovering[i] = 1;
                    menuItemsTex[i].loadFromRenderText(itemsLabel[i], hoveringTextColor);
                }
                else {
                    isHovering[i] = 0;
                    menuItemsTex[i].loadFromRenderText(itemsLabel[i], defaultTextColor);
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&curMX, &curMY);
            for (int i = 0; i < TOTAL_ITEMS; i++) {
                if(curMX >= itemsPos[i].x  && curMY >= itemsPos[i].y && curMX <= itemsPos[i].x + itemsPos[i].w &&  curMY <= itemsPos[i].y + itemsPos[i].h) {
                    isClicked[i] = 1;
                    if(itemsFunction(isClicked) == EXIT_GAME) gameIsRunning = false;
                }
                else {
                    isClicked[i] = 0;
                }
            }
            break; 
        default:
            break;
        }
    }
    if(inOptions) {}

}

int Menu::itemsFunction(bool isClicked[]){
    if(isClicked[NEW_GAME]) {
        inMenu = false;
        return NEW_GAME;
    }
    else if(isClicked[CONTINUE_GAME]) {
        inMenu = false;
        return CONTINUE_GAME;
    }
    else if(isClicked[OPTION_GAME]){
        inOptions = true;
        return OPTION_GAME;
    }
    else if(isClicked[EXIT_GAME]) {
        return EXIT_GAME;
    }
    return TOTAL_ITEMS;
}
void Menu::menuRender() {
    if(inMenu) {
        menuBackground.render(0, 0, &backgroundClip, &backgroundDestRect);
        for (int i = 0; i < TOTAL_ITEMS; i++) {
            menuItemsTex[i].render(itemsPos[i].x, itemsPos[i].y);
        }      
        // titleBox.render(titleBoxDest.x, titleBoxDest.y, &titleBoxClip, &titleBoxDest);
        gameTitle.render(gameTitleDest.x, gameTitleDest.y, nullptr, &gameTitleDest);
    }
    if(inOptions) {
        optionPanel.render(optionPanelDest.x, optionPanelDest.y, &optionPanelClip, &optionPanelDest);
    }
}

bool Menu::getMenuState() {return inMenu;}