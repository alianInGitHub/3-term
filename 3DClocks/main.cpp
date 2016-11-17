
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Clocks.h"

int main()
{
	// Request a 24-bits depth buffer when creating the window
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
	window.setVerticalSyncEnabled(true);

	// Create a sprite for the background
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("wall.jpg"))
		return EXIT_FAILURE;
	sf::Sprite background(backgroundTexture);
	
	window.setActive();

	Clocks DesktopClock;

	// Enable Z-buffer read and write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);

	// Disable lighting
	glDisable(GL_LIGHTING);

	// Configure the viewport (the same size as the window)
	glViewport(0, 0, window.getSize().x, window.getSize().y);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);

	// Bind the texture
	glEnable(GL_TEXTURE_2D);

	// Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
	glm::vec3 size = DesktopClock.getClockSize();
	glm::vec3 deltaSize = DesktopClock.getDeltaSize();

	// FRONT
	static const GLfloat cube[30] =
	{
		-size.x, -size.y,  size.z,  0, 0,
		 size.x, -size.y,  size.z,  1, 0,
		-size.x,  size.y,  size.z,  0, 1,
		-size.x,  size.y,  size.z,  0, 1,
	 	 size.x, -size.y,  size.z,  1, 0,
		 size.x,  size.y,  size.z,  1, 1
	};
	size.x += deltaSize.x;
	size.y += deltaSize.y;
	//BACK
	static const GLfloat cube1[30] =
	{
		-size.x, -size.y, -size.z,  0, 0,
		 size.x, -size.y, -size.z,  1, 0,
		-size.x,  size.y, -size.z,  0, 1,
		-size.x,  size.y, -size.z,  0, 1,
		 size.x, -size.y, -size.z,  1, 0,
		 size.x,  size.y, -size.z,  1, 1,
	};
	
	//RIGHT
	static const GLfloat cube2[30] =
	{
		size.x, -size.y, -size.z,  0, 0,
		size.x,  size.y, -size.z,  1, 0,
		size.x, -size.y,  size.z + deltaSize.z,  0, 1,
		size.x, -size.y,  size.z + deltaSize.z,  0, 1,
		size.x,  size.y, -size.z,  1, 0,
		size.x,  size.y,  size.z + deltaSize.z,  1, 1,
	};
	//LEFT
	static const GLfloat cube3[30] =
	{
		// positions    // texture coordinates
		-size.x, -size.y, -size.z,  0, 0,
		-size.x,  size.y, -size.z,  1, 0,
		-size.x, -size.y,  size.z + deltaSize.z,  0, 1,
		-size.x, -size.y,  size.z + deltaSize.z,  0, 1,
		-size.x,  size.y, -size.z,  1, 0,
		-size.x,  size.y,  size.z + deltaSize.z,  1, 1,
	};
	//UPPER
	static const GLfloat cube4[30] =
	{
		-size.x, -size.y, -size.z,  0, 0,
		 size.x, -size.y, -size.z,  1, 0,
		-size.x, -size.y,  size.z + deltaSize.z,  0, 1,
		-size.x, -size.y,  size.z + deltaSize.z,  0, 1,
		 size.x, -size.y, -size.z,  1, 0,
		 size.x, -size.y,  size.z + deltaSize.z,  1, 1,
	};
	//BOTTOM
	static const GLfloat cube5[30] =
	{
		-size.x,  size.y, -size.z,  0, 0,
		 size.x,  size.y, -size.z,  1, 0,
		-size.x,  size.y,  size.z + deltaSize.z,  0, 1,
		-size.x,  size.y,  size.z + deltaSize.z,  0, 1,
		 size.x,  size.y, -size.z,  1, 0,
		 size.x,  size.y,  size.z + deltaSize.z,  1, 1,
	};

	//sides of width
	// upper
	size.z += deltaSize.z;
	size.y -= deltaSize.y;
	static const GLfloat cube6[30] =
	{
		-size.x, size.y, size.z,  0, 0,
		 size.x, size.y , size.z,  1, 0,
		-size.x,  size.y + deltaSize.y, size.z,  0, 1,
		-size.x,  size.y + deltaSize.y, size.z,  0, 1,
		 size.x, size.y, size.z,  1, 0,
		 size.x,  size.y + deltaSize.y, size.z,  1, 1,
	};
	static const GLfloat cube61[30]
	{
		-size.x, size.y, size.z, 0, 0,
		size.x, size.y, size.z, 1, 0,
		-size.x, size.y, size.z - deltaSize.z, 0, 1,
		-size.x, size.y, size.z - deltaSize.z, 0, 1,
		size.x, size.y, size.z, 1, 0,
		size.x, size.y, size.z - deltaSize.z, 1, 1
	};
	//bottom
	static const GLfloat cube7[30] = 
	{
		-size.x, -size.y - deltaSize.y,  size.z,  0, 0,
		 size.x, -size.y - deltaSize.y,  size.z,  1, 0,
		-size.x, -size.y,  size.z,  0, 1,
		-size.x, -size.y,  size.z,  0, 1,
		 size.x, -size.y - deltaSize.y,  size.z,  1, 0,
		 size.x, -size.y,  size.z,  1, 1
	};
	static const GLfloat cube71[30]
	{
		-size.x, -size.y, size.z, 0, 0,
		size.x, -size.y, size.z, 1, 0,
		-size.x, -size.y, size.z - deltaSize.z, 0, 1,
		-size.x, -size.y, size.z - deltaSize.z, 0, 1,
		size.x, -size.y, size.z, 1, 0,
		size.x, -size.y, size.z - deltaSize.z, 1, 1
	};
	size.x -= deltaSize.x;
	//left
	static const GLfloat cube8[30] =
	{
		-size.x - deltaSize.x, -size.y,  size.z,  0, 0,
		-size.x, -size.y,  size.z,  1, 0,
		-size.x - deltaSize.x, size.y,  size.z,  0, 1,
		-size.x - deltaSize.x, size.y,  size.z,  0, 1,
		-size.x, -size.y,  size.z,  1, 0,
		-size.x, size.y,  size.z,  1, 1
	};
	static const GLfloat cube81[30] = 
	{
		-size.x, -size.y, size.z, 0, 0,
		-size.x, -size.y, size.z - deltaSize.z, 1, 0,
		-size.x, size.y, size.z, 0, 1,
		-size.x, size.y, size.z, 0, 1,
		-size.x, -size.y, size.z - deltaSize.z, 1, 0,
		-size.x, size.y, size.z - deltaSize.z, 1, 1
	};
	//right
	static const GLfloat cube9[30] =
	{
		size.x, -size.y,  size.z,  0, 0,
		size.x + deltaSize.x, -size.y,  size.z,  1, 0,
		size.x, size.y,  size.z,  0, 1,
		size.x, size.y,  size.z,  0, 1,
		size.x + deltaSize.x, -size.y,  size.z,  1, 0,
		size.x + deltaSize.x, size.y,  size.z,  1, 1
	};
	static const GLfloat cube91[30] = 
	{
		size.x, -size.y, size.z - deltaSize.z, 0, 0,
		size.x, -size.y, size.z, 1, 0,
		size.x, size.y, size.z - deltaSize.z, 0, 1,
		size.x, size.y, size.z - deltaSize.z, 0, 1,
		size.x, -size.y, size.z, 1, 0,
		size.x, size.y, size.z, 1, 1
	};

	// set the hour clockwise parameters
	

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Disable normal and color vertex components
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	// Create a clock for measuring the time elapsed
	sf::Clock clock;

	// Start game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

			// Escape key: exit
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();

			// Adjust the viewport when the window is resized
			if (event.type == sf::Event::Resized)
				glViewport(0, 0, event.size.width, event.size.height);
		}

		// Draw the background
		window.pushGLStates();
		window.draw(background);
		window.popGLStates();

		// Clear the depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);

		// We get the position of the mouse cursor, so that we can move the box accordingly
		float x = sf::Mouse::getPosition(window).x * 200.f / window.getSize().x - 100.f;
		float y = -sf::Mouse::getPosition(window).y * 200.f / window.getSize().y + 100.f;

		// Apply some transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(x, y, -100.f);
		//glRotatef(clock.getElapsedTime().asSeconds() * 45.f, 0.f, 0.f, 1.f);
		DesktopClock.Update();
		//draw FRONT FACE
		DesktopClock.drawCubeSide(cube, 0);
		//draw BACK FACE
		DesktopClock.drawCubeSide(cube1, 1);
		//draw RIGHT FACE
		DesktopClock.drawCubeSide(cube2, 2);
		//draw LEFT FACE
		DesktopClock.drawCubeSide(cube3, 3);
		//draw UPPER FACE
		DesktopClock.drawCubeSide(cube4, 4);
		//draw BOTTOM FACE
		DesktopClock.drawCubeSide(cube5, 5);

		DesktopClock.drawCubeSide(cube6, 5);
		DesktopClock.drawCubeSide(cube7, 5);
		DesktopClock.drawCubeSide(cube8, 5);
		DesktopClock.drawCubeSide(cube9, 5);

		DesktopClock.drawCubeSide(cube61, 5);
		DesktopClock.drawCubeSide(cube71, 5);
		DesktopClock.drawCubeSide(cube81, 5);
		DesktopClock.drawCubeSide(cube91, 5);
		//draw clockwises
		DesktopClock.drawClockwises();

		// Finally, display the rendered frame on screen
		window.display();
	}

	return EXIT_SUCCESS;
}
