//Brandon Hernandez
//
#include <iostream>
#include <GL/glx.h>
#include <string>
#include "fonts.h"

using namespace std;

struct GameState
{
    bool mainMenu, newGame, loadGame, highScores, options, board, battle, credits;
    GameState();
    int set_gameState();
    void set_mm();
    void set_ng();
    void set_lg();
    void set_hs();
    void set_op();
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

//void brandonH(int x, int y, GLuint textid);
