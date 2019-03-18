#ifndef GAME_H
#define GAME_H

#include <stack>
#include <vector>

#include "nickolasL.h"
#include "brandonH.h"
#include "nicholasJo.h"

extern BHglobal bhg;

class Game
{
	private:
        int xres, yres;
		stack<GameState*> states;
		//Player player;
		vector<Ally> allies;
		vector<Enemy> enemies;
	public:
		Game(int x, int y);
    void init();
		void procMouseInput(int x, int y);
		void procKeyInput(int key);
		void drawGameState();
};

#endif
