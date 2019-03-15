//Brandon Hernandez
#include "brandonH.h"

//=================================================//
//--------------- START OF BHglobal ---------------//
//=================================================//
BHglobal::BHglobal() {
	static Button btn[5] = {
		Button("New Game", NEW_GAME),
		Button("Load Game",LOAD_GAME),
		Button("High Scores",HIGH_SCORES),
		Button("Controls", CONTROLS),
		Button("Exit",EXIT)
	};
	static Button btn1[5] = {
		Button("Archer", ARCHER),
		Button("Soldier", SOLDIER),
		Button("Tank", TANK),
		Button("Nick", NICK),
		Button("Main Menu", MAIN_MENU)
	};
    static Button btn2[5] = {
        Button("Resume", RESUME),
        Button("Save Game", SAVE_GAME),
        Button("Main Menu", MAIN_MENU),
        Button("Main Menu", MAIN_MENU),
        Button("Main Menu", MAIN_MENU)        
    };

	for (int i=0; i<5; i++) {
		menus[0][i] = btn[i];
		menus[1][i] = btn1[i];
	    menus[2][i] = btn2[i];
    }
} BHglobal bhg;

//=================================================//
//---------------- START OF BUTTON ----------------//
//=================================================//
Button::Button() {
}

Button::Button(string n, ButtonID _bid) {
	name = n;
	bid = _bid;
}

Button::~Button() {
}

//=================================================//
//---------------- START OF MENUGS ----------------//
//=================================================//

MenuGS::MenuGS(int s, Button b[5][5], int xres, int yres)
{
	state = 0;
	size = s;
	buttons = new Button*[5];
	for (int i=0; i<5; i++)
		buttons[i] = new Button[5];
	this->xres = xres;
	this->yres = yres;
	for (int j=0; j<size; j++) {
		for (int i=0; i<size; i++) {
			buttons[j][i] = b[j][i];
			//Position Buttons
			buttons[j][i].width = 100;
			buttons[j][i].height = 20;
			buttons[j][i].center.x = 200;
			buttons[j][i].center.y = 500 - (i+1)*60;
		}
	}
}

MenuGS::~MenuGS()
{
	for (int i=0; i<5; i++)
		delete [] buttons[i];
	delete [] buttons;
}

int MenuGS::procMouseInput(int x, int y)
{
	ButtonID btn;
	for (int i=0;i<size;i++) {
		if (yres - y < buttons[state][i].center.y + buttons[state][i].height && yres - y > buttons[state][i].center.y - buttons[state][i].height &&
				x < buttons[state][i].center.x + buttons[state][i].width && x > buttons[state][i].center.x - buttons[state][i].width) {
			// Output which button and its corressponding ID to verify button clicks
			cout << "Count: " << i << " Button: " << buttons[state][i].name << endl;
			btn = buttons[state][i].bid;
		}
	}
	switch(btn) {
		case MAIN_MENU:
			state = MAIN_MENU;
            size = 5;
			break;
		case NEW_GAME:
			state = NEW_GAME;
			break;
		case LOAD_GAME:
			break;
		case HIGH_SCORES:
			break;
		case CONTROLS:
			break;
		case EXIT:
			exit(0);
			break;
		case ARCHER:
            state = PAUSE;
            size = 3;
            return 1;
			break;
		case SOLDIER:
            state = PAUSE;
            size = 3;
            return 1;
			break;
		case TANK:
            state = PAUSE;
            size = 3;
            return 1;
			break;
		case NICK:
            state = PAUSE;
            size = 3;
            return 1;
			break;
        case PAUSE:
            break;
        case SAVE_GAME:
            break;
        case RESUME:
            return 1;
            break;
	}
    return 0;
}

int MenuGS::procKeyInput(int key)
{
	return 0;//read keys
}

void MenuGS::drawGameState()
{
    if (state != PAUSE) 
        glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,xres,0,yres,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	for (int i=0; i<size; i++) {
		//Draw Buttons
		Button *s;
		glColor3ub(90,140,90);
		s = &buttons[state][i];
		glPushMatrix();
		glTranslatef(s->center.x, s->center.y, s->center.z);
		float w, h;
		w = s->width;
		h = s->height;
		glBegin(GL_QUADS);
		glVertex2i(-w, -h);
		glVertex2i(-w,  h);
		glVertex2i( w,  h);
		glVertex2i( w, -h);
		glEnd();
		glPopMatrix();

		//Draw Names
		int yres = 600;
		Rect r;
		r.bot = yres - (170 +(i*60));
		r.left = 200 ;
		ggprint16(&r, 16, 0x00ffff00, buttons[state][i].name.c_str());
	}
}
