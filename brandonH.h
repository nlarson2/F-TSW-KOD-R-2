//Brandon Hernandez
//
#ifndef BRANDON_H
#define BRANDON_H

#include "nickolasL.h"
#include "nicholasJo.h"

using namespace std;


enum ButtonID
{
    MAIN_MENU,NEW_GAME,LOAD_GAME,HIGH_SCORES,CONTROLS,
    EXIT,ARCHER,SOLDIER,TANK,NICK,
    SAVE1, SAVE2, SAVE3, SAVE4,
};

enum pButtonID
{
    RESUME,SAVE_GAME,PMAIN_MENU,
    RETREAT,
    REST,
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
    Button bmenu[3];
    Button tmenu[3];
    BHglobal();
};
// Done During Lab hours
// Creates pause functionality by pressing esc while in game.
// Additionally added save game functionality
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
// Updated During lab hours
class MenuGS : public GameState {
    private:
        int state;
        int size;
        bool clicked;
        Button ** buttons;
        float xres, yres;
        int name;
    public:
        MenuGS(int, Button[5][5],int, int);
        ~MenuGS();
        int procMouseInput(int, int);
		int procKeyInput(int);
		void drawGameState();
};
// May not need implementation
class TownGS : public GameState {
    private:
        Button * buttons;
        float xres, yres;
    public:
        TownGS(Button[2], int, int);
        ~TownGS();
        int procMouseInput(int, int);
        int procKeyInput(int);
        void drawGameState();
};

#endif
