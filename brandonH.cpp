// Author: Brandon Hernandez
// Spring 2019: CMPS 3350
// Group Project: F-TSW-KOD-R-2
// Last Updated: 5-5-2019

#include "brandonH.h"

extern NJordGlobal njG;
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
        Button("Save 1", SAVE1),
        Button("Save 2", SAVE2),
        Button("Save 3", SAVE3),
        Button("Save 4", SAVE4),
        Button("Main Menu", MAIN_MENU)
    };
    static Button pbtn[3] = {
        Button("Resume", RESUME),
        Button("Save Game", SAVE_GAME),
        Button("Main Menu", PMAIN_MENU),
    };
    static Button bbtn[3] = {
        Button("Resume", RESUME),
        Button("Save Game", SAVE_GAME),
        Button("Retreat", RETREAT),
    };
    static Button tbtn[3] = {
        Button("Resume", RESUME),
        Button("Save Game", SAVE_GAME),
        Button("Rest", REST),
    };
    // Derived Menu from PauseMenu. Select which save file to override
    // Needs implementation
    static Button pbtn2[5] = {
        Button("Save 1", SAVE1),
        Button("Save 2", SAVE2),
        Button("Save 3", SAVE3),
        Button("Save 4", SAVE4),
        Button("Return", PMAIN_MENU),
    };
    for (int i=0; i<5; i++) {
        menus[0][i] = btn[i];
        menus[1][i] = btn1[i];
        menus[2][i] = btn2[i];
    }
    for (int i=0; i<3; i++) { 
        pmenu[i] = pbtn[i];
        bmenu[i] = bbtn[i];
        tmenu[i] = tbtn[i];
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
Button::Button(string n, pButtonID _bid) {
    name = n;
    pbid = _bid;
}
Button::~Button() {
}

//=================================================//
//---------------- START OF PAUSEGS ---------------//
//=================================================//

PauseGS::PauseGS(Button b[3],int xres, int yres)
{
    buttons = new Button[3];
    this->xres = xres;
    this->yres = yres;
    for (int i=0; i<3; i++) {
        buttons[i] = b[i];
        buttons[i].width = 100;
        buttons[i].height = 20;
        buttons[i].center.x = xres/4;
        buttons[i].center.y = yres/1.4 - (i+1)*60;
        //buttons[i].center.y = 500 - (i+1)*60;
    }
}

PauseGS::~PauseGS()
{
    delete [] buttons;
}

int PauseGS::procMouseInput(int x, int y)
{
    pButtonID btn;
    for (int i=0;i<3;i++) {
        if (yres - y < buttons[i].center.y + buttons[i].height &&
                yres - y > buttons[i].center.y - buttons[i].height &&
                x < buttons[i].center.x + buttons[i].width &&
                x > buttons[i].center.x - buttons[i].width) {
            // Output which button and its corressponding ID to verify button clicks
            cout << "Count: " << i << " Button: " << buttons[i].name << endl;
            btn = buttons[i].pbid;
        }
    }
    switch(btn) {
        case RESUME:
#ifdef SOUND
            alSourcePlay(njG.sound.menuSound); 
#endif
            return -1;
            break;
        case SAVE_GAME:
#ifdef SOUND
            alSourcePlay(njG.sound.menuSound); 
#endif
            njG.saveEntities(1);
            break;
        case PMAIN_MENU:
#ifdef SOUND
            alSourceStop(njG.sound.ambientSound);
            alSourcePlay(njG.sound.menuSound); 
#endif
            njG.player->resetInstance();
            njG.resetAllies();
            njG.resetEnemies();
        case RETREAT:
#ifdef SOUND
            alSourceStop(njG.sound.battleSound);
            alSourcePlay(njG.sound.ambientSound);
#endif
            return -2;
            break;
        case REST:
            njG.player->resetStats();
            for(int i=0; i<njG.allies->count;i++) {
                njG.allies[i].resetStats();
            }
            break;
    }
    return 0;

}

int PauseGS::procKeyInput(int key)
{
    return 0;//read keys
}

void PauseGS::drawGameState()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,xres,0,yres,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for (int i=0; i<3; i++) {
        //Draw Buttons
        Button *s;
        glColor3ub(130,130,130);
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
        //r.bot = yres - (170 +(i*60));
        //r.left = 200 ;
        r.bot = yres/.95 - (i+1)*60;
        r.left = xres/4 ;
        ggprint16(&r, 16, 0xFFFFFFFF, buttons[i].name.c_str());
    }
}

