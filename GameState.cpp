#include "GameState.h"

GameState::GameState()
{
    //Menu Items
    mainMenu = true;
    newGame = false;
    loadGame = false;
    highScores = false;
    options = false;
    //Start mainMenu
    set_gameState();
}

int GameState::set_gameState()
{
    if(mainMenu == true) {
        return 1;
    }

    if(newGame == true) {
        return 2;
    }

    if(loadGame == true) {
        return 3;
    }

    if(highScores == true) {
        return 4;
    }

    if(options == true) {
        return 5;
    }

    return 0;
}

void GameState::set_mm()
{
    mainMenu = true;
    newGame = false;
    loadGame = false;
    highScores = false;
    options = false;
}
void GameState::set_ng()
{
    newGame = true;
    mainMenu = false;
    loadGame = false;
    highScores = false;
    options = false;

}

void GameState::set_lg()
{
    loadGame = true;
    mainMenu = false;
    newGame = false;
    highScores = false;
    options = false;
}

void GameState::set_hs()
{
    highScores = true;
    mainMenu = false;
    newGame = false;
    loadGame = false;
    options = false;
}
void GameState::set_op()
{
    options = true;
    mainMenu = false;
    newGame = false;
    loadGame = false;
    highScores = false;
}

