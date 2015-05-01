#include <stdlib.h>
#include <stdio.h>
#include <iostream>

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
#include "ShaderLoader.h"
#include "World.h"
#include "MaterialData.h"
#include "Transformation.h"
#include "HeightMapWorldObject.h"
#include "Polygon.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "SpecularColourMap.h"


//----------------- globals ------------------------------------
bool stereo = false;	//- turns it on or off
long eyes = 10;			//- distance between eyes
float angle = 0.5;
unsigned int program;
unsigned int test_texture_program;

Texture* texture;
Texture* normalMap;
//----------------- functions ----------------------------------

void init()
{
	glEnable(GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);
	int winwid = glutGet(GLUT_WINDOW_WIDTH);
	int winhei = glutGet(GLUT_WINDOW_HEIGHT);
	createInterlaceStencil(winwid,winhei);
	glewInit();
	unsigned int shader = ShaderLoader::compile("phong_vert.txt", GL_VERTEX_SHADER);
	unsigned int fragShader = ShaderLoader::compile("phong_frag.txt", GL_FRAGMENT_SHADER);
	program = ShaderLoader::link(shader, fragShader);
	
	WaveFrontPolygon* poly = new WaveFrontPolygon("Cube-mod.wob");

	HeightMap *h = new HeightMap();
	h->loadFromImage("terrain-heightmap-surround.bmp");
	World* world = world->getInstance();
	
	//Setup material
	//-- usually	objects	have	a	white	specular	reflection
	GLfloat	material_specular[4]	= {	1.0, 1.0, 1.0, 1.0f	};
	//-- set the ambient	and	diffuse	colour	to	be	the	same
	GLfloat	material_diffuse_and_ambient[4] = {	0, .75, .5,	1.0f };
	//-- set	the	shininess	from	range	[0,128]
	GLfloat	material_shininess[1] = { 20 };
	MaterialData* matData = new MaterialData(material_specular, material_diffuse_and_ambient, 
									material_diffuse_and_ambient, material_shininess);
	HeightMapWorldObject *hm = new HeightMapWorldObject(h);
	Vertex4 trans = { 0, .5, -0.5, 0};
	
	world->insertObject(hm);	

	SpecularColourMap *cMap = new SpecularColourMap("wood_floor.bmp");
	PolygonWorldObject *pwo = new PolygonWorldObject(poly, cMap);
	Transformation *translate = new Transformation(TRANSLATE, trans);
	//pwo->transformations.push_back(translate);
	world->insertObject(pwo);
	//----------------

	//Setup light
	DirectionalLight *dirLight = DirectionalLight::getSingleton();
	Vertex4 position = { 50, 50, -100 , 0 };
	Vertex4 diffuse = { 1, 1, 1, 1};
	Vertex4 ambient = { .2, .2, .2, 1 };
	dirLight->setLight(position, ambient, diffuse);
}

void renderScene()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	
	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	GraphicsSettings *gset = GraphicsSettings::getSingleton();	
	gset->resetModelView();
	gset->resetProjectionView();
	Camera *cam = Camera::getSingleton();
	cam->setCamera();
	Frustum::getSingleton()->setFrustum();	
	gset->setGLMatrices();
	//Light setup
	DirectionalLight::getSingleton()->setLight();

	
	World::getInstance()->draw();
	
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
	glEnable(GL_NORMALIZE);
	
	
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
	
	
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(kb);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}
