//Brandon Hernandez
//
#ifndef BRANDON_H
#define BRANDON_H

#include "nickolasL.h"

using namespace std;


enum ButtonID
{
    MAIN_MENU,NEW_GAME,LOAD_GAME,HIGH_SCORES,CONTROLS,EXIT,ARCHER,SOLDIER,TANK,NICK,
};

enum pButtonID
{
    RESUME,SAVE_GAME,PMAIN_MENU
};

struct vec
{
    float x,y,z;
};

struct Button
{
    float height, width;
    vec center;
    string name;
    ButtonID bid; pButtonID pbid;
    Button();
    Button(string,ButtonID);
    Button(string,pButtonID);
    ~Button();
};

struct BHglobal
{
    Button menus[5][5];
    Button pmenu[3];
    BHglobal();
};

class PauseGS : public GameState {
    private:
        Button * buttons;
        float xres, yres;
    public:
        PauseGS(Button[3],int,int);
        ~PauseGS();
        int procMouseInput(int, int);
        int procKeyInput(int);
        void drawGameState();
};

class MenuGS : public GameState {
    private:
        int state;
        int size;
        Button ** buttons;
        float xres, yres;
    public:
        MenuGS(int, Button[5][5],int, int);
        ~MenuGS();
        int procMouseInput(int, int);
		int procKeyInput(int);
		void drawGameState();
};
#endif
