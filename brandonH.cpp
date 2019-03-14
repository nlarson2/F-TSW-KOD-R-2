//Brandon Hernandez
#include "brandonH.h"

Button newGame("New Game", NEW_GAME), loadGame("Load Game",LOAD_GAME), highScores("High Scores",HIGH_SCORES), options("Controls", CONTROLS), exitf("Exit",EXIT);
Button btn[] = {newGame,loadGame,highScores,options,exitf};

Button char1("Archer", ARCHER), char2("Soldier", SOLDIER), char3("Tank", TANK), char4("Nick", NICK), char5("Main Menu", MAIN_MENU);
Button btn1[] = {char1,char2,char3,char4,char5};


BHglobal::BHglobal() {
    for(int i=0; i<5; i++) {
        menus[0][i] = btn[i];
        menus[1][i] = btn1[i];
    }
}

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

void MenuGS::procMouseInput(int x, int y)
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
            break;
        case NEW_GAME:
            break;
        case LOAD_GAME:
            break;
        case HIGH_SCORES:
            break;
        case CONTROLS:
            break;
        case EXIT:
            break;
        case ARCHER:
            break;
        case SOLDIER:
            break;
        case TANK:
            break;
        case NICK:
            break;
    }
}

void MenuGS::procKeyInput(int key)
{
    //read keys
}

void MenuGS::drawGameState()
{
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
        std::cout << buttons[state][i].name << endl;
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
