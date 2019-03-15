//Author: Nickolas Larson
//Date: 2/14/2019
//Modified By: Nickolas Larson
//Modified 3/08/2019

#ifndef NICKOLAS_L_H
#define NICKOLAS_L_H

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <cmath>
#include <GL/glx.h>
#include <GL/glu.h>
#include "fonts.h"

#include "Image.h"
//#include "Game.h"

using namespace std;


#define PI 3.14159265359

class Image;


class NLarsGlobal
{
public:
        //Variables here

private:
        NLarsGlobal();
        NLarsGlobal(NLarsGlobal const& copy);
        NLarsGlobal& operator=(NLarsGlobal const& copy);

public:
        static NLarsGlobal& getInstance();

};


struct vec2
{
	float x, y;
	vec2();
	vec2(float x, float z);
	vec2 operator = (const vec2& right);
	vec2 operator +(const vec2& right);
	vec2 operator +=(const vec2& right);
};

struct vec3
{
	float x, y, z;
	vec3();
	vec3(float x, float y, float z);
	void operator()(float _x, float _y, float _z);
	vec3 operator = (const vec3& right);
	vec3 operator +(const vec3& right);
	vec3 operator +=(const vec3& right);
};


void GenerateGLTexture(GLuint & texture, const char * dataSrc, bool inverted);

void draw_nickLCredit(int x, int y, GLuint texture);

struct Model
{	
	GLuint texture;
	vector<vec3> vert;
	vector<vec2> vertTex;
	vector<vec3> vertNorm;
	//connection values
	vector<unsigned int> vIndices, vtIndices, vnIndices;
	vec3 pos; //moves along x and z
	Model ();
	Model ( const char * objFile, const char * texFile);
	void draw();
	private:
	bool GenerateModel( const char * objFile );
	bool GenerateTexture( const char * texFile );
};

struct Tile
{
	int modelID;
	float x,z;
};

class Map
{
	private:
		int mapW, mapH;
		Tile ** tile;

	public:
		Map(){}
		Map(int *map, int _width, int _height);
		void draw();
};





class Camera{
	private:
		vec3 wPos;//world position
		vec3 pos;
		vec3 front;
		vec3 up;
		vec2 vel;
		float radius;
		float pitch;
		float yaw;
	public:
        //view was private
		vec3 view;
		Camera();
		Camera(float rot, int posx, int posz);
		void update();
		
		void drawCamera(GLuint);
		void rotate(float direction);
		void translate(vec2 direction);

};



class GameState
{
    private:
		
	public:
		GameState() {};
		virtual int procMouseInput(int x, int y) = 0;
		virtual int procKeyInput(int key) = 0;
		virtual void drawGameState() = 0;

};

class WorldGS : public GameState {

    private:
        Map map;
		Camera camera;
		float xres, yres;
    public:
        WorldGS(int* mapArr,int sizex,int sizey,
			float camRot, int posx, int posz,
			float xres, float yres);
		void initWGS_GL();
        int procMouseInput(int x, int y);
		int procKeyInput(int key);
		void drawGameState();
};

#endif
