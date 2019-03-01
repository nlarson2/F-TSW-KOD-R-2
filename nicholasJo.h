//Author: Nicholas Jordan
//Date: 02/24/2019

#include <GL/glx.h>
#include "fonts.h"
#include <string>

using namespace std;

#ifndef NICHOLAS_JO_H
#define NICHOLAS_JO_H

void Display_NicholasJordan(int, int, GLuint);

class Entity
{
	private:
		float max_health;
		float defense;
		bool ally;
	public:
		Entity();
		float getMaxHealth();
		float getCurrentHealth();
		void setMaxHealth(float);
		float getDefense();
		void setDefense(float);
		void setAlly(bool);
		bool getAlly();
		void displayImage();

		string combatType;
		float current_health;
		float damage;
		GLuint image;
};

class Ally : public Entity
{
	public:
		Ally();
		void setAllyCombatType();
};

class Enemy : public Entity
{
	public:
		Enemy();
		void setEnemyCombatType();
};

//singleton class
//initialize player with: Player *player = Player::getInstance();
class Player : public Entity
{
	public:
		static int count;
		static Player* getInstance();
		static Player* getInstance(string, GLuint);
		void setPlayerCombatType(string);
		void setPlayerImage(GLuint);
	private:
		static Player* instance;
		Player(string, GLuint);
		~Player();
};

#endif
