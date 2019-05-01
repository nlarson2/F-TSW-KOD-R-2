//3350
//program: adamO.cpp
//author: adam ostlund
//date: february 14, 2019
//
//This program is an individual source file containing a name and profile picture.
//
//


#ifndef ADAMO_H
#define ADAMO_H


//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <time.h>
//#include <math.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <X11/keysym.h>
#include <GL/glx.h>
//#include "log.h"
////#include "ppm.h"
#include "fonts.h"
#include <string>


using namespace std;

enum stateID
{
    END_TURN, CHAR_MENU, BATTLE, BOX
};

struct vec9
{
    float x, y;
};

struct Boxes
{
    stateID ID;
    float width, height;
    vec9 center;
    Boxes();
    Boxes(stateID);
};

struct AOglobal
{
    Boxes box[11];
    AOglobal();
};

class uiboxes
{
    private:
        int size;
        Boxes boxes[11];
        float xres, yres;
    public:
        uiboxes(Boxes[11], float, float);
        ~uiboxes(){}
        void procMouseInput(int, int);
        void procKeyInput(int key);
        void drawBoxes();
        void posBoxes();
        void check_mouse(int, int, int);
};


void showAdamPicture(int x, int y, GLuint textid);

#endif
