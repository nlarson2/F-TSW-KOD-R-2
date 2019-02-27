#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"
#include "MainMenu.h"
#include "GameState.h"
#include "nicholasJo.h"

using namespace std;


Button newGame("New Game"), loadGame("Load Game"), highScores("High Scores"), options("Controls"), exitf("Exit");
Button btn[] = {newGame,loadGame,highScores,options,exitf};
Menu mm(5,btn);

Button char1("Archer"), char2("Soldier"), char3("Tank"), char4("Null"), char5("Main Menu");
Button btn1[] = {char1,char2,char3,char4,char5};
Menu ng(5,btn1);

GameState gs;

class Global
{
    public:
        int xres, yres;
        int n;
        int count;
        Global() {
            xres = 800;
            yres = 600;
            n = 0;
            count = 0;
        }
} g;

class X11_wrapper {
    private:
        Display *dpy;
        Window win;
        GLXContext glc;
    public:
        ~X11_wrapper() {
            XDestroyWindow(dpy, win);
            XCloseDisplay(dpy);
        }
        X11_wrapper() {
            GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
            int w = g.xres, h = g.yres;
            dpy = XOpenDisplay(NULL);
            if (dpy == NULL) {
                cout << "\n\tcannot connect to X server\n" << endl;
                exit(EXIT_FAILURE);
            }
            Window root = DefaultRootWindow(dpy);
            XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
            if (vi == NULL) {
                cout << "\n\tno appropriate visual found\n" << endl;
                exit(EXIT_FAILURE);
            } 
            Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
            XSetWindowAttributes swa;
            swa.colormap = cmap;
            swa.event_mask =
                ExposureMask | KeyPressMask | KeyReleaseMask |
                ButtonPress | ButtonReleaseMask |
                PointerMotionMask |
                StructureNotifyMask | SubstructureNotifyMask;
            win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
                    InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
            set_title();
            glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
            glXMakeCurrent(dpy, win, glc);
        }
        void set_title() {
            //Set the window title bar.
            XMapWindow(dpy, win);
            XStoreName(dpy, win, "3350 Lab1");
        }
        bool getXPending() {
            //See if there are pending events.
            return XPending(dpy);
        }
        XEvent getXNextEvent() {
            //Get a pending event.
            XEvent e;
            XNextEvent(dpy, &e);
            return e;
        }
        void swapBuffers() {
            glXSwapBuffers(dpy, win);
        }
} x11;

//Function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void render();

//=====================================
// MAIN FUNCTION IS HERE
//=====================================
int main()
{
    srand(time(NULL));
    init_opengl();
    //Main animation loop
    int done = 0;
    while (!done) {
        //Process external events.
        while (x11.getXPending()) {
            XEvent e = x11.getXNextEvent();
            check_mouse(&e);
            done = check_keys(&e);
        }
        render();
        x11.swapBuffers();
    }
    return 0;
}

void init_opengl(void)
{
    //OpenGL initialization
    glViewport(0, 0, g.xres, g.yres);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //Set 2D mode (no perspective)
    glOrtho(0, g.xres, 0, g.yres, -1, 1);
    //Set the screen background color
    glClearColor(0.1, 0.1, 0.1, 1.0);
    //Insert Fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
}

void check_mouse(XEvent *e)
{

    static int savex;
    static int savey;
    int flag;

    if (e->type != ButtonRelease &&
            e->type != ButtonPress) {
        //This is not a mouse event that we care about.
        return;
    }
    if (e->type == ButtonRelease) {
        return;
    }
    //----------------------------------------------------------
    if (e->type == ButtonPress) {
        if (e->xbutton.button==1) {
            //Left button was pressed
            if(savex != e->xbutton.x || savey != e->xbutton.y) {
                savex = e->xbutton.x;
                savey = e->xbutton.y;
            }
            if(g.count == 0)
                flag = mm.check_mouse(savex, savey, g.yres);
            if(g.count == 1)
                flag = ng.check_mouse(savex,savey, g.yres);
            switch(flag) {
                case 0:
                    //check gameState
                    //NewGame GameBoard || Char1 || Save file 1
                    if(g.count == 0) {
                    gs.set_ng();
                    g.count++;
                    } else {
                       Player * player = Player::getInstance("archer");
                       cout << player->getDefense(); 
                    }
                    break;
                case 1:
                    //check gameState
                    //gameState = loadGame || Char2
                    if(g.count == 0) {
                    } else {
                        Player * player = Player::getInstance("soldier");
                        cout << player->getDefense();
                    }

                    break;
                case 2:
                    //check gameState
                    //gameState = highScores || Char3
                    if(g.count == 0) {
                    } else {
                        Player * player = Player::getInstance("tank");
                        cout << player->getDefense();
                    }
                    break;
                case 3:
                    //check gameState
                    //gameState = options
                    break;
                case 4:
                    if(g.count == 0)
                        exit(0);
                    else if(g.count == 1){
                        gs.set_mm();
                        g.count--;
                    }
                    break;
                default:
                    break;          
            }
            return;

            //---------------------------------------------------------
            if (e->xbutton.button==3) {
                //Right button was pressed
                return;
            }
        }
    }
}

int check_keys(XEvent *e)
{
    if (e->type != KeyPress && e->type != KeyRelease)
        return 0;
    int key = XLookupKeysym(&e->xkey, 0);
    if (e->type == KeyPress) {
        switch (key) {
            case XK_1:
                //Key 1 was pressed
                break;
            case XK_a:
                //Key A was pressed
                break;
            case XK_Escape:
                //Escape key was pressed
                return 1;
        }
    }
    return 0;
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int g = gs.set_gameState();
    if(g == 1)
        mm.drawButtons();
    else if(g == 2)
        ng.drawButtons();
    //else if(g == 3)
    //else if(g == 4)
    //else if(g == 5)
}
