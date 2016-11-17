#pragma once
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Shader.hpp>
#include <gl\GLU.h>
#include <string>
#include <iostream>
#include "Camera.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <math.h>

#define GL_CLAMP_TO_EDGE 0x812F

void display();

class Clocks
{
	GLuint clockTexture[9];
	SYSTEMTIME currentTime;
	glm::vec3 clockPos;              // center of the object
	glm::vec3 clockwiseHourPos;      // position of array's end
	glm::vec3 clockwiseMinutePos;
	glm::vec3 clockwiseSecPos;
	int clockwiseHourLen;
	int clockwiseMinuteLen;
	int clockwiseSecLen;
	glm::vec3 clockSize;
	glm::vec3 delta;
	Camera* myCamera;
	int xRotateAngle, yRotateAngle;

	void Set();
	void clockUpdate();
	GLuint LoadTexture(std::string source_name);
public:
	Clocks();
	~Clocks();
	void drawCubeSide(const GLfloat side[30], short int numnberOfTexture);
	void drawClockwises();
	void Update();
	
	glm::vec3 getClockSize() { return clockSize; }
	glm::vec3 getDeltaSize() { return delta; }
};


