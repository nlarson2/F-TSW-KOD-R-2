//Brandon Hernandez
//
#ifndef BRANDON_H
#define BRANDON_H

#include "nickolasL.h"

using namespace std;


enum ButtonID
{
    MAIN_MENU,NEW_GAME,PAUSE,LOAD_GAME,HIGH_SCORES,CONTROLS,EXIT,ARCHER,SOLDIER,TANK,NICK,RESUME,SAVE_GAME,
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
    ButtonID bid;
    Button();
    Button(string,ButtonID);
    ~Button();
};

struct BHglobal
{
    Button menus[5][5];
    BHglobal();
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
		int procKeyInput(int key);
		void drawGameState();
};
#endif