//=================================================//
//---------------- START OF MENUGS ----------------//
//=================================================//

MenuGS::MenuGS(int s, Button b[5][5], int xres, int yres)
{
    state = 0;
    size = s;
    name = "NAME";
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
            buttons[j][i].center.x = xres/2;
            buttons[j][i].center.y = yres/1.4 - (i+1)*60;
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
    for(int i=0;i<size;i++) {
        if(yres - y < buttons[state][i].center.y + buttons[state][i].height &&
                yres - y > buttons[state][i].center.y - buttons[state][i].height &&
                x < buttons[state][i].center.x + buttons[state][i].width &&
                x > buttons[state][i].center.x - buttons[state][i].width) {
            // Output which button and its corressponding ID to verify button clicks
            cout << "Count: " << i << " Button: " << buttons[state][i].name << endl;
            btn = buttons[state][i].bid;
        }
    }
    switch(btn) {
        case MAIN_MENU:
#ifdef SOUND
            alSourcePlay(njG.sound.menuSound);
#endif
            state = MAIN_MENU;
            break;
        case NEW_GAME:
#ifdef SOUND
            alSourcePlay(njG.sound.menuSound); 
#endif
            state = NEW_GAME;
            break;
        case LOAD_GAME:
#ifdef SOUND
            alSourcePlay(njG.sound.menuSound);
#endif
            state = LOAD_GAME;
            break;
        case HIGH_SCORES:
#ifdef SOUND
            alSourcePlay(njG.sound.menuSound); 
#endif
            //state = HIGH_SCORES;
            break;
        case CONTROLS:
#ifdef SOUND
            alSourcePlay(njG.sound.menuSound); 
#endif
            //state = CONTROLS;
            break;
        case EXIT:
#ifdef SOUND
            alSourcePlay(njG.sound.menuSound); 
            njG.sound.clearSounds();
#endif
            exit(0);
            break;
        case ARCHER:
            {
#ifdef SOUND
                alSourcePlay(njG.sound.menuSound); 
                alSourcePlay(njG.sound.ambientSound);
#endif
                if (Player::count != 0) {
                    Player::resetInstance();
                }
                Player *player = Player::setInstance("Archer");
                njG.spawnAllies(3);
                njG.spawnEnemies(3);
                //stops 'unused variable' warning
                (void)player;
                state = MAIN_MENU;
                return 1;
            }
            break;
        case SOLDIER:
            {
#ifdef SOUND
                alSourcePlay(njG.sound.menuSound); 
                alSourcePlay(njG.sound.ambientSound);
#endif
                if (Player::count != 0) {
                    Player::resetInstance();
                }
                Player *player = Player::setInstance("Soldier");
                njG.spawnAllies(3);
                njG.spawnEnemies(3);
                //stops 'unused variable' warning
                (void)player;
                state = MAIN_MENU;
                return 1;
            }
            break;
        case TANK:
            {
#ifdef SOUND
                alSourcePlay(njG.sound.menuSound); 
                alSourcePlay(njG.sound.ambientSound);
#endif
                if (Player::count != 0) {
                    Player::resetInstance();
                }
                Player *player = Player::setInstance("Tank");
                njG.spawnAllies(3);
                njG.spawnEnemies(3);
                //stops 'unused variable' warning
                (void)player;
                state = MAIN_MENU;
                return 1;
            }
            break;
        case NICK:
            {
#ifdef SOUND
                alSourcePlay(njG.sound.menuSound); 
                alSourcePlay(njG.sound.ambientSound);
#endif
                if (Player::count != 0) {
                    Player::resetInstance();
                }
                Player *player = Player::setInstance("Nick");
                njG.spawnAllies(3);
                njG.spawnEnemies(3);
                //stops 'unused variable' warning
                (void)player;
                state = MAIN_MENU;
                return 1;
            }
            break;
        case SAVE1:
            {
#ifdef SOUND
                alSourcePlay(njG.sound.menuSound); 
                alSourcePlay(njG.sound.ambientSound);
#endif
                if (njG.loadEntities(1)) {
                    state = MAIN_MENU;
                    return 1;
                }
                return 0;
            }
            break;
        case SAVE2:
            {
#ifdef SOUND
                alSourcePlay(njG.sound.menuSound); 
                alSourcePlay(njG.sound.ambientSound);
#endif
                if (njG.loadEntities(2)) {
                    state = MAIN_MENU;
                    return 1;
                }
                return 0;
            }
            break;
        case SAVE3:
            {
#ifdef SOUND
                alSourcePlay(njG.sound.menuSound); 
                alSourcePlay(njG.sound.ambientSound);
#endif
                if (njG.loadEntities(3)) {
                    state = MAIN_MENU;
                    return 1;
                }
                return 0;
            }
            break;
        case SAVE4:
            {
#ifdef SOUND
                alSourcePlay(njG.sound.menuSound); 
                alSourcePlay(njG.sound.ambientSound);
#endif
                if (njG.loadEntities(4)) {
                    state = MAIN_MENU;
                    return 1;
                }
                return 0;
            }
            break;
    }
    return 0;
}

