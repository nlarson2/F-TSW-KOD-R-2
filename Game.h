#ifndef GAME_H
#define GAME_H

#include <stack>
#include <vector>

#include "nickolasL.h"
#include "brandonH.h"
#include "nicholasJo.h"



//Map map(tileMap, 25, 25);
//Camera camera;

class Game
{
	private:
		stack<GameState> states;
		//Player player;
		vector<Ally> allies;
		vector<Enemy> enemies;
	public:
		Game();
		void procMouseInput(int x, int y);
		void procKeyInput(int key);
		void drawGameState();
};



#endif