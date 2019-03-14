//Brandon Hernandez
//
#ifndef BRANDON_H
#define BRANDON_H

#include "nickolasL.h"

using namespace std;

/*struct GameState
{
    bool mainMenu, newGame, loadGame, highScores, options, board, battle, credits;
    GameState();
    int set_gameState();
    void set_mm();
    void set_ng();
    void set_lg();
    void set_hs();
    void set_op();
    void set_board();
};*/

enum ButtonID
{
    MAIN_MENU,NEW_GAME,LOAD_GAME,HIGH_SCORES,CONTROLS,EXIT,ARCHER,SOLDIER,TANK,NICK,
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
    //Button btn[5], btn1[5];
    BHglobal();
};

class Menu
{
    public:
        int size;
        Button * buttons;
        Menu(int,Button*);
        int state;
        ~Menu();
        void drawNames(int);
        void posButtons();
        void drawButtons();
        void check_mouse(int,int,int);
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
        void procMouseInput(int, int);
		void procKeyInput(int key);
		void drawGameState();
};
//void brandonH(int x, int y, GLuint textid);
#endif
