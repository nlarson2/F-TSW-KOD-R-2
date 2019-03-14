#ifndef GAME_CPP
#define GAME_CPP
#include "Game.h"

extern BHglobal bhg;
extern int mainMap[];

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
        case -1:
            states.pop();
            break;
        case 1:
            states.push(new WorldGS(mainMap,25 ,25, 180, 0, 0, xres, yres));
            break;
            }
}

void Game::procKeyInput(int key)
{
	int changeState = states.top()->procKeyInput(key);
    switch(changeState) {
        case -1:
            cout << "pop:\n "; 
            states.pop();
            break;
    }
}

void Game::drawGameState()
{
	states.top()->drawGameState();
}

#endif
