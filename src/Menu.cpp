
#include "Menu.h"

Menu::Menu() {

    curMX = 0;
    curMY = 0;

    defaultTextColor = {0, 0, 0}; //Black
    hoveringTextColor = {255, 0, 0}; //Red

    inMenu = true;

}
Menu::~Menu(){}

void Menu::loadMenu() {
    //Load menu background IMG
    menuBackground.loadFromFile(FindRes::getPath("img","MenuBackground.jpg"));
    backgroundClip = {menuBackground.getWidth()/2 - Game::WINDOW_WIDTH/2, menuBackground.getWidth()/2 - Game::WINDOW_WIDTH/2 - 70, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT};
    backgroundDestRect = {0, 0, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT};
    
    int labelVertSpace = 80; 
    for (int i = 0; i < TOTAL_ITEMS; i++)
    {
        menuItemsTex[i].loadFromRenderText(itemsLabel[i], defaultTextColor);
        itemsPos[i].x = Game::WINDOW_WIDTH/2 - menuItemsTex[i].getWidth()/2;
        itemsPos[i].y = Game::WINDOW_HEIGHT/2 - menuItemsTex[i].getHeight()/2 + labelVertSpace;
        itemsPos[i].w = menuItemsTex[i].getWidth();
        itemsPos[i].h = menuItemsTex[i].getHeight();
        labelVertSpace += 48;
    }
}

void Menu::menuHandleEvent(SDL_Event& e, bool &gameIsRunning) {
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

int Menu::itemsFunction(bool isClicked[]){
    if(isClicked[NEW_GAME]) {
        inMenu = false;
        return NEW_GAME;
    }
    if(isClicked[CONTINUE_GAME]) {
        inMenu = false;
        return CONTINUE_GAME;
    }
    if(isClicked[EXIT_GAME]) {
        return EXIT_GAME;
    }
    return TOTAL_ITEMS;
}
void Menu::menuRender() {
    if(inMenu){
        menuBackground.render(0, 0, &backgroundClip, &backgroundDestRect);
        for (int i = 0; i < TOTAL_ITEMS; i++) {
            menuItemsTex[i].render(itemsPos[i].x, itemsPos[i].y);
        }        
    }
}

bool Menu::getMenuState() {return inMenu;}