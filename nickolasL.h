//Author: Nickolas Larson
//Date: 2/14/2019
//Modified By: Nickolas Larson
//Modified 3/02/2019

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
	vec2 operator = (const vec2& right);
	vec2 operator +(const vec2& right);
	vec2 operator +=(const vec2& right);
};

struct vec3
{
	float x, y, z;
	vec3();
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
	vec2 pos; //moves along x and z(y will be used in place of z
	Model () {}
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


struct vector2
{
	float x,z;

	vector2(float _x,float _z);
	
};
struct vector3
{
	float x,y,z;
	vector3() = default;	
	vector3(float _x, float _y, float _z);

	void operator()(float _x, float _y, float _z);

	vector3  operator=(vector3 & right);

	vector3 operator+(vector3  right);
/*
	void rotateY
*/
};



class Camera{
	private:
		vector3 wPos;//world position
		vector3 pos;
		vector3 front;
		vector3 up;
		float radius;
		float pitch;
		float yaw;
	public:
        //view was private
		vector3 view;
		Camera();
		void update();
		
		void drawCamera(GLuint);
		void rotate(float direction);
		void translate(vector2 direction);

};

#endif
