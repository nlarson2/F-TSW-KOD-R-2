
#ifndef NICKOLAS_L_CPP
#define NICKOLAS_L_CPP

#include "nickolasL.h"

class Image;

/*============LARSON'S GLOBALS==========*/
NLarsGlobal::NLarsGlobal() {
	
}

NLarsGlobal& NLarsGlobal::getInstance() {
	static NLarsGlobal instance;
	return instance;
}

/*=======================================*/


/*========VECTORE MATH(vec2/vec3)========*/

//vec2-----------------------------------
vec2::vec2() 
{
	x = y = 0;
}
vec2 vec2::operator = (const vec2& right)
{
	x = right.x;
	y = right.y;
	return *this;
}
vec2 vec2::operator +(const vec2& right)
{
	vec2 ret;
	ret.x = x + right.x;
	ret.y = y + right.y;
	return ret;

}
vec2 vec2::operator +=(const vec2& right)
{
	return *this + right;
	
}
//---------------------------------------
//vec3-----------------------------------
vec3::vec3()
{
	x = y = z = 0;
}
vec3 vec3::operator = (const vec3& right)
{	
	x = right.x;
        y = right.y;
	z = right.z;
        return *this;
}
vec3 vec3::operator +(const vec3& right)
{
	vec3 ret;
        ret.x = x + right.x;
        ret.y = y + right.y;
	ret.z = z + right.z;
        return ret;
}
vec3 vec3::operator +=(const vec3& right)
{
	return *this + right;
}
//---------------------------------------
/*=======================================*/


/*=====Function added to Image Class=====*/
void Image::invertY() {
	unsigned char flip[height][width*3];
	int iter = 0, i, j;
	for ( i = 0 ; i < height ; i++ ) {
		for ( j = 0 ; j < width * 3 ; j++ ) {
			flip[i][j] = data[iter++];
		}
	}

	iter = 0;
	for ( i = height - 1 ; i >= 0 ; i-- ) {
		for ( j = 0 ; j < width * 3 ; j++ ) {
			data[iter++] = flip[i][j];
		}
	}
}

/*=======================================*/


/*==============Draw Credits=============*/

void draw_nickLCredit(int x, int y, GLuint texture)
{
	Rect r;
	float wid = 50;
	glPushMatrix();
	glTranslatef(x,y,0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
	glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);


	glTranslatef(wid,0,0);
	//unsigned int c = 0x00000000;
	r.bot = 0;
	r.left = 10;
	r.center = 0;
	ggprint8b(&r, 16, 0x00000000, "Nickolas Larson");


	glPopMatrix();
}

/*=======================================*/


/*============MODEL STUCTURE=============*/
Model::Model( const char * objFile, const char * texFile ) {
	if(!GenerateModel(objFile)) {
		printf("Failed to generate model\n");
	}
	if(!GenerateTexture(texFile)) {
		printf("Failed to load texture\n");
	}
}

void Model::draw() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);

	for( unsigned int i = 0 ; i < vIndices.size() ; i+=3 ) {
		glTexCoord2f(vertTex[vtIndices.at(i)-1].x,
				vertTex[vtIndices.at(i)-1].y);
		glVertex3f(vert[vIndices.at(i)-1].x + pos.x ,
				vert[vIndices.at(i)-1].y ,
				vert[vIndices.at(i)-1].z + pos.y);
		glTexCoord2f(vertTex[vtIndices.at(i+1)-1].x,
				vertTex[vtIndices.at(i+1)-1].y);
		glVertex3f(vert[vIndices.at(i+1)-1].x + pos.x,
				vert[vIndices.at(i+1)-1].y,
				vert[vIndices.at(i+1)-1].z + pos.y);
		glTexCoord2f(vertTex[vtIndices.at(i+2)-1].x,
				vertTex[vtIndices.at(i+2)-1].y);
		glVertex3f(vert[vIndices.at(i+2)-1].x + pos.x,
				vert[vIndices.at(i+2)-1].y,
				vert[vIndices.at(i+2)-1].z + pos.y);
	}

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);



}


bool Model::GenerateModel( const char * objFile) {
	FILE * inFile= fopen(objFile,"r");
	if(!inFile){
		cout<<"Could Not Locate File Specified\n";
		return 0;
	}
	cout << "File opened succesfully\n";

	while(1){

		char line[128];
		if(fscanf(inFile,"%s",line)==EOF) {
			break;
		}

		//v=vertices vt=textureCoords vn=normals f=faces(holds multiple datas
		if(strcmp(line,"v")==0){
			vec3 vertex;
			fscanf(inFile,"%f %f %f\n",
					&vertex.x,&vertex.y,&vertex.z);
			vert.push_back(vertex);
		}else if(strcmp(line,"vt")==0){
			vec2 texture;
			fscanf(inFile,"%f %f\n",
					&texture.x,&texture.y);
			vertTex.push_back(texture);
		}else if(strcmp(line,"vn")==0){
			vec3 norm;
			fscanf(inFile,"%f %f %f\n", &norm.x, &norm.y, &norm.z);
			vertNorm.push_back(norm);
		}else if(strcmp(line,"f")==0){
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3],
			textureIndex[3],normalIndex[3];
			int matches = fscanf(inFile,
					"%d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIndex[0], &textureIndex[0], &normalIndex[0],
					&vertexIndex[1], &textureIndex[1], &normalIndex[1],
					&vertexIndex[2], &textureIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("%d Failed to read\n",matches);
				return false;
			}
			//save all the data where it needs to be stored
			vIndices.push_back(vertexIndex[0]);
			vIndices.push_back(vertexIndex[1]);
			vIndices.push_back(vertexIndex[2]);
			vtIndices.push_back(textureIndex[0]);
			vtIndices.push_back(textureIndex[1]);
			vtIndices.push_back(textureIndex[2]);
			vnIndices.push_back(normalIndex[0]);
			vnIndices.push_back(normalIndex[1]);
			vnIndices.push_back(normalIndex[2]);
		}


	}
	fclose(inFile);
	return true;
}

bool Model::GenerateTexture ( const char * texFile ) {
	//IMAGE CLASS NEEDS DEFINITION	
	Image data = new Image(texFile);
	int width = data->width;
	int height = data->height;
	glGenTextures( 1, &texture);
	glBindTexture( GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data->data);
	glBindTexture( GL_TEXTURE_2D, 0);

	return glIsTexture(texture);

}

/*=======================================*/
/*=======================================*/
/*=======================================*/
/*=======================================*/
/*=======================================*/
/*=======================================*/
/*=======================================*/
/*=======================================*/
/*=======================================*/


#endif
