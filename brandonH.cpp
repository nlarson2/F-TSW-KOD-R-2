//Brandon Hernandez
#include "brandonH.h"

Button::Button() {
}

Button::Button(string n) {
    name = n;
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

int Menu::check_mouse(int savex, int savey, int yres) {
    for(int i=0;i<size;i++) {
        if(yres - savey < buttons[i].center.y + buttons[i].height && yres - savey > buttons[i].center.y - buttons[i].height &&
                savex < buttons[i].center.x + buttons[i].width && savex > buttons[i].center.x - buttons[i].width) {
            cout << "Count: " << i << " Button: " << buttons[i].name << endl;
            return i;
        }
    }
    return 100;
}

MenuGS::MenuGS(int s, Button * b)
{
    size = s;
    buttons = new Button[size];
    this->xres = xres;
    this->yres = yres;
    for (int i=0; i<size; i++) {
        buttons[i] = b[i];
        //Position Buttons
        buttons[i].width = 100;
        buttons[i].height = 20;
        buttons[i].center.x = 200;
        buttons[i].center.y = 500 - (i+1)*60;
    }
}

void MenuGS::procMouseInput(int x, int y)
{
        for(int i=0;i<size;i++) {
        if(yres - y < buttons[i].center.y + buttons[i].height && yres - y > buttons[i].center.y - buttons[i].height &&
                x < buttons[i].center.x + buttons[i].width && x > buttons[i].center.x - buttons[i].width) {
            cout << "Count: " << i << " Button: " << buttons[i].name << endl;
        }
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
        
            //Draw Names
            int yres = 600;
            Rect r;
            r.bot = yres - (170 +(i*60));
            r.left = 200 ;
            ggprint16(&r, 16, 0x00ffff00, buttons[i].name.c_str());
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
