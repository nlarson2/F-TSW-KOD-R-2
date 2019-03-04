//
//modified by:Adam Ostlund
//date:1/24/19
//
//3350 Spring 2018 Lab-1
//This program demonstrates the use of OpenGL and XWindows
//
//Assignment is to modify this program.
//You will follow along with your instructor.
//
//Elements to be learned in this lab...
// .general animation framework
// .animation loop
// .object definition and movement
// .collision detection
// .mouse/keyboard interaction
// .object constructor
// .coding style
// .defined constants
// .use of static variables
// .dynamic memory allocation
// .simple opengl components
// .git
//
//elements we will add to program...
//   .Game constructor
//   .multiple particles
//   .gravity
//   .collision detection
//   .more objects
//
#include <iostream>
using namespace std;
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"
#include "adamO.h"


const int MAX_PARTICLES = 2000;
const float GRAVITY = - 0.1;

//some structures

struct Vec {
	float x, y, z;
};

struct Shape {
	float width, height;
	float radius;
	Vec center;
};

struct Particle {
	Shape s;
	Vec velocity;
};

class Global {
public:
	int xres, yres;

    Shape box[1];
    Particle particle[MAX_PARTICLES];
	int n;
	Global() {
		xres = 800;
		yres = 600;
		//define a box shape
        //for(int i = 0; i < 5; i++){
		// if gamestate is board view just do box 1 and 2
        // if gamestate is battle view do all three boxes
        box[1].width = 150;
		box[1].height = 200;
		box[1].center.x = 75;
		box[1].center.y = 100;
        
        box[2].width = 50;
        box[2].height = 50;
        box[2].center.x = 2480;
        box[2].center.y = 75;

        box[3].width = 250;
        box[3].height = 75;
        box[3].center.x = 2310;
        box[3].center.y = 1365;

        n = 0;
        //}
    }
} g;

class X11_wrapper {
private:
    Display *dpy;
    Window win;
    GLXContext glc;
public:
    X11_wrapper() { }
    X11_wrapper(int w, int h) {
        GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        //GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
        XSetWindowAttributes swa;
        setup_screen_res(g.xres, g.yres);
        dpy = XOpenDisplay(NULL);
        if (dpy == NULL) {
            std::cout << "\n\tcannot connect to X server" << std::endl;
            exit(EXIT_FAILURE);
        }
        Window root = DefaultRootWindow(dpy);
        XWindowAttributes getWinAttr;
        XGetWindowAttributes(dpy, root, &getWinAttr);
        int fullscreen=0;
        g.xres = w;
        g.yres = h;
        if (!w && !h) {
            //Go to fullscreen.
            g.xres = getWinAttr.width;
            g.yres = getWinAttr.height;
            //When window is fullscreen, there is no client window
            //so keystrokes are linked to the root window.
            XGrabKeyboard(dpy, root, False,
                GrabModeAsync, GrabModeAsync, CurrentTime);
            fullscreen=1;
        }
        XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
        if (vi == NULL) {
            std::cout << "\n\tno appropriate visual found\n" << std::endl;
            exit(EXIT_FAILURE);
        }
        Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
            PointerMotionMask | MotionNotify | ButtonPress | ButtonRelease |
            StructureNotifyMask | SubstructureNotifyMask;
        unsigned int winops = CWBorderPixel|CWColormap|CWEventMask;
        if (fullscreen) {
            winops |= CWOverrideRedirect;
            swa.override_redirect = True;
        }
        win = XCreateWindow(dpy, root, 0, 0, g.xres, g.yres, 0,
            vi->depth, InputOutput, vi->visual, winops, &swa);
        //win = XCreateWindow(dpy, root, 0, 0, gl.xres, gl.yres, 0,
        //vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
        set_title();
        glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);
        show_mouse_cursor(0);
    }
    ~X11_wrapper() {
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
    }
    void set_title() {
        //Set the window title bar.
        XMapWindow(dpy, win);
        XStoreName(dpy, win, "Asteroids template");
    }
	    void check_resize(XEvent *e) {
        //The ConfigureNotify is sent by the
        //server if the window is resized.
        if (e->type != ConfigureNotify)
            return;
        XConfigureEvent xce = e->xconfigure;
        if (xce.width != g.xres || xce.height != g.yres) {
            //Window size did change.
            reshape_window(xce.width, xce.height);
        }
    }
    void reshape_window(int width, int height) {
        //window has been resized.
        setup_screen_res(width, height);
        glViewport(0, 0, (GLint)width, (GLint)height);
        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        glMatrixMode(GL_MODELVIEW); glLoadIdentity();
        glOrtho(0, g.xres, 0, g.yres, -1, 1);
        set_title();
    }
    void setup_screen_res(const int w, const int h) {
        g.xres = w;
        g.yres = h;
    }
    void swapBuffers() {
        glXSwapBuffers(dpy, win);
    }
    bool getXPending() {
        return XPending(dpy);
    }
    XEvent getXNextEvent() {
        XEvent e;
        XNextEvent(dpy, &e);
        return e;
    }
    void set_mouse_position(int x, int y) {
        XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
    }
    void show_mouse_cursor(const int onoff) {
        if (onoff) {
            //this removes our own blank cursor.
            //XUndefineCursor(dpy, win);
            return;
        }
        //vars to make blank cursor
        /*Pixmap blank;
        XColor white;
        char data[1] = {0};
        Cursor cursor;
        //make a blank cursor
        blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
        if (blank == None)
            std::cout << "error: out of memory." << std::endl;
        cursor = XCreatePixmapCursor(dpy, blank, blank, &white, &white, 0, 0);
        XFreePixmap(dpy, blank);
        //this makes you the cursor. then set it using this function
        XDefineCursor(dpy, win, cursor);
        //after you do not need the cursor anymore use this function.
        //it will undo the last change done by XDefineCursor
        //(thus do only use ONCE XDefineCursor and then XUndefineCursor):
    */
   }
} x11(0, 0);





