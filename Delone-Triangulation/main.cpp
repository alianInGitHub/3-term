#include <iostream>
#include <vector>
#include <freeglut.h>
#include <sstream>
#include <string>
#include <Windows.h>
#include <stdio.h> 
#include "Node.h"
#include "Triangle.h"


using namespace std;

HINSTANCE dllHandle = NULL;
BOOL freeResult, runTimeLinkSuccess = FALSE;

typedef std::vector<Triangle*> (CALLBACK* TriangulationType)(std::vector<Node>);


vector<Node> nodes;
vector<Triangle*>triangles;

void push_key(unsigned char key, int x, int y)
{
	if(key == 13)
	{
		//triangulation
		TriangulationType TriangulationPtr = NULL;

		//Load the dll and keep the handle to it
		dllHandle = LoadLibrary((LPWSTR)"Triangulation.dll");
		if (dllHandle != NULL)
		{
			//Get pointer to our function using GetProcAddress:
			TriangulationPtr = (TriangulationType)GetProcAddress(dllHandle, "TriangulationDelone");
		}
		// If the function address is valid, call the function. 
		if (runTimeLinkSuccess = (NULL != TriangulationPtr))
		{
			triangles = TriangulationPtr(nodes);
		}
		//Free the library:
		freeResult = FreeLibrary(dllHandle);
		if (!runTimeLinkSuccess)
			cout << "Problem" << endl;
		//triangles = Triangulation::TriangulationDelone(nodes);
	}
	if (key == GLUT_KEY_DELETE)
	{
		nodes.erase(nodes.begin(), nodes.end());
		triangles.erase(triangles.begin(), triangles.end());
	}
	glutPostRedisplay();
}


void mouse_press(int button, int updown, int x, int y)
{
	if(updown == GLUT_DOWN)
	{
		Node new_node((float)x,(float)y);
		nodes.push_back(new_node);
	}
	glutPostRedisplay();
}


void draw_triangles()
{
	glBegin(GL_LINES);
	for(vector<Triangle*>::iterator it = triangles.begin(); it != triangles.end(); it++)
	{
		glVertex2i((**it)[0].x,(**it)[0].y);
		glVertex2i((**it)[1].x,(**it)[1].y);
		glVertex2i((**it)[0].x,(**it)[0].y);
		glVertex2i((**it)[2].x,(**it)[2].y);
		glVertex2i((**it)[1].x,(**it)[1].y);
		glVertex2i((**it)[2].x,(**it)[2].y);
	}
	glEnd();
}


void display()
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glColor3d ( 1.0, 0.0, 0.0 ) ;
	 glPointSize(10);
	 if(!nodes.empty())
	 {
		 glBegin(GL_POINTS);
	     for(vector<Node>::iterator it = nodes.begin(); it != nodes.end(); it++)
	     {
	      	glVertex2f((*it).x ,(*it).y);
	     }
	     glEnd();
		 for (auto i : nodes)
		 {
			 glRasterPos2f(i.x + 5, i.y + 5);
			 stringstream ss;
			 ss << (int)i.x;
			 glutBitmapString(GLUT_BITMAP_HELVETICA_12 , (unsigned char*)ss.str().c_str());
			 glRasterPos2f(i.x + 5, i.y + 15);
			 stringstream s;
			 s << (int)i.y;
			 glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)s.str().c_str());
		 }
	 }
	 if(!triangles.empty())
		 draw_triangles();
	glutSwapBuffers();
}


void reshape(int width, int height)
{
	glViewport(0 , 0, width, height);
	gluOrtho2D(0,600,600,0);
}

 
int main(int argc, char *argv[])
{

	int pargc = argc;
    /* Set up the OpenGL parameters */
    glEnable ( GL_DEPTH_TEST ) ;
    glClearColor ( 0.0, 0.0, 0.0, 0.0 ) ;
    glClearDepth ( 1.0 ) ;
    /* Initialize GLUT */
    glutInitWindowSize ( 600, 600 ) ;
    glutInit ( &pargc, argv ) ;
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ) ;


    /* Create the window */
    glutCreateWindow ( "Triangulation Delone" ) ;
    glutKeyboardFunc ( push_key ) ;
    glutMouseFunc ( mouse_press ) ;
    glutDisplayFunc ( display ) ;
    glutReshapeFunc ( reshape ) ;
	/* Initialize the attractor:  The easiest way is to call the keyboard callback with an
     * argument of 'r' for Reset.
     */
    push_key ( 'r', 0, 0 ) ;

    /* Enter the GLUT main loop */
    glutMainLoop () ;

    #ifdef _MSC_VER
    /* DUMP MEMORY LEAK INFORMATION */
    _CrtDumpMemoryLeaks () ;
    #endif
}