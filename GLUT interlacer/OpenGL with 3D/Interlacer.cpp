#include "Interlacer.h"

#ifdef _WIN32
	#include "libs/glut.h"
#elif __APPLE__
	#include <GLUT/glut.h>
#elif __unix__		// all unices including  __linux__
	#include <GL/glut.h>
#endif

#define INTERLACING_ON

#ifndef INTERLACING_ON

	void DrawLeftSide()	{}
	void DrawRightSide(){}
	void createInterlaceStencil(int gliWindowWidth, int gliWindowHeight){}

#else

	void DrawLeftSide()
	{
		glStencilFunc(GL_NOTEQUAL,1,1); //- draws if stencil != 1
	}

	void DrawRightSide()
	{
		glStencilFunc(GL_EQUAL,1,1);	//- draws if stencil == 1
	}


	void createInterlaceStencil(int gliWindowWidth, int gliWindowHeight)
	{
		GLint gliY;
		//-- setting screen-corresponding geometry
		glViewport(0,0,gliWindowWidth,gliWindowHeight);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0,gliWindowWidth-1,0.0,gliWindowHeight-1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		//-- clearing and configuring stencil drawing
		glDrawBuffer(GL_BACK);
		glEnable(GL_STENCIL_TEST);
		glClearStencil(0);
		glClear(GL_STENCIL_BUFFER_BIT);
		glStencilOp (GL_REPLACE, GL_REPLACE, GL_REPLACE); // colorbuffer is copied to stencil
		glDisable(GL_DEPTH_TEST);
		glStencilFunc(GL_ALWAYS,1,1); // to avoid interaction with stencil content
	
		// drawing stencil pattern
		glColor4f(1,1,1,0);	// alfa is 0 not to interfere with alpha tests
		for (gliY=0; gliY<gliWindowHeight; gliY+=2)
		{
			glLineWidth(1);
			glBegin(GL_LINES);
				glVertex2f(0,gliY);
				glVertex2f(gliWindowWidth,gliY);
			glEnd();	
		}
		glStencilOp (GL_KEEP, GL_KEEP, GL_KEEP); // disabling changes in stencil buffer
		glFlush();
		glEnable(GL_DEPTH_TEST);
	}
#endif

