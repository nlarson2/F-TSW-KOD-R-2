//Brandon Hernandez
//Lab 04
//Display name/picture in credits menu

#include "brandonH.h"

void brandonH(int x, int y,GLuint textid) 
{
    Rect r;
    r.bot = 60;
    r.left = 10;
    r.center = 0;
    ggprint8b (&r, 16, 0x00ffff44, "Brandon Hernandez");
    glColor3ub(255,255,255);
    static int wid = 30;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, textid);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}
