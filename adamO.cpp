

#ifndef ADAMO_CPP
#define ADAMO_CPP
// Adam Ostlund
#include "adamO.h"


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
    Boxes box[10] = {
        Boxes(BOX),
        Boxes(END_TURN),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX),
        Boxes(BOX)
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
    boxes[0].width = 150;
    boxes[0].height = 200;
    boxes[0].center.x = 75;
    boxes[0].center.y = 100;
    //
    
    // Turn Change Box
    boxes[1].width = xres/16;
    boxes[1].height = yres/12;
    boxes[1].center.x = xres-(xres/16);
    boxes[1].center.y = yres/12;
    //

    // Battle Mode Box
    boxes[2].width = xres*0.2;
    boxes[2].height = yres/20;
    boxes[2].center.x = xres-(xres*0.2);
    boxes[2].center.y = yres-(yres/20);
    //

    // Character Image Box
    boxes[3].width = 75;
    boxes[3].height = 75;
    boxes[3].center.x = 110;
    boxes[3].center.y = 195;

    // Character Info Background Box
    boxes[4].width = 75;
    boxes[4].height = 40;
    boxes[4].center.x = 110;
    boxes[4].center.y = 65;

    // Character Name Box
    boxes[5].width = 70;
    boxes[5].height = 10;
    boxes[5].center.x = 110;
    boxes[5].center.y = 90;

    // Character Health Bar Box
    boxes[6].width = 70;
    boxes[6].height = 10;
    boxes[6].center.x = 110;
    boxes[6].center.y = 65;

    // Character Movements Left Box
    boxes[7].width = 70;
    boxes[7].height = 10;
    boxes[7].center.x = 110;
    boxes[7].center.y = 40;
    //

    /*
       // Enemy Name Box
       box[8].width = ;
       box[8].height = ;
       box[8].center.x = ;
       box[8].center.y = ;

       // Enemy Health Bar Box
       box[9].width = ;
       box[9].height = ;
       box[9].center.x = ;
       box[9].center.y = ;
       //
    */

}

void uiboxes::drawBoxes() {
        

    
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, xres, 0, yres, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

    for (int i = 0; i < 8; i++) {
        Boxes *s;
        glColor3ub(90, 140, 90);
        if (i == 3 || i > 4)
            glColor3ub(0,250,250);
        if (i == 4)
            glColor3ub(250,250,0);
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
