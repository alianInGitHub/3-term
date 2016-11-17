#include <glew.h>
#include "Clocks.h"


#define PI 3.14159265359


Clocks::Clocks()
{
	GetSystemTime(&currentTime);
	xRotateAngle = yRotateAngle = 0;

	clockPos.x = clockPos.y = clockPos.z = 0.0;

	delta.x = 5;
	delta.y = 5;
	delta.z = 6;

	clockSize.x = 30;
	clockSize.y = 30;
	clockSize.z = 8;
	
	clockwiseHourLen = clockSize.x - 12;
	clockwiseMinuteLen = clockSize.x - 9;
	clockwiseSecLen = clockSize.x - 5;

	clockUpdate();
	Set();
}


Clocks::~Clocks()
{
	//delete textures
	glDeleteTextures(1, &clockTexture[0]);
	glDeleteTextures(1, &clockTexture[1]);
	glDeleteTextures(1, &clockTexture[2]);
	glDeleteTextures(1, &clockTexture[3]);
	glDeleteTextures(1, &clockTexture[4]);
	glDeleteTextures(1, &clockTexture[5]);
	glDeleteTextures(1, &clockTexture[6]);
	glDeleteTextures(1, &clockTexture[7]);
	glDeleteTextures(1, &clockTexture[8]);
}


GLuint Clocks::LoadTexture(std::string name)
{
	sf::Image image;
	if (!image.loadFromFile(name))
		return EXIT_FAILURE;
	image.flipVertically();
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	return texture;
}


void Clocks::Set()
{
	//clock cube
	//back
	clockTexture[0] = LoadTexture("clocks_image.png");
	//left
	clockTexture[2] = LoadTexture("side1.png");
	//front
	clockTexture[1] = LoadTexture("side2.png");
	//right
	clockTexture[3] = LoadTexture("side3.png");
	//top
	clockTexture[4] = LoadTexture("side3.png");
	//bottom
	clockTexture[5] = LoadTexture("side3.png");

	//clockwises
	clockTexture[6] = LoadTexture("secund_clockwise.png");
	clockTexture[7] = LoadTexture("minute_clockwise.png");
	clockTexture[8] = LoadTexture("hour_clockwise.png");

	myCamera = new Camera(0, 0, 0, 0.0, 0.0);
}


void Clocks::drawCubeSide(const GLfloat side[30], short int numnberOfTexture)
{
	glBindTexture(GL_TEXTURE_2D, clockTexture[numnberOfTexture]);
	glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), side);
	glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), side + 3);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


void Clocks::drawClockwises()
{
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex3f(clockPos.x, clockPos.y, clockSize.z);
	glVertex3f(clockwiseHourPos.x, clockwiseHourPos.y, clockwiseHourPos.z);
	glVertex3f(clockPos.x, clockPos.y, clockSize.z);
	glVertex3f(clockwiseMinutePos.x, clockwiseMinutePos.y, clockwiseMinutePos.z);
	glVertex3f(clockPos.x, clockPos.y, clockSize.z);
	glVertex3f(clockwiseSecPos.x, clockwiseSecPos.y, clockwiseSecPos.z);
	glEnd();

}


void Clocks::clockUpdate()
{
	clockwiseHourPos.y = cos((float)currentTime.wHour / 12 * 2 * PI ) * clockwiseHourLen;
	clockwiseHourPos.x = sin((float)currentTime.wHour / 12 * 2 * PI ) * clockwiseHourLen;
	clockwiseHourPos.z = clockSize.z + 0.1;

	clockwiseMinutePos.y = cos((float)currentTime.wMinute / 60 * 2 * PI ) * clockwiseMinuteLen;
	clockwiseMinutePos.x = sin((float)currentTime.wMinute / 60 * 2 * PI ) * clockwiseMinuteLen;
	clockwiseMinutePos.z = clockSize.z + 0.1;

	clockwiseSecPos.y = cos((float)currentTime.wSecond / 60 * 2 * PI ) * clockwiseSecLen;
	clockwiseSecPos.x = sin((float)currentTime.wSecond / 60 * 2 * PI ) * clockwiseSecLen;
	clockwiseSecPos.z = clockSize.z + 0.1;
	
}


void Clocks::Update()
{
	GetSystemTime(&currentTime);
	clockUpdate();
	myCamera->Update();
}
