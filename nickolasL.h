//Author: Nickolas Larson
//Date: 2/14/2019
//Modified By: Nickolas Larson
//Modified 2/23/2019

#ifndef NICKOLAS_L_H
#define NICKOLAS_L_H

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <GL/glx.h>
#include "fonts.h"
#include "Image.h"


using namespace std;



#define PI 3.14159265359;

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


void GenerateGLTexture(GLuint & texture, const char * dataSrc);

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





#endif
