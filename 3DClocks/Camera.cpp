#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}


Camera::Camera(int x, int y, int z, float xAngle, float yAngle)
{
	cameraPos.x = x;
	cameraPos.y = y;
	cameraPos.z = z;
	this->xAngle = xAngle;
	this->yAngle = yAngle;
	this->speed = 0.5;
}


void Camera::Update()
{
	changeAngle();
	move();
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,                                                                           // camera position
		cameraPos.x - sin(xAngle / 180 * PI), cameraPos.y + tan(yAngle / 180 * PI), cameraPos.z - cos(xAngle / 180 * PI),      // center
		0, 1, 0);																											   // up
}


// move in opted direction
void Camera::move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		cameraPos.x += sin((xAngle + 90) / 180 * PI) * speed;
		cameraPos.z += cos((xAngle + 90) / 180 * PI) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		cameraPos.x += sin((xAngle - 90) / 180 * PI) * speed;
		cameraPos.z += cos((xAngle - 90) / 180 * PI) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		cameraPos.x += -sin(xAngle / 180 * PI) * speed;
		cameraPos.y +=  tan(yAngle / 180 * PI) * speed;
		cameraPos.z += -cos(xAngle / 180 * PI) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		cameraPos.x +=  sin(xAngle / 180 * PI) * speed;
		cameraPos.y += -tan(yAngle / 180 * PI) * speed;
		cameraPos.z +=  cos(xAngle / 180 * PI) * speed;
	}
}


// rotate camera
void Camera::changeAngle()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		yAngle += DELTA_ANGLE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		yAngle -= DELTA_ANGLE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		xAngle += DELTA_ANGLE;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		xAngle -= DELTA_ANGLE;
	}

	if (yAngle < -89.0) yAngle = -89.0;
	if (yAngle >  89.0) yAngle =  89.0;
}