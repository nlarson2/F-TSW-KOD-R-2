// Fate: The Shadow Wizard: Kingdom of Darkness: Revived Two: The Second One
// Program: nicholasJo.h
// Author: Nicholas Jordan
// Date: 02/24/2019

#include <GL/glx.h>
#include "fonts.h"
#include <string>
#include <typeinfo>

using namespace std;

#ifndef NICHOLAS_JO_H
#define NICHOLAS_JO_H

class Entity
{
	private:
        // can only be called in parent class
		float max_health;
		float default_defense;
        float default_damage;
		bool ally;
    protected:
        // can only be called in parent or inherited classes
		void setMaxHealth(float);
        void setDefaultDefense(float);
        void setDefaultDamage(float);
	public:
		Entity();
		//====[Health Functions]====
        float getMaxHealth();
		float getCurrentHealth();
		//====[Defense Functions]====
		float getDefaultDefense();
		float getCurrentDefense();
		//====[Damage Functions]====
        float getDefaultDamage();
        float getCurrentDamage();
		//====[Ally Functions]====
        void setAlly(bool);
		bool getAlly();
		//====[ETC]====
        void displayImage(int x, int y, int z);
		void resetStats();

		string combatType;
		float current_health;
        float current_defense;
		float current_damage;
		GLuint image;
};

class Enemy : public Entity
{
	public:
		Enemy();
    private:
		void setEnemyCombatType();
		void setEnemyImage();
};

class Ally : public Entity
{
	public:
		Ally();
    private:
		void setAllyCombatType();
		void setAllyImage();
};

//singleton class
class Player : public Entity
{
	public:
        Ally *allies;
		static int count;
		static Player* getInstance();
		static Player* setInstance(string, GLuint);
		void setPlayerCombatType(string);
		void setPlayerImage(GLuint);
	private:
		static Player* instance;
		Player(string, GLuint);
		~Player();
};

void Display_NicholasJordan(int, int, GLuint);
Enemy* spawnEnemies(int);

#endif
