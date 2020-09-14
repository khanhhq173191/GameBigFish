#include "stdafx.h"
#include "SceneManager.h"
#include "Singleton.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < objectNum; i++) {
		delete[] objects[i].texture;
		delete[] objects[i].cubeTexture;
		delete[] objects[i].shaders.m_texture;
	}
	for (int i = 0; i < animNum; i++) {
		delete[] botFish[i].texture;
		delete[] botFish[i].cubeTexture;
		delete[] botFish[i].shaders.m_texture;
	}
	delete[] playerFish[0].texture;
	delete[] playerFish[0].cubeTexture;
	delete[] playerFish[0].shaders.m_texture;
	delete[] objects;
	delete[] anim;
	delete[] botFish;
	delete[] playerFish;
}

void SceneManager::loadObjects(char *l) {
	int ob, objectID, modelID, textureID, cubeTextureID, shaderID, textureNum, cubeTextureNum;
	float anim_speed;
	int animID;
	FILE *file;
	file = fopen(l, "r");
	fscanf(file, "#Objects: %d\n", &objectNum);
	objects = new Objects[objectNum];
	//anim = new Animation2D[objectNum];
	for(int i = 0; i < objectNum; i++){
		fscanf(file, "ID %d\n", &objectID);
		fscanf(file, "MODEL %d\n", &modelID);
		objects[objectID].models = modelID;

		fscanf(file, "TEXTURES %d\n", &textureNum);
		objects[objectID].texture = new int[textureNum];
		objects[objectID].textureNum = textureNum;
		for (int j = 0; j < textureNum; j++) {
			fscanf(file, "TEXTURE %d\n", &textureID);
			objects[objectID].texture[j] = textureID;
		}

		fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
		objects[objectID].cubeTexture = new int[cubeTextureNum];
		objects[objectID].cubeTextureNum = cubeTextureNum;
		for (int j = 0; j < cubeTextureNum; j++) {
			fscanf(file, "CUBETEX %d\n", &cubeTextureID);	
			objects[objectID].cubeTexture[j] = cubeTextureID;
		}

		fscanf(file, "SHADER %d\n", &shaderID);
		objects[objectID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
		int a = objects[objectID].textureNum;
		objects[objectID].shaders.m_texture = new int[a];
		fscanf(file, "POSITION %f, %f, %f\n", &objects[objectID].txw, &objects[objectID].tyw, &objects[objectID].tzw);
		fscanf(file, "ROTATION %f, %f, %f\n", &objects[objectID].rxw, &objects[objectID].ryw, &objects[objectID].rzw);
		fscanf(file, "SCALE %f, %f, %f\n", &objects[objectID].sxw, &objects[objectID].syw, &objects[objectID].szw);
	}

	fscanf(file, "#Animations: %d\n", &animNum);
	anim = new Animation2D[animNum];
	botFish = new BotFish[animNum];
	playerFish = new PlayerFish[1];
	for (int i = 0; i < animNum; i++) {
		if (i == 0) {
			fscanf(file, "ID %d\n", &animID);
			fscanf(file, "MODEL %d\n", &modelID);
			playerFish[animID].models = modelID;
			playerFish[animID].load_element("../Resources/sprites (1).txt");

			fscanf(file, "FRAME %d\n", &playerFish[animID].frameNum);
			playerFish[animID].frame = Singleton<ResourceManager>::GetInstance()->frames[playerFish[animID].frameNum];

			fscanf(file, "TEXTURES %d\n", &textureNum);
			playerFish[animID].texture = new int[textureNum];
			playerFish[animID].textureNum = textureNum;
			for (int j = 0; j < textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &textureID);
				playerFish[animID].texture[j] = textureID;
			}
			playerFish[animID].curent_texture = playerFish[animID].texture[0];
			playerFish[animID].play();

			fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
			for (int j = 0; j < cubeTextureNum; j++) {
				fscanf(file, "CUBETEX %d\n", &cubeTextureID);
			}

			fscanf(file, "SHADER %d\n", &shaderID);

			playerFish[animID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
			int a = playerFish[animID].textureNum;
			playerFish[animID].shaders.m_texture = new int[a];
			fscanf(file, "SPEED %f\n", &playerFish[animID].speed);
			fscanf(file, "SIZE %d\n", &playerFish[animID].size);
			playerFish[animID].vb = 8 - playerFish[animID].size;
			fscanf(file, "POSITION %f, %f, %f\n", &playerFish[animID].txw, &playerFish[animID].tyw, &playerFish[animID].tzw);
			fscanf(file, "ROTATION %f, %f, %f\n", &playerFish[animID].rxw, &playerFish[animID].ryw, &playerFish[animID].rzw);
			fscanf(file, "SCALE %f, %f, %f\n", &playerFish[animID].sxw, &playerFish[animID].syw, &playerFish[animID].szw);
			playerFish[i].sx = playerFish[i].sxw;
			playerFish[i].sy = playerFish[i].syw;
			playerFish[i].sz = playerFish[i].szw;
		}
		else {
			fscanf(file, "ID %d\n", &animID);
			fscanf(file, "MODEL %d\n", &modelID);
			botFish[animID].models = modelID;
			botFish[animID].load_element("../Resources/sprites (1).txt");


			fscanf(file, "FRAME %d\n", &botFish[animID].frameNum);
			botFish[animID].frame = Singleton<ResourceManager>::GetInstance()->frames[botFish[animID].frameNum];

			fscanf(file, "TEXTURES %d\n", &textureNum);
			botFish[animID].texture = new int[textureNum];
			botFish[animID].textureNum = textureNum;
			for (int j = 0; j < textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &textureID);
				botFish[animID].texture[j] = textureID;
			}
			botFish[animID].curent_texture = botFish[animID].texture[0];
			botFish[animID].play();

			fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
			for (int j = 0; j < cubeTextureNum; j++) {
				fscanf(file, "CUBETEX %d\n", &cubeTextureID);
			}

			fscanf(file, "SHADER %d\n", &shaderID);

			botFish[animID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
			int a = botFish[animID].textureNum;
			botFish[animID].shaders.m_texture = new int[a];
			fscanf(file, "SPEED %f\n", &botFish[animID].speed);
			fscanf(file, "SIZE %d\n", &botFish[animID].size);
			botFish[animID].vb = 10 - botFish[animID].size; // VAN TOC CA BOT
			fscanf(file, "POSITION %f, %f, %f\n", &botFish[animID].txw, &botFish[animID].tyw, &botFish[animID].tzw);
			fscanf(file, "ROTATION %f, %f, %f\n", &botFish[animID].rxw, &botFish[animID].ryw, &botFish[animID].rzw);
			fscanf(file, "SCALE %f, %f, %f\n", &botFish[animID].sxw, &botFish[animID].syw, &botFish[animID].szw);
			botFish[i].sx = botFish[i].sxw;
			botFish[i].sy = botFish[i].syw;
			botFish[i].sz = botFish[i].szw;
		}
	}

	fscanf(file, "#CAMERA\nNEAR %f\nFAR %f\nFOV %f\nSPEED %f", &Singleton<Camera>::GetInstance()->nearPlane, &Singleton<Camera>::GetInstance()->farPlane,
		&Singleton<Camera>::GetInstance()->fov, &Singleton<Camera>::GetInstance()->speed);
	fclose(file);
	for (int i = 1; i < animNum-1; i++) {
		botFish[i].tzw = playerFish[0].tzw - (i * 0.01);
	}
}

void SceneManager::draw() {
	Singleton<Camera>::GetInstance()->set_CamVP();
	objects[0].draw();
	for (int i = animNum - 2; i >= 0; i--) {
		if (i == 0) playerFish[i].draw_anim();
		else botFish[i].draw_anim();
	}
	botFish[25].draw_anim();
	for (int i = objectNum - 1; i > 0; i--) {
		objects[i].draw();
	}
}


void SceneManager::update_animation(float deltaTime) {
	objects[19].update();
	objects[20].update();
	objects[21].update();
	objects[22].update();
	objects[23].update();



	for (int i = 0; i < animNum; i++) {
		if (i == 0) playerFish[i].update(deltaTime);
		else botFish[i].update(deltaTime);
	}
	if (m_time > 0.03) {
		m_time = 0;
		for (int i = 1; i < 22; i++) {
			botFish[i].update_animation_move_boss(deltaTime);
		}
	}
	else {
		m_time += deltaTime;
	}
	if (!playerFish[0].dis) {
		checkCoCirCir();
		checkColRecRecP();
		objects[24].txw = 2;
		objects[24].tyw = 2;
	}
	else
	{
		objects[24].txw = playerFish[0].txw;
		objects[24].tyw = playerFish[0].tyw;
	}
	checkColRecRec();
	LevelUp(point);
}

void SceneManager::mouse_animation_move(int x, int y, float deltaTime)
{
	if (m_pTime > 0.01) {
		m_pTime = 0;
		playerFish[0].update_animation_move_player(x, y);
	}
	else {
		m_pTime += deltaTime;
	}
}

void SceneManager::mouse_animation_flash(int x, int y, float deltaTime)
{
	if (m_pTime > 0.01) {
		m_pTime = 0;
		playerFish[0].update_animation_flash_player(x, y);
	}
	else {
		m_pTime += deltaTime;
	}
}

void SceneManager::updateScore()
{
	int a = point;
	for (int i = 0; i < 6; i++) {
		objects[25 + i].texture[0] = 43 + (a % 10);
		a = a / 10;
	}
}



void SceneManager::LevelUp(int i)
{
	if (i >= 100 && i < 1000 && d == 0) {
		playerFish[0].size = 4;
		playerFish[0].sxw = 0.15;
		playerFish[0].syw = 0.15;
		playerFish[0].szw = 0.15;
		objects[24].sxw = 0.273;
		objects[24].syw = 0.273;
		objects[24].szw = 0.273;
		s = 1;
		botFish[25].countFrameTransform = 0;
		d++;

	}
	else if(i >= 1000 && d == 1 )
	{
		playerFish[0].size = 6;
		playerFish[0].sxw = 0.18;
		playerFish[0].syw = 0.18;
		playerFish[0].szw = 0.18;
		objects[24].sxw = 0.306;
		objects[24].syw = 0.306;
		objects[24].szw = 0.306;
		s = 1;
		botFish[25].countFrameTransform = 0;
		d++;
	}
	if (s == 1) {
		botFish[25].txw = playerFish[0].txw;
		botFish[25].tyw = playerFish[0].tyw;
	}
	if (botFish[25].countFrameTransform == 10) {
		botFish[25].txw = 2;
		botFish[25].tyw = 2;
		botFish[25].countFrameTransform = 0;
		s = 0;
	}
}

void SceneManager::free() {
}

bool SceneManager::checkEvent()
{	
	return false;
}

bool SceneManager::checkCoRec(Rectangl rec, Circle cir)
{	
	for (int i = 1; i < animNum; i++) {
	}
	return false;
}

bool SceneManager::checkCoCirCir()
{
	for (int i = 1; i < animNum; i++) {
		if (Singleton<Physic>::GetInstance()->checkCoCirCir(playerFish[0].cir, botFish[i].cir)) {
			if (playerFish[0].size > botFish[i].size) {
				botFish[i].m_hx = -playerFish[0].x_temp + botFish[i].x_temp;
				botFish[i].m_hy = -playerFish[0].y_temp + botFish[i].y_temp;
				}
			else if (playerFish[0].size < botFish[i].size) {
				botFish[i].m_hx = playerFish[0].x_temp - botFish[i].x_temp;
				botFish[i].m_hy = playerFish[0].y_temp - botFish[i].y_temp;
				}
			}
		}
	return true;
}

bool SceneManager::checkColRecRec()
{
	
	for (int i = 1; i < animNum - 1; i++) {
		for (int j = i + 1; j < animNum; j++) {
			if (Singleton<Physic>::GetInstance()->checkColRecRec(botFish[i].rect, botFish[j].rect) && i != j) {
				if (botFish[i].size > botFish[j].size) {
					botFish[i].signal = 3;
					botFish[j].disapear_wait = 1;
				}
				else if (botFish[j].size > botFish[i].size) {
					botFish[j].signal = 3;
					botFish[i].disapear_wait = 1;
				}
			}
		}
	}
	return true;
}

void SceneManager::checkColRecRecP()
{
	for (int i = 1; i < animNum; i++) {
		if (Singleton<Physic>::GetInstance()->checkColRecRec(playerFish[0].rect, botFish[i].rect)) {
			if (playerFish[0].size > botFish[i].size) {
				playerFish[0].signal = 3;
				if (botFish[i].disapear_wait == 0) {
					botFish[i].scoreScene(i % 4);
					botFish[i].frameCountScore = 0;
				}
				botFish[i].disapear_wait = 1;
			}
			else if (playerFish[0].size < botFish[i].size) {
				botFish[i].signal = 3;
				playerFish[0].disapear_wait = 1;
			}
		}
	}

}
