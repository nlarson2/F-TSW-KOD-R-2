//Author: Nickolas Larson
//Date: 2/14/2019
//Modified By: Nickolas Larson
//Modified 3/02/2019

#ifndef NICKOLAS_L_CPP
#define NICKOLAS_L_CPP

#include "nickolasL.h"
#include "iostream"

/*============LARSON'S GLOBALS==========*/
NLarsGlobal::NLarsGlobal()
{
	
}

NLarsGlobal& NLarsGlobal::getInstance()
{
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
vec2::vec2(float _x,float _y)
{
	x = _x;
	y = _y;
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

vec3::vec3(float _x, float _y, float _z)
{
			x = _x;
			y = _y;
			z = _z;
}

void vec3::operator()(float _x, float _y, float _z)
{
		x = _x;
		y = _y;
		z = _z;
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
void Image::invertY()
{
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
Model::Model( const char * objFile, const char * texFile )
{
	if(!GenerateModel(objFile)) {
		printf("Failed to generate model\n");
	}
	if(!GenerateTexture(texFile)) {
		printf("Failed to load texture\n");
	}
}

void Model::draw() 
{
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

static Model tiles[2] = {  Model( "tiles/grassPlain.obj" , "tiles/grassPlainTex.png" ),
    	            Model( "tiles/mountain.obj" , "tiles/mountainTex.png" )};

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
	
	GenerateGLTexture(texture, texFile, true);
	return glIsTexture(texture);

}

/*=======================================*/
/*=======================================*/


Map::Map(int map[], int _width, int _height){
		mapW = _width;
		mapH = _height;
		tile = new Tile *[mapW];
		for(int i = 0; i<25;i++){
				tile[i] = new Tile[mapH];
		}
		int count = 0;
		for(int i = 0; i < 25; i++){

				for(int j = 0; j < 25 ; j++){
					printf("%d\n",count);
					tile[i][j].modelID = map[count];
					tile[i][j].x = 2.0*j;
					tile[i][j].z = 1.70710378118f*i;
					if(i%2 == 0)
						tile[i][j].x -= 1.0f;
					count++;
				}
		}
}

void Map::draw(){
	for(int i = 0; i < 25; i++){
		for(int j = 0; j< 25; j++){
			tiles[tile[i][j].modelID].pos.x = tile[i][j].x;
			tiles[tile[i][j].modelID].pos.y = tile[i][j].z;
			tiles[tile[i][j].modelID].draw();
		}
	}
}





Camera::Camera()
{	
	
	yaw = 180.0f;
	radius = 10.0f;
	pos( sin(yaw * PI / 180)*radius, 8.0f, 
		cos(yaw * PI / 180)*radius);
	front( 0, 0, 0);
	up( 0, 1.0f, 0);	
	pitch = 45.0f;
	view((pos.x + front.x),
		(pos.y + front.y),
		(pos.z + front.z));
	wPos(0,0,0);			
}

Camera::Camera(float rot, int posx, int posz)
{	
	
	yaw = rot;
	wPos.x = posx;
	wPos.z = posz;
	radius = 10.0f;
	pos( sin(yaw * PI / 180)*radius, 8.0f, 
		cos(yaw * PI / 180)*radius);
	front( 0, 0, 0);
	up( 0, 1.0f, 0);	
	pitch = 45.0f;
	view((pos.x + front.x),
		(pos.y + front.y),
		(pos.z + front.z));
	wPos(0,0,0);			
}

void Camera::update()
{
	view((wPos.x + front.x),
		(wPos.y + front.y),
		(wPos.z + front.z));
	
	gluLookAt(pos.x+wPos.x,  pos.y+wPos.y,  pos.z+wPos.z,
			view.x, view.y, view.z,
			up.x,   up.y,   up.z);
}

void Camera::drawCamera(GLuint texture)
{	

	glBindTexture( GL_TEXTURE_2D, texture);
    glPushMatrix();
    
	glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f(view.x+1, 0.5f , view.z+1);
		
        glTexCoord2f(1, 0);
		glVertex3f(view.x+1, 0.5f , view.z-1);
		
        glTexCoord2f(0, 0);
		glVertex3f(view.x-1, 0.5f , view.z-1);
		
        glTexCoord2f(0, 1);
		glVertex3f(view.x-1, 0.5f , view.z+1);
		glColor3f(1.0f,1.0f,1.0f);
	glEnd();
	glPopMatrix();
	glBindTexture( GL_TEXTURE_2D, 0);
}

void Camera::rotate(float direction)
{
	yaw -= direction;
	if(yaw < -180)
		yaw = 180;
	else if(yaw > 180)
		yaw = -180;
	pos.x = sin(yaw * PI / 180)*radius;	
	pos.z = cos(yaw * PI / 180)*radius;
	//printf("X: %f  Z: %f\n",pos.x, pos.z); 
}
void Camera::translate(vec2 direction)
{
	if(direction.y)
	{
		direction.x = (pos.x/6)*direction.y;
		direction.y = (pos.z/6)*direction.y;
	}else
	{	
		direction.x = (pos.z/6) * direction.x;
		direction.y = -(pos.x/6) * direction.x;
	}
	
	wPos.x += direction.x;
	wPos.z += direction.y;

//	front.x += direction.x;
//	front.z += direction.z;
}

/*=======================================*/
/*===============WORLDGS=================*/
WorldGS::WorldGS(int* mapArr,int sizex,int sizey,
	float camRot, int posx, int posz,
	float xres, float yres) :
	map(mapArr, sizex, sizey), camera(camRot, posx, posz)
{	
	this->xres = xres;
	this->yres = yres;
	initWGS_GL();
}

void WorldGS::initWGS_GL()
{
	 //OpenGL initialization
    glViewport(0, 0, xres, yres);
    //Initialize matrices
    
    
    //3D perspective view
    
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)xres/(GLfloat)yres,0.1f,100.0f);


	//discussed futher in later tutorial
	glShadeModel(GL_SMOOTH);//enables smooth shading

	// sets the depth buffer//stop elements from drawing over others
	glClearDepth(1.0f);//Depth buffer setup
	glEnable(GL_DEPTH_TEST);//Enables Depth Testing
	glDepthFunc(GL_LEQUAL);//The type of depth test to do


	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//??makes the perspective view better??
    


    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //Set 2D mode (no perspective)
    //COMMENT OUT LINE BELOW BEFORE TYRING TO MAKE IT 3D
    //glOrtho(0, g.xres, 0, g.yres, -1, 1);


    //Set the screen background color
    glClearColor(0.1, 0.1, 0.1, 1.0);
    //Insert Fonts
    glEnable(GL_TEXTURE_2D);
}
void WorldGS::procMouseInput(int x, int y)
{
	//picking/UI
}
void WorldGS::procKeyInput(int key)
{
	switch (key) {
            case XK_1:
				//Key 1 was pressed
				break;
			case XK_a:
				camera.translate(vec2(-1,0));
				printf("MoveLeft\n");
				break;
			case XK_d:
				camera.translate(vec2(1,0));
				printf("MoveRight\n");
				break;
			case XK_w:
				camera.translate(vec2(0,-1));
				printf("MoveUp\n");
				break;
			case XK_s:
				camera.translate(vec2(0,1));
				printf("MoveDown\n");
				break;
			case XK_q:
				camera.rotate(-4.0f);
				printf("RotateLeft\n");
				break;
			case XK_e:
				camera.rotate(4.0f);
				printf("RotateRight\n");
				break;
        }
}
void WorldGS::drawGameState()
{
	// set perspective
    //draw map
	//
	//
    //gluPerspective(45.0f, xres/yres, 0.1f, 100.0f);
   // glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	camera.update();
	map.draw();
	camera.drawCamera(0);

	//set ortho

	//draw UI
	//
	//


}

/*=======================================*/
/*=======================================*/
/*=======================================*/
/*=======================================*/

void GenerateGLTexture(GLuint & texture, const char * dataSrc, bool inverted)
{
//IMAGE CLASS NEEDS DEFINITION	
	Image data(dataSrc);
	//flip image data because openGL is inverted on the Y
	if(inverted)
		data.invertY();

	int width = data.width;
	int height = data.height;
	glGenTextures( 1, &texture);
	glBindTexture( GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data.data);
	glBindTexture( GL_TEXTURE_2D, 0);
}

/*=======================================*/


#endif
