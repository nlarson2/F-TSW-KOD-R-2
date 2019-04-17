// Fate: The Shadow Wizard: Kingdom of Darkness: Revived Two: The Second One
// Program: nicholasJo.cpp
// Author: Nicholas Jordan
// Date: 02/14/2019

#ifndef NICHOLAS_JO_CPP
#define NICHOLAS_JO_CPP

#include "nicholasJo.h"

NJordGlobal njG;
NJordGlobal::NJordGlobal()
{
}

void NJordGlobal::spawnEnemies(int amount)
{
    Log("spawnEnemies(int amount), amount = %i\n", amount);
    enemies = new Enemy[amount];
}

void NJordGlobal::spawnAllies(int amount)
{
    Log("spawnAllies(int amount), amount = %i\n", amount);
    allies = new Ally[amount];
}

void NJordGlobal::resetAllies()
{
    Log("Ally::resetAllies(), allies->count = %i\n", allies->count);
    delete []allies;
    allies->count = 0;
    return;
}

void NJordGlobal::resetEnemies()
{
    Log("Enemy::resetEnemies(), enemies->count = %i\n", enemies->count);
    delete []enemies;
    enemies->count = 0;
    return;
}
//==========================[ENTITY CLASS]===============================

static Model pModel[1] = {
	Model("models/tank/Tank.obj","models/tank/TankTexture.png")
};

//==========[Health Functions]=========
float Entity::getMaxHealth()
{
    Log("getMaxHealth() returning %f\n", max_health);
	return max_health;
}

float Entity::getCurrentHealth()
{
	if (current_health < 0.0) {
		//negative health is not possible
        current_health = 0.0;
        Log("Entity::getCurrentHealth() returning %f\n", current_health);
		return current_health;
	}
	if (current_health > max_health) {
		//ensures no overheal
		current_health = max_health;
	}
    Log("Entity::getCurrentHealth() returning %f\n", current_health);
	return current_health;
}

void Entity::setMaxHealth(float h)
{
    Log("Entity::setMaxHealth(float h), h = %f\n", h);
	max_health = h;
    return;
}
//==========[Defense Functions]=========
float Entity::getDefaultDefense()
{
    Log("Entity::getDefaultDefense() returning %f\n", default_defense);
    return default_defense;
}

float Entity::getCurrentDefense()
{
    Log("Entity::getCurrentDefense() returning %f\n", current_defense);
	return current_defense;
}

void Entity::setDefaultDefense(float d)
{
    Log("Entity::setDefaultDefense(float d), d = %f\n", d);
	default_defense = d;
    return;
}
//==========[Damage Functions]=========
void Entity::setDefaultDamage(float d)
{
    Log("Entity::setDefaultDamage(float d), d = %f\n", d);
    default_damage = d;
    return;
}

float Entity::getCurrentDamage()
{
    Log("Entity::getCurrentDamage() returning %f\n", current_damage);
    return current_damage;
}

float Entity::getDefaultDamage()
{
    Log("Entity::getDefaultDamage() returning %f\n", default_damage);
    return default_damage;
}

void Entity::dealDamage(Entity &target)
{
    Log("Entity::dealDamage(Entity &target), target.ally = %i\n", target.getAlly());
    if (this->getAlly() != target.getAlly() && target.current_health > 0 &&
        this->current_health > 0)
        target.current_health -= target.current_defense * this->current_damage;
    else
        cout << "Cannot damage an ally!\n";
    if (target.current_health < 0)
        target.current_health = 0;
}
//==========[Ally Functions]=========
void Entity::setAlly(bool a)
{
    Log("Entity::setAlly(bool a), a = %i\n", a);
	ally = a;
    return;
}

bool Entity::getAlly()
{
    Log("Entity::getAlly() returning %i\n", ally);
	return ally;
}
//==========[ETC]=========

