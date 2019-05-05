// Fate: The Shadow Wizard: Kingdom of Darkness: Revived Two: The Second One
// Program: nicholasJo.h
// Author: Nicholas Jordan
// Date: 02/24/2019
//
/*==================[ IMPORTANT NOTES ]====================//
  - Entity is the parent class of Enemy, Ally, and Player

  -  The Player class is a singleton

  -  The functions saveInstance for Player, saveAllies, and 
  saveEnemies are called from saveEntities in NJordGlobal class

  -  The functions loadInstance for Player, loadAllies in 
  NJordGlobal, and loadEnemies in NJordGlobal are called from
  loadEntities which is also in the NJordGlobal class

  -  The save functions write to 'save(*number*).txt'.
  The data is written line by line for the player as follows:
  combatType
  current_health
  current_defense
  current_damage
  wPos.x
  wPos.y
  wPos.z
  The data for the allies is written similarly; however the
  amount of allies is written before anything else.

  -  The load functions can then read from 'save(*number*).txt'
  line by line to be saved into the correct object's variable

  -  Sound can be enabled and disable simply by using different
  makefile target. Using 'make' compiles the game with no sound.
  Using 'make sound' compiles the game with sound. Both targets
  generate different executables: 'game' and 'sound'.

  -  In order to minimize the amount of space taken up by sound
  files, all sounds are in .ogg file format. This means that
  each sound file needs to be uncompressed and decoded. This
  was done using the libogg and libvorgis libraries that can
  be found at https://xiph.org/vorbis/

  -  Example code that I looked at and used for sound can be 
  found at https://www.gamedev.net/articles/programming/
  general-and-gameplay-programming/introduction-to-ogg-vorbis-r2031/

//=========================================================*/
#ifndef NICHOLAS_JO_H
#define NICHOLAS_JO_H

#include <GL/glx.h>
#include "fonts.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include "nickolasL.h"
#include "log.h"
#include <random>
#include <cmath>
#ifdef SOUND
#include <AL/alut.h>
#include <AL/al.h>
#include <vorbis/vorbisfile.h>
#endif

using namespace std;


#ifdef SOUND
class Sound {
    public:
        ALuint alBuffer[15];
        ALuint menuSound;
        ALuint moveSound;
        ALuint ambientSound;
        ALuint battleSound;
        ALuint hitSound;
        ALuint gruntSound[10];
        Sound();
        void loadOGG(char *, vector<char>&, ALenum&, ALsizei&);
        void clearSounds();
        void initializeSounds();
        void loadSounds();
        void playRandomGrunt();
};
#endif

class Entity {
    private:
	float max_health;
	float default_defense;
	float default_damage;
	bool ally;
    int turns;
    protected:
	void setMaxHealth(float);
	void setDefaultDefense(float);
	void setDefaultDamage(float);
    void setMaxTurns(int);
    public:
	//====[Health Functions]====
	float getMaxHealth();
	float getCurrentHealth();
	//====[Defense Functions]====
	float getDefaultDefense();
	float getCurrentDefense();
	//====[Damage Functions]====
	float getDefaultDamage();
	float getCurrentDamage();
	void dealDamage(Entity *target);
	//====[Ally Functions]====
	void setAlly(bool);
	bool getAlly();
	//====[ETC]====
	void resetStats();
	void displayImage(int,int,int);
	void drawWorld();
	void drawBattle();
    bool inWorldRange(Entity *target);
    bool inBattleRange(Entity *target);
    int getMaxTurns();

	string combatType;
	GLuint image;
	Model playerModel;
	int modelID;
	float current_health;
	float current_defense;
	float current_damage;
    float wYaw;
    float bYaw;
	vec3 wPos; //world position
	vec3 bPos; //battle position

	/*NickolasL additions*/
	int moveRange;
	int attackRange;
};

class Enemy : public Entity {
    public:
	Enemy();
	static int count;
	void saveEnemies(ofstream&);
	void loadEnemyCombatType(string);
    private:
	void setEnemyCombatType();
	void setEnemyImage();
};

class Ally : public Entity {
    public:
	Ally();
	void saveAllies(ofstream&);
	static int count;
	void loadAllyCombatType(string);
    private:
	void setAllyCombatType();
	void setAllyImage();
};

//singleton class
class Player : public Entity {
    public:
	static int count;
	static Player* getInstance();
	static Player* setInstance(string);
	void saveInstance(ofstream&);
	void loadInstance(ifstream&);
	static void resetInstance();
	void setPlayerCombatType(string);
	void setPlayerImage();
    private:
	static Player* instance;
	Player(string);
};

class NJordGlobal {
    public:
#ifdef SOUND
    Sound sound;
#endif
	Player *player;
	Enemy *enemies;
	Ally *allies;
	NJordGlobal();
	void spawnEnemies(int);
	void spawnAllies(int);
	void resetAllies();
	void resetEnemies();
    void saveEntities(int);
    bool loadEntities(int);
	void loadAllies(ifstream&);
    void loadEnemies(ifstream&);
    //int type: 0 = player, 1 = ally, 2 = enemy
    int checkWorldCollision(int x , int y, int type = 0);
    bool checkBattleCollision(int x, int y, int position = 0, int type = 0);
    void controlTurns(Entity *target, int dest_x, int dest_z, int turn_amount, Tile**);
};

void Display_NicholasJordan(int, int, GLuint);

#endif
