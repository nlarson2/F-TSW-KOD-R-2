#ifndef GAME_CPP
#define GAME_CPP
#include "Game.h"

extern BHglobal bhg;
extern NLarsGlobal * nlG;// = NLarsGlobal::GetInstance();
//extern NJordGlobal njG;
Game::Game(int x, int y) 
{
    xres = x;
    yres = y;
}

void Game::init()
{
    states.push(new MenuGS(5, bhg.menus,  xres, yres));
}

void Game::procMouseInput(int x, int y)
{
	int changeState = states.top()->procMouseInput(x,y);

    switch (changeState) {
        case -2:
            for (int i=0; i<2; i++)
            states.pop();
            break;
        case -1:
            states.pop();
            break;
        case 1:
            states.push(new WorldGS(nlG->MainMap, 25 ,25, 180, 0, 0, xres, yres));
            break;
        case 2:
            states.push(new PauseGS(bhg.pmenu,xres,yres));
            break;
        case 4:
            states.push(new PauseGS(bhg.bmenu,xres,yres));
            break;
    }
}

void Game::procKeyInput(int key)
{
	int changeState = states.top()->procKeyInput(key);
    switch(changeState) {
        case -2:
            for (int i=0; i<2; i++)
            states.pop();
            break;
        case -1:
            states.pop();
            break;
        case 1:
            states.push(new WorldGS(nlG->MainMap,25 ,25, 180, 0, 0, xres, yres));
            break;
        case 2:
            states.push(new PauseGS(bhg.pmenu,xres,yres));
            break;
        case 3:
            states.push(new BattleGS(nlG->BattleMap1,10 ,10, 180, 0, 0, xres, yres));
            break;
        case 4:
            states.push(new PauseGS(bhg.bmenu,xres,yres));
            break;
        case 5:
            states.push(new PauseGS(bhg.tmenu,xres,yres));
            break;
    }
}

void Game::drawGameState()
{
	states.top()->drawGameState();
}

#endif
