

#ifndef ADAMO_CPP
#define ADAMO_CPP
// Adam Ostlund
#include "adamO.h"
#include "nicholasJo.h"

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



//extern void opengl();

AOglobal::AOglobal() {
    Boxes box[11] = {
        Boxes(BOX),
        Boxes(END_TURN),
        Boxes(BATTLE),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BATTLE),
        Boxes(BATTLE)
    };
}

AOglobal aog;

Boxes::Boxes() {
}

Boxes::Boxes(stateID sID) {
    ID = sID;
}


void uiboxes::posBoxes() {

    // Character Frame Box
    boxes[0].width = (xres*0.0625) + 35;
    boxes[0].height = (yres/6);
    boxes[0].center.x = ((xres*11)/120);
    boxes[0].center.y = (yres/6);
    //

    // Character Pane Box
    boxes[1].width = (xres*0.0625) + 30;
    boxes[1].height = (yres/6) - 5;
    boxes[1].center.x = (xres*11)/120; 
    boxes[1].center.y = (yres/6);
    
    // Turn Change Box
    boxes[2].width = 60;
    boxes[2].height = 60;
    boxes[2].center.x = xres - 60;
    boxes[2].center.y = 60;
    //

    // Battle Mode Box
    boxes[3].width = 75;
    boxes[3].height = 27.5;
    boxes[3].center.x = xres - 75;
    boxes[3].center.y = yres - 27.5;
    //

    // Character Image Box
    boxes[4].width = 75;
    boxes[4].height = 75;
    boxes[4].center.x = 110;
    boxes[4].center.y = 195;

    // Character Info Background Box
    boxes[5].width = 75;
    boxes[5].height = 40;
    boxes[5].center.x = 110;
    boxes[5].center.y = 65;

    // Character Name Box
    boxes[6].width = 70;
    boxes[6].height = 10;
    boxes[6].center.x = 110;
    boxes[6].center.y = 90;

    // Character Health Bar Box
    boxes[7].width = 70;
    boxes[7].height = 10;
    boxes[7].center.x = 110;
    boxes[7].center.y = 65;

    // Character Movements Left Box
    boxes[8].width = 70;
    boxes[8].height = 10;
    boxes[8].center.x = 110;
    boxes[8].center.y = 40;
        
    // Enemy Name Box
    boxes[9].width = 70;
    boxes[9].height = 10;
    boxes[9].center.x = xres - 75;
    boxes[9].center.y = yres - 15;
    
       
    // Enemy Health Bar Box
    boxes[10].width = 70;
    boxes[10].height = 10;
    boxes[10].center.x = xres - 75;
    boxes[10].center.y = yres - 40;
    //
  
    

}

void uiboxes::drawBoxes() {
        

   glPushMatrix(); 
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, xres, 0, yres, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    for (int i = 0; i < 11; i++) {
        Boxes *s;
        glColor3ub(90, 140, 90);
        if (i > 5 || i == 1 || i >= 9)
            glColor3ub(40,40,40);
        if (i == 2 || i == 5 || i == 3 || i == 4 || i == 0)
            glColor3ub(130,130,130);
        s = &boxes[i];
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(s->center.x, s->center.y, 0);
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
    }
    Rect r;
    Player *player = Player::getInstance();

    
    r.bot = 78;
    r.left = 110;
    ggprint16(&r, 16, 0xffffffff, player->combatType.c_str());
    
    r.bot = 53;
    r.left = 90;
    string hc;
    hc = std::to_string((int)player->getCurrentHealth());
    if (player->getCurrentHealth() <= player->getMaxHealth() / 2)
        ggprint16(&r, 16, 0xfff00000, hc.c_str());
    else
        ggprint16(&r, 16, 0xffffffff, hc.c_str());
    
    r.bot = 53;
    r.left = 130;
    string hm;
    hm = std::to_string((int)player->getMaxHealth());
    if (player->getCurrentHealth() <= player->getMaxHealth() / 2)
        ggprint16(&r, 16, 0xfff00000, hm.c_str());
    else 
        ggprint16(&r, 16, 0xffffffff, hm.c_str());
    
    r.bot = 53;
    r.left = 110;
    ggprint16(&r, 16, 0xffffffff, "/");
    
    r.bot = 28;
    r.left = 110;
    string mv = to_string(player->moveRange);
    string mv2 = mv;
    ggprint16(&r, 16, 0xffffffff, mv2.c_str());
    
    glPushMatrix();
    glTranslatef(boxes[4].center.x, boxes[4].center.y, 0);
    glColor3ub(250,250,250);
    glBindTexture(GL_TEXTURE_2D, player->image);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-boxes[4].width+5,-boxes[4].width+5);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-boxes[4].width+5, boxes[4].width-5);
        glTexCoord2f(1.0f, 0.0f); glVertex2i( boxes[4].width-5, boxes[4].width-5);
        glTexCoord2f(1.0f, 1.0f); glVertex2i( boxes[4].width-5,-boxes[4].width+5);
    glEnd();

    glPopMatrix();
    glPopMatrix();
}

//=====================================//
//------------- UI BOXES --------------//
//=====================================//

uiboxes::uiboxes(Boxes b[10], float xres, float yres)
{
    size = 10;
    this->xres = xres;
    this->yres = yres;
    for(int i = 0; i < size; i++)
        boxes[i] = b[i];
    posBoxes();

}

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
}



#endif
