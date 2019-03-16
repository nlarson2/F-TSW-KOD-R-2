//program: marbienJ.h
//author: Marbien Jimeno
//
//This program is a header file containing function prototype
 
#ifndef MARBIEN_J_H
#define MARBIEN_J_H

#include <GL/glx.h>
#include "fonts.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

/*int Movement(int);
bool inRange(int, int);
void displayMap(int, int, int[][6]);*/

#define ROW 25 
#define COL 25 
  
// shortcut for int, int pair type 
typedef pair<int, int> Pair; 
  
// shortcut for pair<int, pair<int, int>> type 
typedef pair<double, pair<int, int>> pPair; 
   
struct cell 
{ 
    // Row and Column index of its parent 
    int parent_i, parent_j; 
    // f = g + h 
    double f, g, h; 
};

bool isValid(int, int);
bool isUnBlocked(int[][25], int, int);
bool isDestination(int, int, Pair);
double calculateHValue(int, int, Pair);
void tracePath(cell[][25], Pair dest);
void aStarSearch(int[][25], Pair src, Pair dest);
void displayMap(int[][25]);

void Movement(int[][25], int, int, int, int); 
void showMarbienPicture(int x, int y, GLuint textid);

#endif