int MenuGS::procKeyInput(int key)
{
    switch(key) {
        if(state == 0) {
            case XK_Escape:
                return -1;
        }
        case XK_a:
        case XK_A:
        if(state == 1 && name.size() < 4) {
            name = name +"A";
            cout << "Inserting A" << endl;
            cout << this->state << " " << name.size() << endl;

        }
        break;
        case XK_b:
        case XK_B:
        if(state == 1 && name.size() < 4) {
            name = name +"B";
            cout << "Inserting B" << endl;
        }
            break;
        case XK_c:
        case XK_C:
        if(state == 1 && name.size() < 4) {
            name = name +"C";
            cout << "Inserting C" << endl;
        }
            break;
        case XK_d:
        case XK_D:
        if(state == 1 && name.size() < 4) {
            name = name +"D";
            cout << "Inserting D" << endl;
        }
            break;
        case XK_e:
        case XK_E:
        if(state == 1 && name.size() < 4) {
            name = name +"E";
            cout << "Inserting E" << endl;
        }
            break;
        case XK_f:
        case XK_F:
        if(state == 1 && name.size() < 4) {
            name = name +"F";
            cout << "Inserting F" << endl;
        }
            break;
        case XK_g:
        case XK_G:
        if(state == 1 && name.size() < 4) {
            name = name +"G";
            cout << "Inserting G" << endl;
        }
            break;
        case XK_h:
        case XK_H:
        if(state == 1 && name.size() < 4) {
            name = name +"H";
            cout << "Inserting H" << endl;
        }
            break;
        case XK_i:
        case XK_I:
        if(state == 1 && name.size() < 4) {
            name = name +"I";
            cout << "Inserting I" << endl;
        }
            break;
        case XK_j:
        case XK_J:
        if(state == 1 && name.size() < 4) {
            name = name +"J";
            cout << "Inserting J" << endl;
        }
            break;
        case XK_k:
        case XK_K:
        if(state == 1 && name.size() < 4) {
            name = name +"K";
            cout << "Inserting K" << endl;
        }
            break;
        case XK_l:
        case XK_L:
        if(state == 1 && name.size() < 4) {
            name = name +"L";
            cout << "Inserting L" << endl;
        }
            break;
        case XK_m:
        case XK_M:
        if(state == 1 && name.size() < 4) {
            name = name +"M";
            cout << "Inserting M" << endl;
        }
            break;
        case XK_n:
        case XK_N:
        if(state == 1 && name.size() < 4) {
            name = name +"N";
            cout << "Inserting N" << endl;
        }
            break;
        case XK_o:
        case XK_O:
        if(state == 1 && name.size() < 4) {
            name = name +"O";
            cout << "Inserting O" << endl;
        }
            break;
        case XK_p:
        case XK_P:
        if(state == 1 && name.size() < 4) {
            name = name +"P";
            cout << "Inserting P" << endl;
        }
            break;
        case XK_q:
        case XK_Q:
        if(state == 1 && name.size() < 4) {
            name = name +"Q";
            cout << "Inserting Q" << endl;
        }
            break;
        case XK_r:
        case XK_R:
        if(state == 1 && name.size() < 4) {
            name = name +"R";
            cout << "Inserting R" << endl;
        }
            break;
        case XK_s:
        case XK_S:
        if(state == 1 && name.size() < 4) {
            name = name +"S";
            cout << "Inserting S" << endl;
        }
            break;
        case XK_t:
        case XK_T:
        if(state == 1 && name.size() < 4) {
            name = name +"T";
            cout << "Inserting T" << endl;
        }
            break;
        case XK_u:
        case XK_U:
        if(state == 1 && name.size() < 4) {
            name = name +"U";
            cout << "Inserting U" << endl;
        }
            break;
        case XK_v:
        case XK_V:
        if(state == 1 && name.size() < 4) {
            name = name +"V";
            cout << "Inserting V" << endl;
        }
            break;
        case XK_w:
        case XK_W:
        if(state == 1 && name.size() < 4) {
            name = name +"W";
            cout << "Inserting W" << endl;
        }
            break;
        case XK_x:
        case XK_X:
        if(state == 1 && name.size() < 4) {
            name = name +"X";
            cout << "Inserting X" << endl;
        }
            break;
        case XK_y:
        case XK_Y:
        if(state == 1 && name.size() < 4) {
            name = name +"Y";
            cout << "Inserting Y" << endl;
        }
            break;
        case XK_z:
        case XK_Z:
        if(state == 1 && name.size() < 4) {
            name = name +"Z";
            cout << "Inserting Z" << endl;
        }
            break;
        case XK_BackSpace:
        if(state == 1 && name.size() > 0) {
            name.pop_back();

        }
            break;
        default:
            break;
    };
    return 0;
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
        glColor3ub(130,130,130);
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
        //r.bot = yres - (170 +(i*60));
        r.bot = yres/.95 - (i+1)*60;
        r.left = xres/2 ;
        ggprint16(&r, 16, 0xFFFFFFFF, buttons[state][i].name.c_str());
        //buttons[j][i].center.x = xres/2;
        //buttons[j][i].center.y = yres/1.4 - (i+1)*60;
    }
    if(state == 1) {
        Rect r;
        r.bot = yres/1.25;
        r.left = xres/2;
        ggprint16(&r, 16, 0xFFFFFFFF, "Name:");
        r.bot = yres/1.3;
        ggprint16(&r, 16, 0xFFFFFFFF, this->name.c_str());
    }
}

