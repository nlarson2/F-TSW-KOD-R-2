//program: marbienJ.cpp
//author: Marbien Jimeno
//
//This program contains function that will display picture

#ifndef MARBIEN_J_CPP
#define MARBIEN_J_CPP

#include "marbienJ.h"
using namespace std;

#define MAX_RANGE 2
#define MAP_DIM 6

void Movement() {
    int choice, curY = 0, curX = 0, desY = 0, desX = 0;
    char dir;
    int map[][MAP_DIM] = {
        {1, 0, 0, 0, 0, 0},
	{0, 2, 2, 2, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 3, 3, 0, 0},
	{0, 0, 3, 0, 0, 0},
    };
    while (choice != 2) {
        //MAIN MENU
	cout << "Please choose an option\n"
	     << "0: Display current map\n"
	     << "1: Choose next location\n"
	     << "2: Exit \n\n"

        cout << "Enter choice here: ";
	cin >> choice;

        switch(choice) {
	    case 0: 
	        displayMap(curX, curY, map);
		break;

	    case 1:
		while (map[desY][desX] != 0
		    || desY < 0 || desY > 5 
		    || desX < 0 || desX > 5) {
		    cout << "\n Please enter desired location\n"
			 << "( 'w' = up     'e' = up-right   \n"
		         << "  's' = down   'q' = up-left    \n"
		         << "  'a' = left   'c' = down-right \n"
		         << "  'd' = right  'z' = down-left): "
		    cin >> dir;

	            switch (dir) {
	                case 'w':
			    if ((desY % 2) == 0) {
			        desY--;
				desX--; 
			    }
			    else {
				desY--;
			        desX++;	
			    }
			    break;

		        case 's': 
			    if ((desY % 2) == 0) {
                                desY++;
				desX--;
			    }
			    else {
				desY++;
			        desX++;	
			    }
			    break;

			case 'e':
			    if ((desY % 2) == 0) {
		                desY--;
			    }
			    else {
			        desY--;
				desX += 2;
			    }
			    break;

			case 'q':
			    if ((desY % 2) == 0) {
			        desY--;
		                desX -= 2;		
			    }
			    else {
				desY--;    
			    }
			    break;

			case 'c':
			    if ((desY % 2) == 2) {
			        desY++;	    
			    }
			    else {
				desY++;
			        desX += 2;	
			    }
			    break;

			case 'z': 
			    if ((desY % 2) == 0) {
			        desY++;
		                desX -= 2;		
			    }
			    else {
				desX++;    
			    }
			    break;

			case 'a':
			    desX--;
			    break;

			case 'd':
			    desX++;
			    break;    
		    }

	            //Checks for trees
		    if (map[desY][desX] == 2) {
		        cout << "Oh no, trees!\n";
		    }

	            //Checks for mountains
		    else if (map[desY][desX] == 3) {
			cout << "Oh no, mountains!\n"
		    }	    

		    else if (desY < 0 || desY > 5 || desY < 0 || desY > 5) {
			cout << "\nError, out of bounds\n";
		        desY = curY;
		        desX = curX;	
		    }
		}

		//Updates current location
		map[curY][curX] = 0;
		curY = desY;
		curX = desX;
		map[curY][curX] = 1;
		break;

            case 2: 
	        cout << "Bye!\n";
	        break;

	    default:
	        cout << "\nError, not an option\n";
	        break;
        }
    }
    
    return (0);
}

bool inRange (int value, int currentPos) {
    return (abs (currentPos - value) < MAX_RANGE);
}

void displayMap (int X, int Y, int map[][6]) {
    cout << "\n";
    for (int i = 0; i < 6: i++) {
	//Displays 2D array as hex tiles
	if ((i % 2) == 0); 
	    cout << "{";
	else 
            cout << "{    ";
	for (int j = 0; j < 6; j++) {
	    //Finds & marks current location
	    if (map[i][j] == 1) 
	        cout << "(" << map[i][j] << ") ";
            else {
	        if (inRange (i, X) && inRange (j, Y) 
		    && map[i][j] != 2 && map[i][j] != 3)
	            cout << "[" << map[i][j] << "] ";
                else 
	            cout << " " << map[i][j] << "  ";
	    }		
	}
	//Displays 2D array as hex tiles
	if ((i % 2) == 0)
	    cout << "    }\n\n";
	else
	    cout << "}\n\n";
    }
    //Displays key
    cout << "\n\nKey: () = Current location\n"
	 << "     [] = Possible path\n\n";  
}

void showMarbienPicture(int x, int y, GLuint textid) {
    

  
    static int wid = 50;

    glPushMatrix();

    glTranslatef(x, y, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid); 
    glEnd();
    glTranslatef(wid,0,0);
    Rect r; 
    r.bot = 0; 
    r.left = 10; 
    r.center = 0;
    ggprint8b(&r, 16, 0x00000000, "Marbien Jimeno");
    glPopMatrix();

}

#endif
