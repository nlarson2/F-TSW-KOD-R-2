#include <iostream>
#include <string>
#include <GL/glx.h>
#include "fonts.h"

using namespace std;

struct vec
{
    float x,y,z;
};

struct Button
{
    float height, width;
    vec center;
    string name;
    Button();
    Button(string n);
    ~Button();
};

class Menu
{
    public:
        int size;
        Button * buttons;
        Menu(int,Button*);
        ~Menu();
        void drawNames(int);
        void posButtons();
        void drawButtons();
        int check_mouse(int,int,int);
};

/*
Button newGame("New Game"), loadGame("Load Game"), highScores("High Scores"), options("Controls"), exitf("Exit");
Button btn[] = {newGame,loadGame,highScores,options,exitf};
Menu mm(5,btn);

Button char1("Archer"), char2("Char2"), char3("Char3"), char4("Char4"), char5("Main Menu");
Button btn1[] = {char1,char2,char3,char4,char5};
Menu ng(5,btn1);
*/