//=================================================//
//---------------- START OF TOWNGS ----------------//
//=================================================//

TownGS::TownGS(Button b[3],int xres, int yres)
{
    buttons = new Button[3];
    this->xres = xres;
    this->yres = yres;
    for (int i=0; i<3; i++) {
        buttons[i] = b[i];
        buttons[i].width = 100;
        buttons[i].height = 20;
        buttons[i].center.x = xres/4;
        buttons[i].center.y = yres/1.4 - (i+1)*60;
        //buttons[i].center.y = 500 - (i+1)*60;
    }
}

TownGS::~TownGS()
{
    delete [] buttons;
}

int TownGS::procMouseInput(int x, int y)
{
    pButtonID btn;
    for (int i=0;i<3;i++) {
        if (yres - y < buttons[i].center.y + buttons[i].height &&
                yres - y > buttons[i].center.y - buttons[i].height &&
                x < buttons[i].center.x + buttons[i].width &&
                x > buttons[i].center.x - buttons[i].width) {
            // Output which button and its corressponding ID to verify button clicks
            cout << "Count: " << i << " Button: " << buttons[i].name << endl;
            btn = buttons[i].pbid;
        }
    }
    switch(btn) {
        case RESUME:
            return -1;
            break;
        case REST:
            njG.player->resetStats();
            break;
        case SAVE_GAME:
            break;
        case PMAIN_MENU:
            break;
        case RETREAT:
            break;
    }
    return 0;

}

int TownGS::procKeyInput(int key)
{
    return 0;//read keys
}

void TownGS::drawGameState()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,xres,0,yres,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    for (int i=0; i<3; i++) {
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
        //r.bot = yres - (170 +(i*60));
        //r.left = 200 ;
        r.bot = yres/.95 - (i+1)*60;
        r.left = xres/4 ;
        ggprint16(&r, 16, 0x00ffff00, buttons[i].name.c_str());
    }
}

//=================================================//
//--------------- START OF TITLEGS ----------------//
//=================================================//
TitleGS::TitleGS(int xres, int yres)
{
    this->xres = xres;
    this->yres = yres;
}

int TitleGS::procMouseInput(int,int)
{
    return 0;
}

int TitleGS::procKeyInput(int)
{
    return 6;
}

void TitleGS::drawGameState()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,xres,0,yres,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Rect r;
    r.bot = yres/2+100;
    r.left = xres/2;
    ggprint16(&r, 16, 0xFFFFFFFF, "Fate: The Shadow Wizard: Kingdom of Darkness: Revived: 2: The Second One");
    r.bot = yres/2;
    r.left = xres/2;
    ggprint16(&r, 16, 0xFFFFFFFF, "Press any key");
}
























