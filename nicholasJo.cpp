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

int Ally::count = 0;

Ally::Ally() {
	setAlly(true);
	setAllyCombatType();
    current_health = getMaxHealth();
    current_defense = getDefaultDefense();
    current_damage = getDefaultDamage();
    count++;
}

void Ally::saveAllies(ofstream& file) {
    if (file) {
        file << Ally::count << endl;                    //line 8
        for (int i = 0; i < Ally::count; i++) {
            file << this[i].combatType << endl;         //line 9+7i
            file << this[i].current_health << endl;     //line 10+7i
            file << this[i].current_defense << endl;    //line 11+7i
            file << this[i].current_damage << endl;     //line 12+7i
            file << this[i].wPos.x << endl;             //line 13+7i
            file << this[i].wPos.y << endl;             //line 14+7i
            file << this[i].wPos.z << endl;             //line 15+7i
        }
    } else {
        printf("Could not locate file specified\n");
    }
}

void Ally::loadAllies(ifstream& file) {
    string line;
    if (file) {
        //load count - line 8
        getline(file, line);
        this->count = atoi(line.c_str());
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                //load combatType - line 9+7i
                getline(file, line);
                this[i].loadAllyCombatType(line);
                //load current_health - line 10+7i
                getline(file, line);
                //strtof = string to float
                this[i].current_health = strtof(line.c_str(), NULL); 
                //load current_defense - line 11+7i
                getline(file, line);
                this[i].current_defense = strtof(line.c_str(), NULL);
                //load current_damage - line 12+7i
                getline(file, line);
                this[i].current_damage = strtof(line.c_str(), NULL);
                //load wPos.x - line 13+7i
                getline(file, line);
                this[i].wPos.x = strtof(line.c_str(), NULL);
                //load wPos.y - line 14+7i
                getline(file, line);
                this[i].wPos.y = strtof(line.c_str(), NULL);
                //load wPos.z - line 15+7i
                getline(file, line);
                this[i].wPos.z = strtof(line.c_str(), NULL);
            }
        }
    } else {
        printf("Could not locate file specified\n");
    }
}

void Ally::loadAllyCombatType(string c) {
	if (c == "archer") {
        combatType = c;
		setMaxHealth(50.0);
		setDefaultDefense(0.3);
		setDefaultDamage(10.0);
	} else if (c == "soldier") {
        combatType = c;
		setMaxHealth(75.0);
		setDefaultDefense(0.5);
		setDefaultDamage(15.0);
	} else if (c == "tank") {
        combatType = c;
		setMaxHealth(100.0);
		setDefaultDefense(0.70);
	    setDefaultDamage(12.0);
    }
    setAllyImage();
	return;
}

void Ally::setAllyCombatType() {
	//randomly generate a number from 0 to 2 to choose combat type
	srand(time(NULL));
	switch (rand()%3) {
		case 0:
            {
			    combatType = "archer";
			    setMaxHealth(50.0);
			    setDefaultDefense(0.3);
			    setDefaultDamage(10.0);
            }
			break;
		case 1:
            {
			    combatType = "soldier";
			    setMaxHealth(75.0);
			    setDefaultDefense(0.5);
			    setDefaultDamage(15.0);
            }
			break;
		case 2:
            {
			    combatType = "tank";
			    setMaxHealth(100);
			    setDefaultDefense(0.7);
			    setDefaultDamage(12.0);
            }
			break;
	}
	return;
}

void Ally::setAllyImage() {
    if (combatType == "archer" || combatType == "nick") {
        GenerateGLTexture(image, "./images/nickLCreditPic.jpg", false);
    } else if (combatType == "soldier") {
        GenerateGLTexture(image, "./images/nicholasJo.png", false);
    } else if (combatType == "tank") {
        GenerateGLTexture(image, "./images/brandonH.png", false);
    }
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
    if (combatType == "archer" || combatType == "nick") {
        GenerateGLTexture(image, "./images/nickLCreditPic.jpg", false);
    } else if (combatType == "soldier") {
        GenerateGLTexture(image, "./images/nicholasJo.png", false);
    } else if (combatType == "tank") {
        GenerateGLTexture(image, "./images/brandonH.png", false);
    } 
}

