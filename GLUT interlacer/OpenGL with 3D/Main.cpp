#include <stdlib.h>
#include <stdio.h>

//----------------- includes --------------------------------
#ifdef _WIN32
	#include "libs\glew.h"
	#include "libs/glut.h"

	#include <windows.h>
	#pragma comment(lib, "winmm.lib")			//- not required but have it in anyway
	#pragma comment(lib, "libs/glut32.lib")
#elif __APPLE__
	#include <GLUT/glut.h>
#elif __unix__		// all unices including  __linux__
	#include <GL/glut.h>
#endif

#include "Interlacer.h"

#include "WFObjectLoader.h"
#include <math.h>


//----------------- globals ------------------------------------
bool stereo = false;	//- turns it on or off
long eyes = 10;			//- distance between eyes
WaveFrontPolygon *poly;
//----------------- functions ----------------------------------

void drawCircle(double radius, double cx, double cy)
{
	int numPoints = 50;
	glBegin(GL_TRIANGLE_FAN);
		glVertex2d(cx, cy);
		for (int i = 0; i < numPoints; i++)
		{
			double angle = ((2 * 3.14)/numPoints) * i;
			double x = radius * cos(angle) + cx;
			double y = radius * sin(angle) + cy;
			glVertex2d(x, y);
		}
	glEnd();
}

void DrawTriangle(int eyes)
{
	float e = eyes / 100.0;
	glBegin( GL_TRIANGLES );
	{
		glVertex2f( e+0.0f, 1.5f );
		glVertex2f( e+1.75f, -1.5f );
		glVertex2f( e-1.75f, -1.5f );
	}
	glEnd();
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glCullFace(GL_BACK);
	int winwid = glutGet(GLUT_WINDOW_WIDTH);
	int winhei = glutGet(GLUT_WINDOW_HEIGHT);
	createInterlaceStencil(winwid,winhei);
	glewInit();
	
}

void display(void)
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//-----
	
	int numVerts = poly->vertices.size();
	std::vector<double> verts;
	verts.reserve(numVerts * 3);
	for (int i = 0; i < numVerts; i++)
	{
		verts.push_back(poly->vertices[i].x);
		verts.push_back(poly->vertices[i].y);
		verts.push_back(poly->vertices[i].z);
	}
	std::vector<GLubyte> indices;
	for (unsigned int i = 0; i < poly->faces.size(); i++)
	{
		indices.insert(indices.end(), poly->faces[i].vertexIndices.begin(),
			poly->faces[i].vertexIndices.end());
	}
	float colours[] = 
	{
		0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1,
		1, 0, 1, 1, 0, 0
	};
	glTranslatef(-.5, -.5, 0);
	glRotatef(45, 0, 1, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, verts.data());
	glColorPointer(3, GL_FLOAT, 0, colours);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, indices.data());
	GLenum err = glGetError();
	glDisableClientState(GL_VERTEX_ARRAY);

	//-----

	glutSwapBuffers();
	glutPostRedisplay();
}

void kb(unsigned char c, int x, int y)
{
	switch (c) 
	{ 
	case 's': stereo ^= 1, eyes = 10;break;
	case ']': eyes++;	break;
	case '[': eyes--;	break;
	case 27 : exit(0);
	}
}

void reshape(int w,int h)
{
	glViewport(0,0,w,h);
	createInterlaceStencil(w,h);
}   

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL | GLUT_DEPTH);
	glutInitWindowSize(600, 600); 
	glutCreateWindow("OpenGL Interlacer");
	init();
	poly = WFObjectLoader::loadObjectFile("Cube-mod.obj");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(kb);
	glutMainLoop();
	return 0;
}
