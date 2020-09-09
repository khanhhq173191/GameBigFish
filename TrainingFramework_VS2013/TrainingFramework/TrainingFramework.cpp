// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include"../Include/Box2D/Box2D.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "model.h"
#include "Texture.h"
#include "Object.h"
#include "Matran.h"
#include "Camera.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Singleton.h"
#include "Sprite2D.h"
#include "Animation2D.h"
#include <conio.h>
#include <iostream>
#include <time.h>


using namespace std;
GLuint vboId, iboId, textureID, matrixID;
Shaders myShaders;
Matran matrix;
int a, b;
int m, n;
float TimeFlash = 0.0;
bool first = true;
bool s;
bool Move = false;
bool Flash = false;
int Init ( ESContext *esContext )
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Singleton<ResourceManager>::GetInstance()->loadResource("../Resources/Resource.txt");
	Singleton<SceneManager>::GetInstance()->loadObjects("../Resources/Scene.txt");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return 0;
}

void Draw ( ESContext *esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Singleton<Game>::GetInstance()->Draw();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime)
{	
	Singleton<Game>::GetInstance()->Update_animation(deltaTime);
	if (Move) {
		Singleton<Game>::GetInstance()->mouse_animation_move(a, b, deltaTime);
	}

	if (Flash && TimeFlash < 0.3) {
	Singleton<Game>::GetInstance()->mouse_animation_flash(m, n, deltaTime);
	TimeFlash += deltaTime;
}
	//Singleton<Game>::GetInstance()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	Singleton<Game>::GetInstance()->Key(key, bIsPressed);
}

void TouchActionDown(ESContext* esContext, int x, int y)
{	
	Flash = true;
	TimeFlash = 0;
	m = x;
	n = y;
}

void TouchActionUp(ESContext* esContext, int x, int y)
{	
	Flash = false;
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	Move = true;
	a = x;
	b = y;
}

void CleanUp()
{	
	for (int i = 0; i < Singleton<ResourceManager>::GetInstance()->modelsNum; i++) {
		glDeleteBuffers(1, &Singleton<ResourceManager>::GetInstance()->models[i].vboId);
		glDeleteBuffers(1, &Singleton<ResourceManager>::GetInstance()->models[i].iboId);
	}
	for (int i = 0; i < Singleton<ResourceManager>::GetInstance()->modelsNum; i++) {
		Singleton<ResourceManager>::GetInstance()->free();
	}
	//glDeleteBuffers(1, &Singleton<Sprite2D>::GetInstance()->anim->model.vboId);
	//glDeleteBuffers(1, &Singleton<Sprite2D>::GetInstance()->anim->model.iboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

