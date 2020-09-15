#pragma once
#include "../Utilities/utilities.h"
#include "Box2D/Box2D.h"
#include "Singleton.h"
#include "SceneManager.h"
#include <iostream>

class Game
{
public:
	bool Eat = false, Flash = false, LevelUp = false, Disapear = false;
	bool MoveR = false, MoveL = false, MoveU = false, MoveD = false, MoveF = false, MoveB = false;
	bool RotateL = false, RotateR = false, RotateU = false, RotateD = false;
	Game(void);
	~Game(void);
	static Game* GetInstance();
	void Update(float deltaTime);
	void Update_animation(float);
	void mouse_animation_move(int x, int y, float deltime);
	void mouse_animation_flash(int x, int y, float deltime);
	void Key( unsigned char key, bool bIsPressed);
	void Draw();
	bool checkEvent();

private:
	static Game* s_Instance;
};

