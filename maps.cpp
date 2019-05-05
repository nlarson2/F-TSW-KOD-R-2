/*
INDEX:
      0 - water
      1 - grass
      2 - mountain
      3 - forest  
      4 - smallBoat
      5 - medBoat
      6 - lgBoat
      7 - castle
      8 - caslteRotated
*/
int mainMap[][25]={
  
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1 },
      {  0,5,0,0,0,6,0,0,0,5,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
      { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,1,1,1,1,1,1,1,1 },
      {  0,0,6,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,7,1,1,1,1,1},
      { 0,0,0,0,0,5,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1 },
      {  0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      { 0,0,0,0,0,4,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
      {  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1},
      { 1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,2,1,1,1,1,1,1 },
      {  1,1,1,1,1,1,3,1,1,1,1,1,2,2,1,1,2,2,2,1,1,1,1,1,1},
      { 2,1,1,2,1,3,3,3,1,1,1,1,1,1,2,2,2,2,2,2,1,1,1,1,1 },
      {  2,2,2,2,3,3,3,1,1,1,8,1,1,1,2,2,1,1,2,1,1,1,1,1,1},
      { 1,2,2,1,1,3,3,3,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1 },
      {  1,1,1,1,1,3,3,3,3,3,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
      { 1,1,7,1,1,1,3,3,3,3,1,1,1,1,1,2,2,1,3,3,3,1,1,1,1 },
      {  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,3,3,3,3,1,1,1,1},
      { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,1,1,1 },
      {  1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1},
      { 1,1,1,2,2,1,1,1,1,1,1,1,1,1,7,1,1,3,1,3,1,1,1,1,1 },
      {  1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      { 1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
      {  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
      { 1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1 },
      {  1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1},
      { 1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1  }
  
};

int battleMap1[][10] {
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 }
};

int battleMap2[][10] {
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 },
      { 1,1,1,1,1,1,1,1,1,1},
      {1,1,1,1,1,1,1,1,1,1 }
};