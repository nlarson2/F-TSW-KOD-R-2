// Fate: The Shadow Wizard: Kingdom of Darkness: Revived Two: The Second One
// Program: nicholasJo.h
// Author: Nicholas Jordan
// Date: 02/24/2019

#include <GL/glx.h>
#include "fonts.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include "nickolasL.h"

using namespace std;

#ifndef NICHOLAS_JO_H
#define NICHOLAS_JO_H

class Entity
{
    private:
		float max_health;
		float default_defense;
        float default_damage;
		bool ally;
	protected:
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
        //void displayImage(int x, int y, int z);
		void resetStats();
        void displayImage(int,int,int);

		string combatType;
		float current_health;
        float current_defense;
		float current_damage;
		GLuint image;
        Model playerModel;
        vec3 wPos; //world position
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
        //saveAllies is called in saveInstance
        void saveAllies(ofstream&);
        //loadAllies is called in loadInstance
        void loadAllies(ifstream&);
        static int count;
    private:
        //setAlly is used for initializing a new ally's combat type
		void setAllyCombatType();
        //loadAllyCombatType is used for loading already set 
        //combat types from save(*number*).txt
		void loadAllyCombatType(string);
		void setAllyImage();
};

//singleton class
class Player : public Entity
{
	public:
        Ally *allies;
		static int count;
		static Player* getInstance();
		static Player* setInstance(string);
        //saveInstance and loadInstance are called from brandonH.cpp
        //save player and ally instances in save(*number*).txt file
        //The save functions write to save(*number*).txt line by 
        //line for easy reading for the load functions
        void saveInstance(int);
        //load player and ally intances from save(*number*).txt file
        void loadInstance(int);
        static void resetInstance();
		void setPlayerCombatType(string);
		void setPlayerImage();
	private:
		static Player* instance;
		Player(string);
};

void Display_NicholasJordan(int, int, GLuint);
Enemy* spawnEnemies(int);
Ally* spawnAllies(int);

#endif
