//program: marbienJ.cpp
//author: Marbien Jimeno
//
//This program contains function that will display picture

#ifndef MARBIEN_J_CPP
#define MARBIEN_J_CPP

#include "marbienJ.h"
using namespace std;

/*
#define MAX_RANGE 2
#define MAP_DIM 6

int Movement() 
{
    int choice, curY = 0, curX = 0, desY = 0, desX = 0;
    char dir;
    int map[][MAP_DIM] = {
        {1, 0, 0, 0, 0, 0},
	{0, 2, 2, 2, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 3, 3, 0, 0},
	{0, 0, 3, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
    };
    while (choice != 2) {
        //MAIN MENU
	cout << "Please choose an option\n"
	     << "0: Display current map\n"
	     << "1: Choose next location\n"
	     << "2: Exit \n\n";

        cout << "Enter choice here: ";
	cin >> choice;

        switch(choice) {
	    case 0: 
	        displayMap(curX, curY, map);
		break;

	    case 1:
		while (map[desY][desX] != 0 || desY < 0 || desY > 5 || desX < 0 || desX > 5) {
		    cout << "\n Please enter desired location\n"
			 << "( 'w' = up     'e' = up-right   \n"
		         << "  's' = down   'q' = up-left    \n"
		         << "  'a' = left   'c' = down-right \n"
		         << "  'd' = right  'z' = down-left): ";
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
			    if ((desY % 2) == 0) {
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
				desY++;    
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
			cout << "Oh no, mountains!\n";
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
    
    return 0;
}

bool inRange (int value, int currentPos) 
{
    return (abs (currentPos - value) < MAX_RANGE);
}

void displayMap (int X, int Y, int map[][6]) 
{
    cout << "\n";
    for (int i = 0; i < 6; i++) {
	//Displays 2D array as hex tiles
	if ((i % 2) == 0) 
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
}*/


bool isValid(int row, int col) 
{ 
    // in range? 
    return (row >=  0) && (row < ROW) && 
           (col >= 0) && (col < COL); 
} 
  
bool isUnBlocked(int grid[][COL], int row, int col) 
{ 
    // true if blocked else false 
    if (grid[row][col] == 0) 
        return (true); 
    else
        return (false); 
} 
   
bool isDestination(int row, int col, Pair dest) 
{ 
    if (row == dest.first && col == dest.second) 
        return (true); 
    else
        return (false); 
} 
  
// calculate the 'h' heuristics. 
double calculateHValue(int row, int col, Pair dest) 
{ 
    // distance formula 
    return ((double)sqrt ((row-dest.first)*(row-dest.first) 
                          + (col-dest.second)*(col-dest.second))); 
} 
  
// trace path from the source to destination
void tracePath(cell cellDetails[][COL], Pair dest) 
{ 
    printf ("\nThe Path is: \n"); 
    int row = dest.first; 
    int col = dest.second; 
  
    stack<Pair> Path; 
  
    while (!(cellDetails[row][col].parent_i == row 
             && cellDetails[row][col].parent_j == col )) 
    { 
        Path.push (make_pair (row, col)); 
        int temp_row = cellDetails[row][col].parent_i; 
        int temp_col = cellDetails[row][col].parent_j; 
        row = temp_row; 
        col = temp_col; 
    } 
  
    Path.push (make_pair (row, col)); 
    while (!Path.empty()) 
    { 
        pair<int,int> p = Path.top(); 
        Path.pop(); 
        printf("-> (%d,%d) \n",p.first,p.second); 
    } 
  
    return; 
} 
  
