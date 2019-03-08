// Fate: The Shadow Wizard: Kingdom of Darkness: Revived Two: The Second One
// Program: nicholasJo.cpp
// Author: Nicholas Jordan
// Date: 02/14/2019

#ifndef NICHOLAS_JO_CPP
#define NICHOLAS_JO_CPP

#include "nicholasJo.h"

//==========================[ENTITY CLASS]===============================
//Parent Class

Entity::Entity() {
}
//==========[Health Functions]=========
float Entity::getMaxHealth() {
	return max_health;
}

float Entity::getCurrentHealth() {
	if (current_health < 0.0) {
		//negative health is not possible
		return 0.0;
	}
	if (current_health > max_health) {
		//ensures no overheal
		current_health = max_health;
	}
	return current_health;
}

void Entity::setMaxHealth(float h) {
	max_health = h;
    return;
}
//==========[Defense Functions]=========
float Entity::getDefaultDefense() {
    return default_defense;
}

float Entity::getCurrentDefense() {
	return current_defense;
}

void Entity::setDefaultDefense(float d) {
	default_defense = d;
    return;
}
//==========[Damage Functions]=========
void Entity::setDefaultDamage(float d) {
    default_damage = d;
    return;
}

float Entity::getCurrentDamage() {
    return current_damage;
}

float Entity::getDefaultDamage() {
    return default_damage;
}
//==========[Ally Functions]=========
void Entity::setAlly(bool a) {
	ally = a;
    return;
}

bool Entity::getAlly() {
	return ally;
}
//==========[ETC]=========
void Entity::displayImage(int x, int y, int z) {
	float wid = 1;
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(wid, 0.5f, wid);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(wid, 0.5f, -wid);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-wid, 0.5f, -wid);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-wid, 0.5f, wid);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void Entity::resetStats() {
    current_health = max_health;
    current_defense = default_defense;
    current_damage = default_damage;
}

//==========================[ALLY CLASS]===============================
//Inherits from Entity

Ally::Ally() {
	setAlly(true);
	setAllyCombatType();
    current_health = getMaxHealth();
    current_defense = getDefaultDefense();
    current_damage = getDefaultDamage();
}

void Ally::setAllyCombatType() {
	//randomly generate a number from 0 to 2 to choose combat type
	srand(time(NULL));
    int random = rand() % 3;
	switch (random) {
		case 0 :
			combatType = "archer";
			setMaxHealth(50.0);
			setDefaultDefense(0.3);
			setDefaultDamage(10.0);
			break;
		case 1:
			combatType = "soldier";
			setMaxHealth(75.0);
			setDefaultDefense(0.5);
			setDefaultDamage(15.0);
			break;
		case 2:
			combatType = "tank";
			setMaxHealth(100);
			setDefaultDefense(0.7);
			setDefaultDamage(12.0);
			break;
	}
	return;
}

//==========================[ENEMY CLASS]===============================
//Inherits from Entity

Enemy::Enemy() {
	setAlly(false);
	setEnemyCombatType();
    current_health = getMaxHealth();
    current_defense = getDefaultDefense();
    current_damage = getDefaultDamage();
}

void Enemy::setEnemyCombatType() {
	//randomly generate a number from 0 to 2 to choose combat type
	srand(time(NULL));
	int random = rand() % 3;
	switch (random) {
		case 0 :
			combatType = "archer";
			setMaxHealth(50.0);
			setDefaultDefense(0.3);
			setDefaultDamage(10.0);
			break;
		case 1:
			combatType = "soldier";
			setMaxHealth(75.0);
			setDefaultDefense(0.5);
			setDefaultDamage(15.0);
			break;
		case 2:
			combatType = "tank";
			setMaxHealth(100);
			setDefaultDefense(0.7);
			setDefaultDamage(12.0);
			break;
	}
	return;
}

void Enemy::setEnemyImage() {

}

//==========================[PLAYER CLASS]===============================
//Inherits from Entity

int Player::count = 0;

Player::Player(string c, GLuint i) {
	setPlayerCombatType(c);
	setPlayerImage(i);
    current_health = getMaxHealth();
    current_defense = getDefaultDefense();
    current_damage = getDefaultDamage();
	count++;
}

//Null because instance will be initialized on demand
Player* Player::instance = 0;

Player* Player::getInstance() {
	if (instance != 0) {
		return instance;
	}
	return 0;
}

Player* Player::setInstance(string c, GLuint i) {
	if (instance == 0) {
		instance = new Player(c, i);
	}
	return instance;
}

Player::~Player() {
	delete []instance;
}

void Player::setPlayerCombatType(string c) {
	if (c == "archer") {
		setMaxHealth(75.0);
		setDefaultDefense(0.60);
		setDefaultDamage(15.0);
	} else if (c == "soldier") {
		setMaxHealth(100.0);
		setDefaultDefense(0.70);
		setDefaultDamage(20.0);
	} else if (c == "tank") {
		setMaxHealth(125.0);
		setDefaultDefense(0.80);
	    setDefaultDamage(22.0);
	}
	return;
}

void Player::setPlayerImage(GLuint i) {
	image = i;
}

//============================================================================

void Display_NicholasJordan(int x, int y, GLuint textid) {
    glColor3ub(255, 255, 255);
    //static float angle = 0.0f;
    static int wid = 50;
    //wid += sin(angle) * 10;
    //float fx = (float)x;
    //float fy = (float)y;
    //float a = 0;
    //a += sin(angle) * 10.0f;
    //fx += a;
    //angle += 0.2f;
    glPushMatrix();
    //glTranslatef(fx, fy, 0);
    glTranslatef(x, y, 0);
    //glRotatef(a, 0, 0, 1.0);
    glBindTexture(GL_TEXTURE_2D, textid);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();

    
    Rect r;
    glTranslatef(wid,0,0);
    r.bot = 0;
    r.left = 10;
    r.center = 0;
    ggprint8b(&r, 16, 0x00000000, "Nicholas Jordan");
    glPopMatrix();
}

Enemy* spawnEnemies(int amount) {
    Enemy *baddies = new Enemy[amount];
    return baddies;
}

#endif