//==========================[PLAYER CLASS]===============================
//Inherits from Entity

int Player::count = 0;

Player::Player(string c) {
	setPlayerCombatType(c);
	setPlayerImage();
    current_health = getMaxHealth();
    current_defense = getDefaultDefense();
    current_damage = getDefaultDamage();
    //initial player position
    playerModel.pos.x = -1;
    playerModel.pos.y = 0.1;
    playerModel.pos.z = 0;
    allies = spawnAllies(3);
    count++;
}

//Null because instance will be initialized on demand
Player* Player::instance = 0;

Player* Player::getInstance() {
	if (count != 0) {
		return instance;
	}
	return 0;
}

Player* Player::setInstance(string c) {
	if (count == 0) {
		instance = new Player(c);
    }
	return instance;
}

void Player::resetInstance() {
    delete instance;
    instance = NULL;
    count--;
}

void Player::saveInstance(int save_number) {
    string file_name = "save" + to_string(save_number) + ".txt";
    ofstream file(file_name);
    if (file.is_open()) {
        file << instance->combatType << endl;           //line 1
        file << instance->current_health << endl;       //line 2
        file << instance->current_defense << endl;      //line 3
        file << instance->current_damage << endl;       //line 4
        file << instance->wPos.x << endl;               //line 5
        file << instance->wPos.y << endl;               //line 6
        file << instance->wPos.z << endl;               //line 7

    } else {
        printf("Could not locate file specified\n");
    }
    this->allies->saveAllies(file);
    file.close();
}

void Player::loadInstance(int save_number) {
    string file_name = "save" + to_string(save_number) + ".txt";
    string line;
    ifstream file(file_name);
    if (file) {
        //load combatType - line 1
        getline(file, line);
        Player *player = setInstance(line);
        //load current_health - line 2
        getline(file, line);
        player->current_health = strtof(line.c_str(), NULL); //strtof = string to float
        //load current_defense - line 3
        getline(file, line);
        player->current_defense = strtof(line.c_str(), NULL);
        //load current_damage - line 4
        getline(file, line);
        player->current_damage = strtof(line.c_str(), NULL);
        //load wPos.x - line 5
        getline(file, line);
        player->wPos.x = strtof(line.c_str(), NULL);
        //load wPos.y - line 6
        getline(file, line);
        player->wPos.y = strtof(line.c_str(), NULL);
        //load wPos.z - line 7
        getline(file, line);
        player->wPos.z = strtof(line.c_str(), NULL);
        
        player->count = 1;
    } else {
        printf("Could not locate file specified\n");
    }
    Player *player = getInstance();
    player->allies->loadAllies(file);
    file.close();
}

void Player::setPlayerCombatType(string c) {
	if (c == "archer") {
        combatType = c;
		setMaxHealth(75.0);
		setDefaultDefense(0.60);
		setDefaultDamage(15.0);
	} else if (c == "soldier") {
        combatType = c;
		setMaxHealth(100.0);
		setDefaultDefense(0.70);
		setDefaultDamage(20.0);
	} else if (c == "tank") {
        combatType = c;
		setMaxHealth(125.0);
		setDefaultDefense(0.80);
	    setDefaultDamage(22.0);
	} else if (c == "nick") {
        combatType = c;
		setMaxHealth(999);
		setDefaultDefense(1);
	    setDefaultDamage(999);
    }
	return;
}

void Player::setPlayerImage() {
    if (combatType == "archer" || combatType == "nick") {
        GenerateGLTexture(image, "./images/nickLCreditPic.jpg", false);
    } else if (combatType == "soldier") {
        GenerateGLTexture(image, "./images/nicholasJo.png", false);
    } else if (combatType == "tank") {
        GenerateGLTexture(image, "./images/brandonH.png", false);
    }
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

Ally* spawnAllies(int amount) {
    Ally *goodies = new Ally[amount];
    return goodies;
}

#endif