// A* Search Algorithm 
void aStarSearch(int grid[][COL], Pair src, Pair dest) 
{ 
    // source is out of range? 
    if (isValid (src.first, src.second) == false) 
    { 
        printf ("Source is invalid\n"); 
        return; 
    } 
  
    // destination is out of range? 
    if (isValid (dest.first, dest.second) == false) 
    { 
        printf ("Destination is invalid\n"); 
        return; 
    } 
  
    // source or the destination is blocked? 
    if (isUnBlocked(grid, src.first, src.second) == false || 
            isUnBlocked(grid, dest.first, dest.second) == false) 
    { 
        printf ("Source or the destination is blocked\n"); 
        return; 
    } 
  
    // destination cell = source cell? 
    if (isDestination(src.first, src.second, dest) == true) 
    { 
        printf ("We are already at the destination\n"); 
        return; 
    } 
  
    // closed list and initialise false 
    // no cell included yet 
    // closed list implemented as boolean 2D array 
    bool closedList[ROW][COL]; 
    memset(closedList, false, sizeof (closedList)); 
  
    // 2D array structure to hold details of cell 
    cell cellDetails[ROW][COL]; 
  
    int i, j; 
  
    for (i=0; i<ROW; i++) 
    { 
        for (j=0; j<COL; j++) 
        { 
            cellDetails[i][j].f = FLT_MAX; 
            cellDetails[i][j].g = FLT_MAX; 
            cellDetails[i][j].h = FLT_MAX; 
            cellDetails[i][j].parent_i = -1; 
            cellDetails[i][j].parent_j = -1; 
        } 
    } 
  
    // parameters of the starting node 
    i = src.first, j = src.second; 
    cellDetails[i][j].f = 0.0; 
    cellDetails[i][j].g = 0.0; 
    cellDetails[i][j].h = 0.0; 
    cellDetails[i][j].parent_i = i; 
    cellDetails[i][j].parent_j = j; 
  
    /* 
     open list 
     <f, <i, j>> 
     where f = g + h, 
     and i = row and j = column index 
     open list implenented set of pair of pair.*/
    set<pPair> openList; 
  
    // starting cell on open list 
    // 'f' = 0 
    openList.insert(make_pair (0.0, make_pair (i, j))); 
   
    bool foundDest = false; 
  
    while (!openList.empty()) { 
        pPair p = *openList.begin(); 
  
        openList.erase(openList.begin()); 
  
        // Add vertex closed list 
        i = p.second.first; 
        j = p.second.second; 
        closedList[i][j] = true; 
       
        double gNew, hNew, fNew; 
  
        //----------- (North) ------------ 
        if ((i % 2) == 0) { 	 
            if (isValid(i-1, j-1) == true) {  
                if (isDestination(i-1, j-1, dest) == true) { 
                    // set parent of destination cell 
                    cellDetails[i-1][j-1].parent_i = i; 
                    cellDetails[i-1][j-1].parent_j = j; 
                    printf ("The destination cell is found\n"); 
                    tracePath (cellDetails, dest); 
                    foundDest = true; 
                    return; 
                }  
                else if (closedList[i-1][j-1] == false && 
                         isUnBlocked(grid, i-1, j-1) == true) { 
                    gNew = cellDetails[i][j].g + 1.0; 
                    hNew = calculateHValue (i-1, j-1, dest); 
                    fNew = gNew + hNew; 
  
                    // If it isn’t on the open list, add it to 
                    // the open list. Make the current square 
                    // the parent of this square. Record the 
                    // f, g, and h costs of the square cell 
                    //                OR 
                    // If it is on the open list already, check 
                    // to see if this path to that square is better, 
                    // using 'f' cost as the measure. 
                    if (cellDetails[i-1][j-1].f == FLT_MAX || 
                            cellDetails[i-1][j-1].f > fNew) { 
                        openList.insert(make_pair(fNew, 
                                        make_pair(i-1, j-1))); 
  
                        // Update details of cell 
                        cellDetails[i-1][j-1].f = fNew; 
                        cellDetails[i-1][j-1].g = gNew; 
                        cellDetails[i-1][j-1].h = hNew; 
                        cellDetails[i-1][j-1].parent_i = i; 
                        cellDetails[i-1][j-1].parent_j = j; 
                    } 
                }
            } 
        } 
	    else {
            if (isValid(i-1, j+1) == true) {  
                if (isDestination(i-1, j+1, dest) == true) { 
                    // Set Parent destination cell 
                    cellDetails[i-1][j+1].parent_i = i; 
                    cellDetails[i-1][j+1].parent_j = j; 
                    printf ("The destination cell is found\n"); 
                    tracePath (cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i-1][j+1] == false && 
                         isUnBlocked(grid, i-1, j+1) == true) { 
                    gNew = cellDetails[i][j].g + 1.0; 
                    hNew = calculateHValue (i-1, j+1, dest); 
                    fNew = gNew + hNew; 
  
                    // If not on open list, add to 
                    // open list. Make current square 
                    // the parent. Record the 
                    // f, g, and h costs square cell 
                    //                OR 
                    // If on the open list already, check 
                    // if this path to that square is better, 
                    // using 'f' cost as the measure. 
                    if (cellDetails[i-1][j+1].f == FLT_MAX || 
                            cellDetails[i-1][j+1].f > fNew) { 
                        openList.insert(make_pair(fNew, 
                                        make_pair(i-1, j+1))); 
  
                        // Update details of cell 
                        cellDetails[i-1][j+1].f = fNew; 
                        cellDetails[i-1][j+1].g = gNew; 
                        cellDetails[i-1][j+1].h = hNew; 
                        cellDetails[i-1][j+1].parent_i = i; 
                        cellDetails[i-1][j+1].parent_j = j; 
                    } 
                }
            } 
	    } 
        //----------- (South) ------------ 
 	    if ((i % 2) == 0) {  
            if (isValid(i+1, j-1) == true) { 
                if (isDestination(i+1, j-1, dest) == true) { 
                    cellDetails[i+1][j-1].parent_i = i; 
                    cellDetails[i+1][j-1].parent_j = j; 
                    printf("The destination cell is found\n"); 
                    tracePath(cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i+1][j-1] == false && 
                         isUnBlocked(grid, i+1, j-1) == true) { 
                    gNew = cellDetails[i][j].g + 1.0; 
                    hNew = calculateHValue(i+1, j-1, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i+1][j-1].f == FLT_MAX || 
                            cellDetails[i+1][j-1].f > fNew) { 
                        openList.insert(make_pair (fNew, make_pair (i+1, j-1))); 
                        cellDetails[i+1][j-1].f = fNew; 
                        cellDetails[i+1][j-1].g = gNew; 
                        cellDetails[i+1][j-1].h = hNew; 
                        cellDetails[i+1][j-1].parent_i = i; 
                        cellDetails[i+1][j-1].parent_j = j; 
                    } 
                } 
            }
	    } 
	    else {
            if (isValid(i+1, j+1) == true) { 
                if (isDestination(i+1, j+1, dest) == true) { 
                    cellDetails[i+1][j+1].parent_i = i; 
                    cellDetails[i+1][j+1].parent_j = j; 
                    printf("The destination cell is found\n"); 
                    tracePath(cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i+1][j+1] == false && 
                         isUnBlocked(grid, i+1, j+1) == true) { 
                    gNew = cellDetails[i][j].g + 1.0; 
                    hNew = calculateHValue(i+1, j+1, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i+1][j+1].f == FLT_MAX || 
                            cellDetails[i+1][j+1].f > fNew) { 
                        openList.insert(make_pair (fNew, make_pair (i+1, j+1)));
                        cellDetails[i+1][j+1].f = fNew; 
                        cellDetails[i+1][j+1].g = gNew; 
                        cellDetails[i+1][j+1].h = hNew; 
                        cellDetails[i+1][j+1].parent_i = i; 
                        cellDetails[i+1][j+1].parent_j = j; 
                    } 
                } 
            }	
	    }
  
        //----------- (East) ------------ 
        if (isValid (i, j+1) == true) 
        { 
            if (isDestination(i, j+1, dest) == true) 
            { 
                cellDetails[i][j+1].parent_i = i; 
                cellDetails[i][j+1].parent_j = j; 
                printf("The destination cell is found\n"); 
                tracePath(cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
            else if (closedList[i][j+1] == false && 
                     isUnBlocked (grid, i, j+1) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.0; 
                hNew = calculateHValue (i, j+1, dest); 
                fNew = gNew + hNew; 
                if (cellDetails[i][j+1].f == FLT_MAX || 
                        cellDetails[i][j+1].f > fNew) 
                { 
                    openList.insert(make_pair(fNew, 
                                    make_pair (i, j+1))); 
                    cellDetails[i][j+1].f = fNew; 
                    cellDetails[i][j+1].g = gNew; 
                    cellDetails[i][j+1].h = hNew; 
                    cellDetails[i][j+1].parent_i = i; 
                    cellDetails[i][j+1].parent_j = j; 
                } 
            } 
        } 
  
        //----------- 4th Successor (West) ------------ 
        if (isValid(i, j-1) == true) 
        { 
            if (isDestination(i, j-1, dest) == true) 
            { 
                cellDetails[i][j-1].parent_i = i; 
                cellDetails[i][j-1].parent_j = j; 
                printf("The destination cell is found\n"); 
                tracePath(cellDetails, dest); 
                foundDest = true; 
                return; 
            } 
            else if (closedList[i][j-1] == false && 
                     isUnBlocked(grid, i, j-1) == true) 
            { 
                gNew = cellDetails[i][j].g + 1.0; 
                hNew = calculateHValue(i, j-1, dest); 
                fNew = gNew + hNew; 
                if (cellDetails[i][j-1].f == FLT_MAX || 
                        cellDetails[i][j-1].f > fNew) 
                { 
                    openList.insert(make_pair (fNew, 
                                    make_pair (i, j-1))); 
                    cellDetails[i][j-1].f = fNew; 
                    cellDetails[i][j-1].g = gNew; 
                    cellDetails[i][j-1].h = hNew; 
                    cellDetails[i][j-1].parent_i = i; 
                    cellDetails[i][j-1].parent_j = j; 
                } 
            } 
        } 
  
        //----------- (North-East) ------------ 
  	    if ((i % 2) == 0) {
            if (isValid(i-1, j) == true) { 
                if (isDestination(i-1, j, dest) == true) { 
                    cellDetails[i-1][j].parent_i = i; 
                    cellDetails[i-1][j].parent_j = j; 
                    printf ("The destination cell is found\n"); 
                    tracePath (cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i-1][j] == false && 
                         isUnBlocked(grid, i-1, j) == true) { 
                    gNew = cellDetails[i][j].g + 1.414; 
                    hNew = calculateHValue(i-1, j, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i-1][j].f == FLT_MAX || 
                            cellDetails[i-1][j].f > fNew) { 
                        openList.insert(make_pair (fNew,  
                                        make_pair(i-1, j))); 
                        cellDetails[i-1][j].f = fNew; 
                        cellDetails[i-1][j].g = gNew; 
                        cellDetails[i-1][j].h = hNew; 
                        cellDetails[i-1][j].parent_i = i; 
                        cellDetails[i-1][j].parent_j = j; 
                    } 
                } 
            } 
        }
        else {
            if (isValid(i-1, j+2) == true) { 
                if (isDestination(i-1, j+2, dest) == true) { 
                    cellDetails[i-1][j+2].parent_i = i; 
                    cellDetails[i-1][j+2].parent_j = j; 
                    printf ("The destination cell is found\n"); 
                    tracePath (cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i-1][j+2] == false && 
                         isUnBlocked(grid, i-1, j+2) == true) { 
                    gNew = cellDetails[i][j].g + 1.414; 
                    hNew = calculateHValue(i-1, j+2, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i-1][j+2].f == FLT_MAX || 
                            cellDetails[i-1][j+2].f > fNew) { 
                        openList.insert(make_pair (fNew,  
                                        make_pair(i-1, j+2))); 
                        cellDetails[i-1][j+2].f = fNew; 
                        cellDetails[i-1][j+2].g = gNew; 
                        cellDetails[i-1][j+2].h = hNew; 
                        cellDetails[i-1][j+2].parent_i = i; 
                        cellDetails[i-1][j+2].parent_j = j; 
                    } 
                } 
            } 
        }  
        //----------- (North-West) ------------ 
        if ((i % 2) == 0) {
            if (isValid (i-1, j-2) == true) { 
                if (isDestination (i-1, j-2, dest) == true) { 
                    cellDetails[i-1][j-2].parent_i = i; 
                    cellDetails[i-1][j-2].parent_j = j; 
                    printf ("The destination cell is found\n"); 
                    tracePath (cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i-1][j-2] == false && 
                        isUnBlocked(grid, i-1, j-2) == true) { 
                    gNew = cellDetails[i][j].g + 1.414; 
                    hNew = calculateHValue(i-1, j-2, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i-1][j-2].f == FLT_MAX || 
                        cellDetails[i-1][j-2].f > fNew) { 
                        openList.insert( make_pair (fNew, make_pair (i-1, j-2))); 
                        cellDetails[i-1][j-2].f = fNew; 
                        cellDetails[i-1][j-2].g = gNew; 
                        cellDetails[i-1][j-2].h = hNew; 
                        cellDetails[i-1][j-2].parent_i = i; 
                        cellDetails[i-1][j-2].parent_j = j; 
                    } 
                } 
            } 
        }
        else {
            if (isValid (i-1, j) == true) { 
                if (isDestination (i-1, j, dest) == true) { 
                    cellDetails[i-1][j].parent_i = i; 
                    cellDetails[i-1][j].parent_j = j; 
                    printf ("The destination cell is found\n"); 
                    tracePath (cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i-1][j] == false && 
                        isUnBlocked(grid, i-1, j) == true) { 
                    gNew = cellDetails[i][j].g + 1.414; 
                    hNew = calculateHValue(i-1, j, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i-1][j].f == FLT_MAX || 
                        cellDetails[i-1][j].f > fNew) { 
                        openList.insert( make_pair (fNew, make_pair (i-1, j))); 
                        // Update the details of this cell 
                        cellDetails[i-1][j].f = fNew; 
                        cellDetails[i-1][j].g = gNew; 
                        cellDetails[i-1][j].h = hNew; 
                        cellDetails[i-1][j].parent_i = i; 
                        cellDetails[i-1][j].parent_j = j; 
                    } 
                } 
            } 
        }
        //----------- (South-East) ------------ 
        if ((i % 2) == 0) {
            if (isValid(i+1, j) == true) { 
                if (isDestination(i+1, j, dest) == true) { 
                    cellDetails[i+1][j].parent_i = i; 
                    cellDetails[i+1][j].parent_j = j; 
                    printf ("The destination cell is found\n"); 
                    tracePath (cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i+1][j] == false && 
                        isUnBlocked(grid, i+1, j) == true) { 
                    gNew = cellDetails[i][j].g + 1.414; 
                    hNew = calculateHValue(i+1, j, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i+1][j].f == FLT_MAX || 
                            cellDetails[i+1][j].f > fNew) 
                    { 
                        openList.insert(make_pair(fNew,  
                                            make_pair (i+1, j))); 
                        cellDetails[i+1][j].f = fNew; 
                        cellDetails[i+1][j].g = gNew; 
                        cellDetails[i+1][j].h = hNew; 
                        cellDetails[i+1][j].parent_i = i; 
                        cellDetails[i+1][j].parent_j = j; 
                    } 
                } 
            } 
        }
        else {
            if (isValid(i+1, j+2) == true) { 
                if (isDestination(i+1, j+2, dest) == true) { 
                    cellDetails[i+1][j+2].parent_i = i; 
                    cellDetails[i+1][j+2].parent_j = j; 
                    printf ("The destination cell is found\n"); 
                    tracePath (cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i+1][j+2] == false && 
                        isUnBlocked(grid, i+1, j+2) == true) { 
                    gNew = cellDetails[i][j].g + 1.414; 
                    hNew = calculateHValue(i+1, j+2, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i+1][j+2].f == FLT_MAX || 
                            cellDetails[i+1][j+2].f > fNew) 
                    { 
                        openList.insert(make_pair(fNew,  
                                            make_pair (i+1, j+2))); 
                        cellDetails[i+1][j+2].f = fNew; 
                        cellDetails[i+1][j+2].g = gNew; 
                        cellDetails[i+1][j+2].h = hNew; 
                        cellDetails[i+1][j+2].parent_i = i; 
                        cellDetails[i+1][j+2].parent_j = j; 
                    } 
                } 
            }
        }
        //----------- (South-West) ------------ 
        if ((i % 2) == 0) {
            if (isValid (i+1, j-2) == true) { 
                if (isDestination(i+1, j-2, dest) == true) { 
                    cellDetails[i+1][j-2].parent_i = i; 
                    cellDetails[i+1][j-2].parent_j = j; 
                    printf("The destination cell is found\n"); 
                    tracePath(cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i+1][j-2] == false && 
                         isUnBlocked(grid, i+1, j-2) == true) { 
                    gNew = cellDetails[i][j].g + 1.414; 
                    hNew = calculateHValue(i+1, j-2, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i+1][j-2].f == FLT_MAX || 
                        cellDetails[i+1][j-2].f > fNew) 
                    { 
                        openList.insert(make_pair(fNew,  
                                        make_pair(i+1, j-2))); 
                        cellDetails[i+1][j-2].f = fNew; 
                        cellDetails[i+1][j-2].g = gNew; 
                        cellDetails[i+1][j-2].h = hNew; 
                        cellDetails[i+1][j-2].parent_i = i; 
                        cellDetails[i+1][j-2].parent_j = j; 
                    } 
                } 
            }  
        } 
        else { 
            if (isValid (i+1, j) == true) { 
                if (isDestination(i+1, j, dest) == true) { 
                    cellDetails[i+1][j].parent_i = i; 
                    cellDetails[i+1][j].parent_j = j; 
                    printf("The destination cell is found\n"); 
                    tracePath(cellDetails, dest); 
                    foundDest = true; 
                    return; 
                } 
                else if (closedList[i+1][j] == false && 
                         isUnBlocked(grid, i+1, j) == true) { 
                    gNew = cellDetails[i][j].g + 1.414; 
                    hNew = calculateHValue(i+1, j, dest); 
                    fNew = gNew + hNew; 
                    if (cellDetails[i+1][j].f == FLT_MAX || 
                        cellDetails[i+1][j].f > fNew) 
                    { 
                        openList.insert(make_pair(fNew,  
                                        make_pair(i+1, j))); 
                        cellDetails[i+1][j].f = fNew; 
                        cellDetails[i+1][j].g = gNew; 
                        cellDetails[i+1][j].h = hNew; 
                        cellDetails[i+1][j].parent_i = i; 
                        cellDetails[i+1][j].parent_j = j; 
                    } 
                } 
            } 
        }
    } 
    if (foundDest == false) 
        printf("Failed to find the Destination Cell\n"); 
  
    return; 
} 

