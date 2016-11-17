#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\OpenGL.hpp>
#include <iostream>
#include <string>

class Go_Go_Clock
{
	GLuint clock_texture;
	GLuint background_texture;
	SYSTEMTIME systime;
	SYSTEMTIME previos_time;
	int WNDHEIGHT = 800;
	int WNDWIDTH = 800;
public:
	Go_Go_Clock();
	~Go_Go_Clock();
	GLuint Load_Texture(std::string name);
	void Set_Clock(std::string name_of_texture);
	void Draw_Clock();
	void Update_Clock();
	int  y_angle, z_angle;
};

