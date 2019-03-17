//Brandon Hernandez
#include "brandonH.h"

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
		Button("Save 1", SAVE1),
		Button("Save 2", SAVE2),
		Button("Save 3", SAVE3),
		Button("Save 4", SAVE4),
		Button("Main Menu", MAIN_MENU)
	};
	static Button btn3[5] = {
		Button("Save Game", SAVE_GAME),
		Button("Controls", CONTROLS),
		Button("High Scores", HIGH_SCORES),
		Button("Main Menu", MAIN_MENU),
		Button("Exit", EXIT)
	};

	for(int i=0; i<5; i++) {
		menus[0][i] = btn[i];
		menus[1][i] = btn1[i];
        menus[2][i] = btn2[i];
        menus[3][i] = btn3[i];
	}
}

BHglobal bhg;

Button::Button() {
}

Button::Button(string n, ButtonID _bid) {
	name = n;
	bid = _bid;
}

Button::~Button() {
}

Menu::Menu(int s, Button * b) {
	size = s;
	buttons = new Button[size];
	for(int i = 0; i < size; i++)
		buttons[i] = b[i];
	posButtons();
}

Menu::~Menu() {
	delete [] buttons;
}


void Menu::drawNames(int i) {
	int yres = 600;
	Rect r;
	r.bot = yres - (170 +(i*60));
	r.left = 200 ;
	ggprint16(&r, 16, 0x00ffff00, buttons[i].name.c_str());
}

void Menu::posButtons() {
	for(int i=0; i<size; i++) {
		buttons[i].width = 100;
		buttons[i].height = 20;
		buttons[i].center.x = 200;
		buttons[i].center.y = 500 - (i+1)*60;
	}
}

void Menu::drawButtons() {
	for (int i=0; i<size; i++) {
		Button *s;
		glColor3ub(90,140,90);
		s = &buttons[i];
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
		drawNames(i);
	}
}

void Menu::check_mouse(int savex, int savey, int yres) {
	for(int i=0;i<size;i++) {
		if(yres - savey < buttons[i].center.y + buttons[i].height && yres - savey > buttons[i].center.y - buttons[i].height &&
				savex < buttons[i].center.x + buttons[i].width && savex > buttons[i].center.x - buttons[i].width) {
			cout << "Count: " << i << " Button: " << buttons[i].name << endl;
		}
	}
}


//=================================================
//---------------- START OF MENUGS ----------------
//=================================================

MenuGS::MenuGS(int s, Button b[5][5], int xres, int yres)
{
	state = 0;
	size = s;
	buttons = new Button*[5];
	for(int i=0; i<5; i++)
		buttons[i] = new Button[5];
	this->xres = xres;
	this->yres = yres;
	for(int j=0; j<size; j++) {
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
	for(int i=0; i<5; i++)
		delete [] buttons[i];
	delete [] buttons;
}

int MenuGS::procMouseInput(int x, int y)
{
	ButtonID btn;
	for(int i=0;i<size;i++) {
		if(yres - y < buttons[state][i].center.y + buttons[state][i].height && yres - y > buttons[state][i].center.y - buttons[state][i].height &&
				x < buttons[state][i].center.x + buttons[state][i].width && x > buttons[state][i].center.x - buttons[state][i].width) {
			// Output which button and its corressponding ID to verify button clicks
			cout << "Count: " << i << " Button: " << buttons[state][i].name << endl;
			btn = buttons[state][i].bid;
		}
	}
	switch(btn) {
		case MAIN_MENU:
			state = MAIN_MENU;
			break;
		case NEW_GAME:
			state = NEW_GAME;
			break;
		case LOAD_GAME:
			state = LOAD_GAME;
			break;
		case HIGH_SCORES:
			state = HIGH_SCORES;
			break;
		case CONTROLS:
			state = CONTROLS;
			break;
		case EXIT:
            {
                Player *player = Player::getInstance();
                player->saveInstance(1);
			    exit(0);
            }
			break;
		case ARCHER:
            {
                if (Player::count != 0) {
                    Player::resetInstance();
                }
                Player *player = Player::setInstance("archer");
                //stops 'unused variable' warning
                (void)player;
                state = MAIN_MENU;
                return 1;
            }
			break;
		case SOLDIER:
            {
                if (Player::count != 0) {
                    Player::resetInstance();
                }
                Player *player = Player::setInstance("soldier");
                //stops 'unused variable' warning
                (void)player;
                state = MAIN_MENU;
                return 1;
            }
            break;
		case TANK:
            {
                if (Player::count != 0) {
                    Player::resetInstance();
                }
                Player *player = Player::setInstance("tank");
                //stops 'unused variable' warning
                (void)player;
                state = MAIN_MENU;
                return 1;
            }
            break;
		case NICK:
            {
                if (Player::count != 0) {
                    Player::resetInstance();
                }
                Player *player = Player::setInstance("nick");
                //stops 'unused variable' warning
                (void)player;
                state = MAIN_MENU;
                return 1;
            }
			break;
        case SAVE1:
            {
                Player *player = Player::getInstance();
                player->loadInstance(1);
                state = MAIN_MENU;
                return 1;
            }
            break;
        case SAVE2:
            {
                Player *player = Player::getInstance();
                player->loadInstance(2);
                state = MAIN_MENU;
                return 1;
            }
            break;
        case SAVE3:
            {
                Player *player = Player::getInstance();
                player->loadInstance(3);
                state = MAIN_MENU;
                return 1;
            }
            break;
        case SAVE4:
            {
                Player *player = Player::getInstance();
                player->loadInstance(4);
                state = MAIN_MENU;
                return 1;
            }
            break;
        case SAVE_GAME:
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

/*
   GameState::GameState() {
//Menu Items
mainMenu = true;
newGame = false;
loadGame = false;
highScores = false;
options = false;
board = false;
//Start mainMenu
set_gameState();
}

int GameState::set_gameState() {
if(mainMenu == true) {
return 1;
}

if(newGame == true) {
return 2;
}

if(loadGame == true) {
return 3;
}

if(highScores == true) {
return 4;
}

if(options == true) {
return 5;
}
if(board == true) {
return 6;
}
return 0;
}

void GameState::set_mm() {
mainMenu = true;
newGame = false;
loadGame = false;
highScores = false;
options = false;
board = false;
}
void GameState::set_ng() {
newGame = true;
mainMenu = false;
loadGame = false;
highScores = false;
options = false;
board = false;
}

void GameState::set_lg() {
loadGame = true;
mainMenu = false;
newGame = false;
highScores = false;
options = false;
board = false;
}

void GameState::set_hs() {
highScores = true;
mainMenu = false;
newGame = false;
loadGame = false;
options = false;
board = false;
}
void GameState::set_op() {
	options = true;
	mainMenu = false;
	newGame = false;
	loadGame = false;
	highScores = false;
	board = false;
}
void GameState::set_board() {
	board = true;
	options = false;
	mainMenu = false;
	newGame = false;
	loadGame = false;
	highScores = false;
}*/
/*
   void brandonh(int x, int y,gluint textid) 
   {

   glcolor3ub(255,255,255);
   static int wid = 50;
   glPushMatrix();
   glTranslatef(x, y, 0);
   glBindTexture(GL_TEXTURE_2D, textid);

   glBegin(GL_QUADS);
   glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
   glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
   glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
   glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, 0);

   glTranslatef(wid,0,0);
   Rect r;
   r.bot = 0;
   r.left = 10;
   r.center = 0;
   ggprint8b (&r, 16, 0x00000000, "Brandon Hernandez");
   glPopMatrix();
   }*/