void displayMap(int map[ROW][COL])
{
    cout << "\n";
    for(int i = 0; i < ROW; ++i) {
        //Displays 2d array as "hex tiles"
        if((i % 2) == 0)
            cout << "{";
        else
            cout << "{    ";
        for(int j = 0; j < COL; ++j) {
            //Finds & marks current location
            if (map[i][j] == 2)
                cout << "(" << map[i][j] << ") ";
            else if (map[i][j] == 3) 
                cout << "[" << map[i][j]  << "] ";
            else 
                cout << " " << map[i][j] << "  ";
        }
        //Displays 2d array as hex tiles
            if((i%2) == 0)
                cout << "    }\n\n";
            else
                cout << "}\n\n";
    }
    //Displays the key
    cout << "Key: (2) = Current source\n     [3] = Destination\n\n";
}


void Movement(int grid[][25]) 
{
    int sRow, sCol, dRow, dCol;
    bool error = false;

     // Source is selected
    cout << "Please pick source: ";
    cin >> sRow >> sCol;  
    Pair src = make_pair(sRow, sCol); 
    grid[sRow][sCol] = 2;
  
    // Destination is selected
    cout << "Please pick destination: ";
    cin >> dRow >> dCol;
    Pair dest = make_pair(dRow, dCol);
    grid[dRow][dCol] = 3;
 
    // Display Map
    displayMap(grid);
 
    aStarSearch(grid, src, dest); 

}

void showMarbienPicture(int x, int y, GLuint textid) 
{
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
