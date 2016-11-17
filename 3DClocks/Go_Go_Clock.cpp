#include "Go_Go_Clock.h"
#include <gl\GLU.h>




Go_Go_Clock::Go_Go_Clock()
{
	y_angle = z_angle = 0;
}


Go_Go_Clock::~Go_Go_Clock()
{
}


GLuint Go_Go_Clock::Load_Texture(std::string name)
{
	sf::Image texture;
    if(!texture.loadFromFile(name))
		return EXIT_FAILURE;
	GLuint temp = 0;
	texture.flipVertically();
	glGenTextures(1, &temp);
	glBindTexture(GL_TEXTURE_2D, temp);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texture.getSize().x, texture.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}


void Go_Go_Clock::Set_Clock(std::string name)
{
	//clock_texture = Load_Texture(name);
	GetSystemTime(&systime);
	previos_time = systime;
	//bind opengl
}


void Go_Go_Clock::Draw_Clock()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	/*glBindTexture(GL_TEXTURE_2D, clock_texture);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 200);
	glTexCoord2f(1, 0); glVertex3f(100, 100, 200);
	glTexCoord2f(1, 1); glVertex3f(100, 100, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
	glEnd();*/

	
	GLfloat cubeVertexArray[8][3];
	GLfloat cubeColorArray[8][3];
	GLubyte cubeIndexArray[6][4];

	cubeVertexArray[0][0] = 0.0;
	cubeVertexArray[0][1] = 0.0;
	cubeVertexArray[0][2] = 100.0;

	cubeVertexArray[1][0] = 0.0;
	cubeVertexArray[1][1] = 100.0;
	cubeVertexArray[1][2] = 100.0;

	cubeVertexArray[2][0] = 100.0;
	cubeVertexArray[2][1] = 100.0;
	cubeVertexArray[2][2] = 100.0;

	cubeVertexArray[3][0] = 100.0;
	cubeVertexArray[3][1] = 0.0;
	cubeVertexArray[3][2] = 100.0;

	cubeVertexArray[4][0] = 0.0;
	cubeVertexArray[4][1] = 0.0;
	cubeVertexArray[4][2] = 0.0;

	cubeVertexArray[5][0] = 0.0;
	cubeVertexArray[5][1] = 100.0;
	cubeVertexArray[5][2] = 0.0;

	cubeVertexArray[6][0] = 100.0;
	cubeVertexArray[6][1] = 100.0;
	cubeVertexArray[6][2] = 0.0;

	cubeVertexArray[7][0] = 100.0;
	cubeVertexArray[7][1] = 0.0;
	cubeVertexArray[7][2] = 0.0;

	cubeColorArray[0][0] = 0.0;
cubeColorArray[0][1] = 0.0;
cubeColorArray[0][2] = 1.0;
 
cubeColorArray[1][0] = 0.6;
cubeColorArray[1][1] = 0.98;
cubeColorArray[1][2] = 0.6;
 
cubeColorArray[2][0] = 1.0;
cubeColorArray[2][1] = 0.84;
cubeColorArray[2][2] = 0.8;
 
cubeColorArray[3][0] = 0.8;
cubeColorArray[3][1] = 0.36;
cubeColorArray[3][2] = 0.36;
 
cubeColorArray[4][0] = 1.0;
cubeColorArray[4][1] = 0.27;
cubeColorArray[4][2] = 0.0;
 
cubeColorArray[5][0] = 0.82;
cubeColorArray[5][1] = 0.13;
cubeColorArray[5][2] = 0.56;
 
cubeColorArray[6][0] = 0.54;
cubeColorArray[6][1] = 0.17;
cubeColorArray[6][2] = 0.89;
 
cubeColorArray[7][0] = 0.0;
cubeColorArray[7][1] = 1.0;
cubeColorArray[7][2] = 1.0;

	cubeIndexArray[0][0] = 0;
	cubeIndexArray[0][1] = 3;
	cubeIndexArray[0][2] = 2;
	cubeIndexArray[0][3] = 1;

	cubeIndexArray[1][0] = 0;
	cubeIndexArray[1][1] = 1;
	cubeIndexArray[1][2] = 5;
	cubeIndexArray[1][3] = 4;

	cubeIndexArray[2][0] = 7;
	cubeIndexArray[2][1] = 4;
	cubeIndexArray[2][2] = 5;
	cubeIndexArray[2][3] = 6;

	cubeIndexArray[3][0] = 3;
	cubeIndexArray[3][1] = 7;
	cubeIndexArray[3][2] = 6;
	cubeIndexArray[3][3] = 2;

	cubeIndexArray[4][0] = 1;
	cubeIndexArray[4][1] = 2;
	cubeIndexArray[4][2] = 6;
	cubeIndexArray[4][3] = 5;

	cubeIndexArray[5][0] = 0;
	cubeIndexArray[5][1] = 4;
	cubeIndexArray[5][2] = 7;
	cubeIndexArray[5][3] = 3;

	glVertexPointer(3, GL_FLOAT, 0, cubeVertexArray);
	//glTexCoordPointer(2, GL_FLOAT, 0, cubeTextureArray);
	glColorPointer(3, GL_FLOAT, 0, cubeColorArray);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndexArray);
}


void Go_Go_Clock::Update_Clock()
{
	//move clockwises
}