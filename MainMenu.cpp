#include "MainMenu.h"

Button::Button()
{
}
Button::Button(string n)
{
    name = n;
}
Button::~Button()
{
}

Menu::Menu(int s, Button * b)
{
    size = s;
    buttons = new Button[size];
    for(int i = 0; i < size; i++)
        buttons[i] = b[i];
    posButtons();
}

Menu::~Menu()
{
    delete [] buttons;
}


void Menu::drawNames(int i)
{
    int yres = 600;
    Rect r;
    r.bot = yres - (170 +(i*60));
    r.left = 500 ;
    ggprint16(&r, 16, 0x00ffff00, buttons[i].name.c_str());
}

void Menu::posButtons()
{
    for (int i=0; i<size; i++) {
        buttons[i].width = 100;
        buttons[i].height = 20; 
        buttons[i].center.x = 500;
        buttons[i].center.y = 500 - (i+1)*60;
    }
}

void Menu::drawButtons()
{
    for(int i = 0; i < size; i++) {
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

int Menu::check_mouse(int savex, int savey, int yres)
{
    for(int i=0;i<size;i++) {
        if(yres - savey < buttons[i].center.y + buttons[i].height && yres - savey > buttons[i].center.y - buttons[i].height &&
                savex < buttons[i].center.x + buttons[i].width && savex > buttons[i].center.x - buttons[i].width) {
            cout << "Count: " << i << " Button: " << buttons[i].name << endl;
            return i;
        }
    }
    return 100;
}

