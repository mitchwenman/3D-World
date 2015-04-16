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

#include <math.h>

//----------------- globals ------------------------------------
bool stereo = false;	//- turns it on or off
long eyes = 10;			//- distance between eyes
GLuint vbo[1], vao[1];
//----------------- functions ----------------------------------

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
	float triangle[] = 
	{
		0.0, 1.0, 0.0,
		-1.0, -1.0, 0.0,
		1.0, -1.0, 0
	};
	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

void display(void)
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//-----
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
	glutInitWindowSize(1000, 600); 
	glutCreateWindow("OpenGL Interlacer");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(kb);
	glutMainLoop();
	return 0;
}
