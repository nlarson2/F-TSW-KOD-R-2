// Fate the Shadow Wizard Kingdom of Darkness Revived Two The Second One
// program: nicholasJo.cpp
// author: Nicholas Jordan
// date: 02/14/2019

#ifndef NICHOLAS_JO_CPP
#define NICHOLAS_JO_CPP

#include "nicholasJo.h"

//==========================[ENTITY CLASS]===============================
//Parent Class

Entity::Entity() {
}

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

float Entity::getDefense() {
	return defense;
}

void Entity::setAlly(bool a) {
	ally = a;
}

bool Entity::getAlly() {
	return ally;
}

void Entity::setMaxHealth(float h) {
	max_health = h;
}

void Entity::setDefense(float d) {
	defense = d;
}

void Entity::displayImage() {
	float wid = 50;
	glPushMatrix();
	glTranslatef(100, 100, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

//==========================[ALLY CLASS]===============================
//Inherits from Entity

Ally::Ally() {
	setAlly(true);
	setAllyCombatType();
}

void Ally::setAllyCombatType() {
	//randomly generate a number from 0 to 2 to choose combat type
	int random = rand() % 3;
	switch (random) {
		case 0 :
			combatType = "archer";
			setMaxHealth(50.0);
			setDefense(0.3);
			damage = 10;
			break;
		case 1:
			combatType = "soldier";
			setMaxHealth(75.0);
			setDefense(0.5);
			damage = 15;
			break;
		case 2:
			combatType = "tank";
			setMaxHealth(100);
			setDefense(0.7);
			damage = 12;
			break;
	}
	return;
}

//==========================[ENEMY CLASS]===============================
//Inherits from Entity

Enemy::Enemy() {
	setAlly(false);
	setEnemyCombatType();
}

void Enemy::setEnemyCombatType() {
	//randomly generate a number from 0 to 2 to choose combat type
	srand(time(NULL));
	int random = rand() % 3;
	switch (random) {
		case 0 :
			combatType = "archer";
			setMaxHealth(50.0);
			setDefense(0.3);
			damage = 10;
			break;
		case 1:
			combatType = "soldier";
			setMaxHealth(75.0);
			setDefense(0.5);
			damage = 15;
			break;
		case 2:
			combatType = "tank";
			setMaxHealth(100);
			setDefense(0.7);
			damage = 12;
			break;
	}
	return;
}

//==========================[PLAYER CLASS]===============================
//Inherits from Entity

int Player::count = 0;

Player::Player(string c, GLuint i) {
	setPlayerCombatType(c);
	setPlayerImage(i);
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

Player* Player::getInstance(string c, GLuint i) {
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
		setDefense(0.60);
		damage = 15;
	} else if (c == "soldier") {
		setMaxHealth(100.0);
		setDefense(0.70);
		damage = 20;
	} else if (c == "tank") {
		setMaxHealth(125.0);
		setDefense(0.80);
		damage = 22;
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

#endif
