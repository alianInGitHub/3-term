#pragma once
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include <glut.h>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

#define PI 3.141592
#define DELTA_ANGLE 1;


class Camera
{
	float xAngle, yAngle;   // angles of camera rotation
	glm::vec3 cameraPos;
	float speed;

	void move();
	void changeAngle();

public:
	Camera();
	Camera(int x, int y, int z, float xAngle, float yAngle);
	~Camera();
	void Update();
	glm::vec3 getPos()
	{
		return cameraPos;
	}
};

