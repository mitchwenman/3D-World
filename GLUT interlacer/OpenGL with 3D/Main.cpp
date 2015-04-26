#include <stdlib.h>
#include <stdio.h>

#define INTERLACING_ON
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
#include "WaveFrontPolygon.h"
#include "ModelTransform.h"
#include "WaveFrontPolygonDrawer.h"
#include "GraphicsSettings.h"
#include "Camera.h"
#include "UserInput.h"
#include "Frustum.h"
#include "CameraUtil.h"
#include "Lighting.h"
#include "HeightMap.h"

//----------------- globals ------------------------------------
bool stereo = false;	//- turns it on or off
long eyes = 10;			//- distance between eyes
WaveFrontPolygon *poly;
float angle = 0.5;
HeightMap* h;
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

void renderScene()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	glFrustum(-1, 1, -1, 1, .1, 200);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	Camera *cam = Camera::getSingleton();
	//cam->setCamera();
	Vertex3 eye = cam->getEye();
	Vertex3 at = cam->getCentre();
	gluLookAt(eye.x, 1.0, eye.z, at.x, 1.0, at.z, 0, 1, 0);
	glColor3f(255, 255, 255);
	h->render();
	GraphicsSettings *gset = GraphicsSettings::getSingleton();
	
	//gset->resetModelView();
	//gset->resetProjectionView();
	
	//Setup material
	//-- usually	objects	have	a	white	specular	reflection
	GLfloat	material_specular[]	= {	1.0, 1.0, 1.0, 1.0f	};
	//-- set the ambient	and	diffuse	colour	to	be	the	same
	GLfloat	material_diffuse_and_ambient[] = {	0, .75, .5,	1.0f };
	//-- set	the	shininess	from	range	[0,128]
	GLfloat	material_shininess[] = { 100 };
			

	Vertex4 position = { 0, 5, 20, 0 };
	Vertex4 diffuse = { 1, 1, 1, 1 };
	Vertex4 ambient = { .2, .2, .2, 1 };
	Vertex3 direction = { 0, 0, -1 };
	
	Lighting::setupSpotLight(position, diffuse, ambient, direction, 30);
		//-- set specular reflection
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	//-- set shininess
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);
	//-- set diffuse and ambient properties
	glMaterialfv(GL_FRONT_AND_BACK,	GL_AMBIENT,	material_diffuse_and_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse_and_ambient);
	
	WaveFrontPolygonDrawer::draw(*poly);
	
	
	//Frustum::getSingleton()->setFrustum();

	//ModelTransform::translate(0, 0, -5);
	//ModelTransform::rotate(angle += 0.1, 0, 1, 0);
	//gset->setGLMatrices(); //Give the matrices to openGL via glLoadMatrixf
	//Setup lighting after matrix setup
	
	
	
	
	/*
	gset->resetModelView();
	Camera::getSingleton()->setCamera();
	ModelTransform::translate(-1, 0, 0);
	//ModelTransform::rotate(angle, 0, 1, 0);
	
	//---Scene
	gset->setGLMatrices(); //Give the matrices to openGL
	Lighting::setupSpotLight(position, diffuse, ambient, direction, 50.0);
	WaveFrontPolygonDrawer::draw(*poly);
	*/
	//----- 
	/*
	gset->resetModelView();
	gset->resetProjectionView();
	*/
}

void display(void)
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	
	//-----
	
	if (stereo)
	{
		DrawLeftSide();
		renderScene();
		//Get the difference
		Camera* cam = Camera::getSingleton();
		Vertex3 leftEye = cam->getEye();
		Vertex3 rightEye = CameraUtil::calculateRightEye(*cam, eyes/100.0);
		//Modify camera
		Vertex3 centre = cam->getCentre();
		Vertex3 up = cam->getUp();
		cam->lookAt(rightEye.x, rightEye.y, rightEye.z, centre.x, centre.y, centre.z, up.x, up.y, up.z);
		//Render the scene
		DrawRightSide();
		renderScene();
		//Reset the camera
		cam->lookAt(leftEye.x, leftEye.y, leftEye.z, centre.x, centre.y, centre.z, up.x, up.y, up.z);
	} else
	{		
		renderScene(); //just render the scene
	}
	
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
	case 27 : exit(0);	break;
	default:
		UserInput::handleKeyInput(c, x, y);
	}
}

void special(int key, int x, int y)
{
	kb((unsigned char)key, x, y);
}

void reshape(int w,int h)
{
	GraphicsSettings::getSingleton()->setFrameDimensions(w, h);
	glViewport(0,0,w,h);
	createInterlaceStencil(w,h);
}   

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL | GLUT_DEPTH);
	int width = 600;
	int height = 600;
	glutInitWindowSize(600, 600); 
	GraphicsSettings::getSingleton()->setFrameDimensions(width, height);
	glutCreateWindow("OpenGL Interlacer");
	init();
	poly = WFObjectLoader::loadObjectFile("Cube-mod.wob");
	h = new HeightMap();
	h->loadFromImage("terrain-heightmap-surround.bmp");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(kb);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}