void Entity::displayImage(int x, int y, int z)
{
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

void Entity::resetStats()
{
    Log("Entity::resetStats()\n");
    current_health = max_health;
    current_defense = default_defense;
    current_damage = default_damage;
}

void Entity::draw()
{
    pModel[this->modelID].draw(this->wPos.x, this->wPos.z, 0.3);
}

//==========================[ALLY CLASS]===============================
//Inherits from Entity

int Ally::count = 0;

Ally::Ally()
{
    Log("Ally::Ally()\n");
	setAlly(true);
	setAllyCombatType();
    setAllyImage();
    current_health = getMaxHealth();
    current_defense = getDefaultDefense();
    current_damage = getDefaultDamage();
    count++;
}

void Ally::saveAllies(ofstream& file)
{
    Log("Ally::saveAllies(ostream& file)\n");
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

void Ally::loadAllies(ifstream& file)
{
    Log("Ally::loadAllies(ifstream& file)\n");
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

void Ally::loadAllyCombatType(string c)
{
    Log("Ally::loadAllyCombatType(string c), c = %s\n", c.c_str());
	if (c == "archer") {
        modelID = 0;
        combatType = c;
		setMaxHealth(50.0);
		setDefaultDefense(0.3);
		setDefaultDamage(10.0);
	} else if (c == "soldier") {
        modelID = 0;
        combatType = c;
		setMaxHealth(75.0);
		setDefaultDefense(0.5);
		setDefaultDamage(15.0);
	} else if (c == "tank") {
        modelID = 0;
        combatType = c;
		setMaxHealth(100.0);
		setDefaultDefense(0.70);
	    setDefaultDamage(12.0);
    }
    setAllyImage();
	return;
}

void Ally::setAllyCombatType()
{
    Log("Ally::setAllyCombatType()\n");
	//randomly generate a number from 0 to 2 to choose combat type
	random_device generator;
    uniform_int_distribution<int> distribution(0, 2);
	switch (distribution(generator)) {
		case 0:
            modelID = 0;
			combatType = "archer";
			setMaxHealth(50.0);
			setDefaultDefense(0.3);
			setDefaultDamage(10.0);
			break;
		case 1:
            modelID = 0;
			combatType = "soldier";
			setMaxHealth(75.0);
			setDefaultDefense(0.5);
			setDefaultDamage(15.0);
			break;
		case 2:
            modelID = 0;
			combatType = "tank";
			setMaxHealth(100);
			setDefaultDefense(0.7);
		    setDefaultDamage(12.0);
			break;
	}
	return;
}

void Ally::setAllyImage()
{
    Log("Ally::setAllyImage()\n");
    if (combatType == "archer" || combatType == "nick")
        GenerateGLTexture(image, "./images/nickLCreditPic.jpg", false);
    else if (combatType == "soldier")
        GenerateGLTexture(image, "./images/nicholasJo.png", false);
    else if (combatType == "tank")
        GenerateGLTexture(image, "./images/brandonH.png", false);
}


//==========================[ENEMY CLASS]===============================
//Inherits from Entity

int Enemy::count = 0;

Enemy::Enemy()
{
    Log("Enemy::Enemy()\n");
	setAlly(false);
	setEnemyCombatType();
    current_health = getMaxHealth();
    current_defense = getDefaultDefense();
    current_damage = getDefaultDamage();
    wPos.x = count;
    wPos.z = 1;
    count++;
}

void Enemy::setEnemyCombatType()
{
    Log("Enemy::setEnemyCombatType()\n");
	//randomly generate a number from 0 to 2 to choose combat type
	random_device generator;
    uniform_int_distribution<int> distribution(0, 2);
    switch (distribution(generator)) {
		case 0 :
            modelID = 0;
			combatType = "archer";
			setMaxHealth(50.0);
			setDefaultDefense(0.3);
			setDefaultDamage(10.0);
			break;
		case 1:
            modelID = 0;
			combatType = "soldier";
			setMaxHealth(75.0);
			setDefaultDefense(0.5);
			setDefaultDamage(15.0);
			break;
		case 2:
            modelID = 0;
			combatType = "tank";
			setMaxHealth(100);
			setDefaultDefense(0.7);
			setDefaultDamage(12.0);
			break;
	}
	return;
}

void Enemy::setEnemyImage()
{
    Log("Enemy::setEnemyImage()\n");
    if (combatType == "archer" || combatType == "nick")
        GenerateGLTexture(image, "./images/nickLCreditPic.jpg", false);
    else if (combatType == "soldier")
        GenerateGLTexture(image, "./images/nicholasJo.png", false);
    else if (combatType == "tank")
        GenerateGLTexture(image, "./images/brandonH.png", false);
}


//==========================[PLAYER CLASS]===============================
//Inherits from Entity

//Null because instance will be initialized on demand
int Player::count = 0;
Player* Player::instance = 0;

Player::Player(string c)
{
    Log("Player::Player(string c), c = %s\n", c.c_str());
    setPlayerCombatType(c);
	setPlayerImage();
    setAlly(true);
    current_health = getMaxHealth();
    current_defense = getDefaultDefense();
    current_damage = getDefaultDamage();
    count++;
}

Player* Player::getInstance()
{
	if (count != 0)
		return instance;
	return 0;
}

Player* Player::setInstance(string c)
{
    Log("Player::setInstance(string c), c = %s\n", c.c_str());
	if (count == 0)
		instance = new Player(c);
	return instance;
}

void Player::resetInstance()
{
    Log("Player::resetInstance()\n");
    delete instance;
    instance = NULL;
    count--;
}

void Player::saveInstance(int save_number)
{
    Log("Player::saveInstance(int save_number), save_number = %i\n", save_number);
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
    njG.allies->saveAllies(file);
    file.close();
}

bool Player::loadInstance(int save_number)
{
    Log("Player::loadInstance(int save_number), save_number = %i\n", save_number);
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
        return false;
    }
    Player *player = getInstance();
    njG.allies->loadAllies(file);
    file.close();
    return true;
}

void Player::setPlayerCombatType(string c)
{
    Log("Player::setPlayerCombatType(string c), c = %s\n", c.c_str());
	if (c == "archer") {
        modelID = 0;
        combatType = c;
		setMaxHealth(75.0);
		setDefaultDefense(0.60);
		setDefaultDamage(15.0);
	} else if (c == "soldier") {
        modelID = 0;
        combatType = c;
		setMaxHealth(100.0);
		setDefaultDefense(0.70);
		setDefaultDamage(20.0);
	} else if (c == "tank") {
        modelID = 0;
        combatType = c;
		setMaxHealth(125.0);
		setDefaultDefense(0.80);
	    setDefaultDamage(22.0);
	} else if (c == "nick") {
        modelID = 0;
        combatType = c;
		setMaxHealth(999);
		setDefaultDefense(1);
	    setDefaultDamage(999);
    }
	return;
}

void Player::setPlayerImage()
{
    Log("Player::setPlayerImage()\n");
    if (combatType == "archer" || combatType == "nick")
        GenerateGLTexture(image, "./images/nickLCreditPic.jpg", false);
    else if (combatType == "soldier")
        GenerateGLTexture(image, "./images/nicholasJo.png", false);
    else if (combatType == "tank")
        GenerateGLTexture(image, "./images/brandonH.png", false);
}

//============================================================================

void Display_NicholasJordan(int x, int y, GLuint textid)
{
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
