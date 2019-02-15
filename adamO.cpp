//3350
//program: adamO.cpp
//author: adam ostlund
//date: february 14, 2019
//
//This program is an individual source file containing a name and profile picture.
//
//

#include "adamO.h"

void showAdamPicture(int x, int y, GLuint textid) {
    
    Rect r;
    r.bot = 200;
    r.left = 300;
    r.center = 100;
    ggprint8b (&r, 16, 0x00ffff44, "Adam Ostlund");
    
    
    glColor3ub(255,255,255);
    static int wid = 100;
    float fx = (float)x + 100;
    float fy = (float)y + 100;;
        
    
    glPushMatrix();
    glTranslatef(fx,fy,0);
    
    glBindTexture(GL_TEXTURE_2D, textid);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
    glEnd();
    glPopMatrix();
}