//Function prototypes
void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void movement();
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
		movement();
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
}

void makeParticle(int x, int y)
{/*
	if (g.n >= MAX_PARTICLES)
		return;
	cout << "makeParticle() " << x << " " << y << endl;
	//position of particle
	Particle *p = &g.particle[g.n];
	p->s.center.x = x;
	p->s.center.y = y;
	p->velocity.y = -4.0;
	p->velocity.x =  1.0;
	++g.n;
    */
}

void check_mouse(XEvent *e)
{
	static int savex = 0;
	static int savey = 0;

	if (e->type != ButtonRelease &&
		e->type != ButtonPress &&
		e->type != MotionNotify) {
		//This is not a mouse event that we care about.
		return;
	}
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button was pressed
			int y = g.yres - e->xbutton.y;
			makeParticle(e->xbutton.x, y);
			return;
		}
		if (e->xbutton.button==3) {
			//Right button was pressed
			return;
		}
	}
	if (e->type == MotionNotify) {
		//The mouse moved!
		if (savex != e->xbutton.x || savey != e->xbutton.y) {
			savex = e->xbutton.x;
			savey = e->xbutton.y;
			int y = g.yres - e->xbutton.y;
			//makeParticle(e->xbutton.x, y);
			return;


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

void movement()
{
    /*
	if (g.n <= 0)
		return;
	for (int i = 0; i<g.n; i++) {

		Particle *p = &g.particle[i];
		p->s.center.x += p->velocity.x;
		p->s.center.y += p->velocity.y;
		p->velocity.y += GRAVITY;


		//check for collision with shapes...
        for (int i = 0; i < 5; i++){
		    Shape *s = &g.box[i];
		    if (p->s.center.y < s->center.y + s->height &&
		    p->s.center.y > s->center.y - s->height &&
		    p->s.center.x > s->center.x - s->width &&
		    p->s.center.x < s->center.x + s->width){
			    //bounce
			    p->velocity.y = -0.6*p->velocity.y;
		    }
        }

		//check for off-screen
		if (p->s.center.y < 0.0) {
			//cout << "off screen" << endl;
			g.particle[i] = g.particle[--g.n];
			//--g.n;
		}
	}*/
}

void render()
{
	Rect r;
    
    glClear(GL_COLOR_BUFFER_BIT);
	//Draw shapes...
	//
	//draw a box
	Shape *s;
	glColor3ub(90,140,90);
    float w, h, radius;

    for (int i = 1; i < 4; i++){
        s = &g.box[i];
	    glPushMatrix();
	    glTranslatef(s->center.x, s->center.y, s->center.z);
	    w = s->width;
	    h = s->height;
	    glBegin(GL_QUADS);
		    glVertex2i(-w, -h);
		    glVertex2i(-w,  h);
		    glVertex2i( w,  h);
		    glVertex2i( w, -h);
	    glEnd();
	    glPopMatrix();/*
        
        s = &g.box[2];
        glPushMatrix();
        glTranslatef(s->center.x, s->center.y, s->center.x);
        w = s->width;
        h = s->height;
        glBegin(GL_QUADS);
            glVertex2i(-w, -h);
            glVertex2i(-w,  h);
            glVertex2i( w,  h);
            glVertex2i( w, -h);
        glEnd();
        glPopMatrix(); */
    }
	//
	//Draw the particle here
	/*
    glPushMatrix();
	glColor3ub(150,160,220);
	for (int i=0; i<g.n; i++) {
		Vec *c = &g.particle[i].s.center;
		w =
		h = 2;
		glBegin(GL_QUADS);
			glVertex2i(c->x-w, c->y-h);
			glVertex2i(c->x-w, c->y+h);
			glVertex2i(c->x+w, c->y+h);
			glVertex2i(c->x+w, c->y-h);
		glEnd();
		glPopMatrix();
	}
    */
	//
	//Draw your 2D text here
    
    unsigned int c = 0x00ffff44;
    r.bot = g.yres - 20;
    r.left = 10;
    r.center = 0;
    ggprint8b(&r, 16, c, "B - Bigfoot");
    ggprint8b(&r, 16, c, "F - Forest");
    ggprint8b(&r, 16, c, "S - Silhouette");
    ggprint8b(&r, 16, c, "T - Trees");
    ggprint8b(&r, 16, c, "U - Umbrella");
    ggprint8b(&r, 16, c, "R - Rain");
    ggprint8b(&r, 16, c, "D - Deflection");
    ggprint8b(&r, 16, c, "N - Sounds");

}

/*
void showAdamPicture(int x, int y, GLuint textid) {
    glColor3ub(255,255,255);
    static int wid = 50;
    //float fx = (float)x + 100;
    //float fy = (float)y + 100;;
    glPushMatrix();
    glTranslatef(x,y,0);
    glBindTexture(GL_TEXTURE_2D, textid);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
    glEnd();
    glTranslatef(wid,0,0);
    Rect r;
    r.bot = 0;
    r.left = 10;
    r.center = 0;
    ggprint8b (&r, 16, 0x00000000, "Adam Ostlund");
    glPopMatrix();
}*/

