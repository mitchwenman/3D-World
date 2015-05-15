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
#include "TangentWaveFrontPolygon.h"
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
#include "TangentPolygonWorldObject.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "SpecularColourMap.h"
#include "SpecularNormalMap.h"
#include "HighlightShaderProgram.h"
#include "Maze.h"
#include "Animation.h"
#include "MazeWalker.h"


//----------------- globals ------------------------------------
bool stereo = false;	//- turns it on or off
long eyes = 10;			//- distance between eyes

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
	
	// Object Files
	std::cout << "Loading object files...";
	TangentWaveFrontPolygon* tableObj = new TangentWaveFrontPolygon("Table.wob");
	TangentWaveFrontPolygon* cube = new TangentWaveFrontPolygon("crate.wob");
	WaveFrontPolygon* moon = new WaveFrontPolygon("sphere.wob");
	std::cout << "Done." << std::endl;

	//Shader programs
	std::cout << "Loading textures...";
	SpecularColourMap *mars = new SpecularColourMap("Mars.bmp");
	SpecularColourMap *moonTex = new SpecularColourMap("moon-texture.bmp");
	SpecularColourMap *earthTex = new SpecularColourMap("earth.bmp");
	SpecularNormalMap *nMap = new SpecularNormalMap("marble-texture.bmp", "marble-normal.bmp");
	SpecularNormalMap *crateTexture = new SpecularNormalMap("box-wood-texture.bmp", "box-wood-normal.bmp");
	std::cout << "Done." << std::endl;

	//--- Heightmap
	std::cout << "Loading terrain...";
	HeightMap *h = new HeightMap();
	h->loadFromImage("terrain-heightmap-surround.bmp");
	World* world = world->getInstance();
	HeightMapWorldObject *hm = new HeightMapWorldObject(h, mars);
	world->heightMap = hm;
	std::cout << "Done." << std::endl;

	//Table
	TangentPolygonWorldObject *table = new TangentPolygonWorldObject(tableObj, nMap);
	Vertex4 tableTrans = { 5.0, .25, 6, 0 };
	Transformation *tableTranslate = new Transformation(TRANSLATE, tableTrans);
	table->transformations.push_back(tableTranslate);
	Vertex4 tableSc = { 2, 2, 2, 0 };
	Transformation *tableScale = new Transformation(SCALE, tableSc);
	table->transformations.push_back(tableScale);
	world->insertObject(table);
	
	TangentPolygonWorldObject *table2 = new TangentPolygonWorldObject(tableObj, nMap);
	Vertex4 table2Trans = { 12.25, .25, 4, 0 };
	Transformation *table2Translate = new Transformation(TRANSLATE, table2Trans);
	table2->transformations.push_back(table2Translate);
	Vertex4 table2Sc = { 2, 2, 2, 0 };
	Transformation *table2Scale = new Transformation(SCALE, table2Sc);
	table2->transformations.push_back(table2Scale);
	world->insertObject(table2);
	

	//Box
	TangentPolygonWorldObject *crate1 = new TangentPolygonWorldObject(cube, crateTexture); 
	Vertex4 crate1TransVals = { 7.5, .25, .5, 0 };
	Transformation *crate1Translate = new Transformation(TRANSLATE, crate1TransVals);
	Vertex4 crate1ScaleVals = { 0.5, 0.5, 0.5, 0 };
	Transformation *crate1Scale = new Transformation(SCALE, crate1ScaleVals);
	crate1->transformations.push_back(crate1Translate);
	crate1->transformations.push_back(crate1Scale);
	world->insertObject(crate1);

	TangentPolygonWorldObject* crate2 = new TangentPolygonWorldObject(cube, crateTexture);
	Vertex4 crate2TransVals = { 11, .5, -.5, 0 };
	Transformation *crate2Translate = new Transformation(TRANSLATE, crate2TransVals);
	crate2->transformations.push_back(crate2Translate);
	world->insertObject(crate2);
	
	// Moon
	Vertex4 scaleVals = { 0.5, 0.5, 0.5, 0 };
	Transformation *scaleTrans = new Transformation(SCALE, scaleVals);

	Vertex4 values = { 0, 0, 0, 0 };
	Vertex4 aniValues = { 0.5, 0, 1, 0 };
	Animation *ani = new Animation(ROTATE, values, 50, aniValues);
	Vertex4 transVals = { 0, 3.5, 1.75, 0 };
	Transformation *trans = new Transformation(TRANSLATE, transVals);
	PolygonWorldObject *moonWO = new PolygonWorldObject(moon, moonTex);
	
	moonWO->transformations.push_back(ani);
	moonWO->transformations.push_back(trans);
	moonWO->transformations.push_back(scaleTrans);

	//Earth
	PolygonWorldObject *earthWO = new PolygonWorldObject(moon, earthTex);
	Vertex4 earthTransVals = { 0, 3.5, 0, 0 };
	Transformation *earthTrans = new Transformation(TRANSLATE, earthTransVals);
	earthWO->transformations.push_back(earthTrans);
	Animation *earthAni = new Animation(ROTATE, values, 50, aniValues);
	earthWO->transformations.push_back(earthAni);

	moonWO->boundingSphere.setTransform(moonWO->transformations);
	earthWO->boundingSphere.setTransform(earthWO->transformations);

	world->insertObject(moonWO);
	world->insertObject(earthWO);

	
	//Maze
	Maze *maze = new Maze("Maze.txt", cube);
	world->maze = maze;

	//Maze walker
	MazeWalker *mazeWalker = new MazeWalker(cube, crateTexture, maze); //Inserts itself into the world
	
	//Setup light
	DirectionalLight *dirLight = DirectionalLight::getSingleton();
	Vertex4 position = { -50, -50, -100 , 0 };
	Vertex4 diffuse = { 1, 1, 1, 1};
	Vertex4 ambient = { .3, .3, .3, 1 };
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
	glEnable(GL_DEPTH_TEST);
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
	case ']': eyes++;	break;
	case '[': eyes--;	break;
	case 27 : exit(0);	break;
	default:
		UserInput::handleKeyInput(c, x, y);
	}
}

void special(int key, int x, int y)
{
	UserInput::handleSpecialKeyInput(key, x, y);
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
