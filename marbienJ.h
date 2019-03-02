//program: marbienJ.h
//author: Marbien Jimeno
//
//This program is a header file containing function prototype
 
#ifndef MARBIEN_J_H
#define MARBIEN_J_H

#include <GL/glx.h>
#include "fonts.h"
#include <iostream>
#include <cmath>

void Movement();
bool inRange(int, int);
void displayMap(int, int, int[][6]);
void showMarbienPicture(int x, int y, GLuint textid);

#endif
