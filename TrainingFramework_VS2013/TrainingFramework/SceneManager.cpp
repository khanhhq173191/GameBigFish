#include "stdafx.h"
#include "SceneManager.h"
#include "Singleton.h"
#include <time.h>

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
	for (int i = 0; i < effectAnimNum; i++) {
		delete[] effectAnim[i].texture;
		delete[] effectAnim[i].cubeTexture;
		delete[] effectAnim[i].shaders.m_texture;
	}
	for (int i = 0; i < modelBotFishNum; i++) {
		delete[] modelBotFish[i].texture;
		delete[] modelBotFish[i].cubeTexture;
		delete[] modelBotFish[i].shaders.m_texture;
	}
	delete[] objects;
	delete[] anim;
	delete[] botFish;
	delete[] playerFish;
	delete[] modelBotFish;
	delete[] effectAnim;
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
	for (int i = 0; i < objectNum; i++) {
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
	fscanf(file, "#Num: %d\n", &modelBotFishNum);
	anim = new Animation2D[animNum];
	botFish = new BotFish[animNum];
	playerFish = new PlayerFish[1];
	modelBotFish = new BotFish[modelBotFishNum + 1];
	for (int i = 0; i < 1; i++) {
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
	for (int i = 1; i <= modelBotFishNum; i++) {
			fscanf(file, "ID %d\n", &animID);
			fscanf(file, "MODEL %d\n", &modelID);
			modelBotFish[animID].models = modelID;
			modelBotFish[animID].load_element("../Resources/sprites (1).txt");


			fscanf(file, "FRAME %d\n", &modelBotFish[animID].frameNum);
			modelBotFish[animID].frame = Singleton<ResourceManager>::GetInstance()->frames[modelBotFish[animID].frameNum];

			fscanf(file, "TEXTURES %d\n", &textureNum);
			modelBotFish[animID].texture = new int[textureNum];
			modelBotFish[animID].textureNum = textureNum;
			for (int j = 0; j < textureNum; j++) {
				fscanf(file, "TEXTURE %d\n", &textureID);
				modelBotFish[animID].texture[j] = textureID;
			}
			modelBotFish[animID].curent_texture = modelBotFish[animID].texture[0];
			modelBotFish[animID].play();

			fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
			for (int j = 0; j < cubeTextureNum; j++) {
				fscanf(file, "CUBETEX %d\n", &cubeTextureID);
			}

			fscanf(file, "SHADER %d\n", &shaderID);

			modelBotFish[animID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
			int a = modelBotFish[animID].textureNum;
			modelBotFish[animID].shaders.m_texture = new int[a];
			fscanf(file, "SPEED %f\n", &modelBotFish[animID].speed);
			fscanf(file, "SIZE %d\n", &modelBotFish[animID].size);
			modelBotFish[animID].vb = 8 - modelBotFish[animID].size; // VAN TOC CA BOT
			fscanf(file, "POSITION %f, %f, %f\n", &modelBotFish[animID].txw, &modelBotFish[animID].tyw, &modelBotFish[animID].tzw);
			fscanf(file, "ROTATION %f, %f, %f\n", &modelBotFish[animID].rxw, &modelBotFish[animID].ryw, &modelBotFish[animID].rzw);
			fscanf(file, "SCALE %f, %f, %f\n", &modelBotFish[animID].sxw, &modelBotFish[animID].syw, &modelBotFish[animID].szw);
			modelBotFish[i].sx = modelBotFish[i].sxw;
			modelBotFish[i].sy = modelBotFish[i].syw;
			modelBotFish[i].sz = modelBotFish[i].szw;
		}

	fscanf(file, "#Effect: %d\n", &effectAnimNum);
	effectAnim = new EffectAnim[effectAnimNum];
	for (int i = 0; i < effectAnimNum; i++) {
		fscanf(file, "ID %d\n", &animID);
		fscanf(file, "MODEL %d\n", &modelID);
		effectAnim[animID].models = modelID;
		effectAnim[animID].load_element("../Resources/sprites (1).txt");

		fscanf(file, "FRAME %d\n", &effectAnim[animID].frameNum);
		effectAnim[animID].frame = Singleton<ResourceManager>::GetInstance()->frames[effectAnim[animID].frameNum];

		fscanf(file, "TEXTURES %d\n", &textureNum);
		effectAnim[animID].texture = new int[textureNum];
		effectAnim[animID].textureNum = textureNum;
		for (int j = 0; j < textureNum; j++) {
			fscanf(file, "TEXTURE %d\n", &textureID);
			effectAnim[animID].texture[j] = textureID;
		}
		effectAnim[animID].curent_texture = effectAnim[animID].texture[0];
		effectAnim[animID].play();

		fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
		for (int j = 0; j < cubeTextureNum; j++) {
			fscanf(file, "CUBETEX %d\n", &cubeTextureID);
		}

		fscanf(file, "SHADER %d\n", &shaderID);

		effectAnim[animID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
		int a = effectAnim[animID].textureNum;
		effectAnim[animID].shaders.m_texture = new int[a];
		fscanf(file, "SPEED %f\n", &effectAnim[animID].speed);
		fscanf(file, "SIZE %d\n", &effectAnim[animID].size);
		effectAnim[animID].vb = 8 - effectAnim[animID].size; // VAN TOC CA BOT
		fscanf(file, "POSITION %f, %f, %f\n", &effectAnim[animID].txw, &effectAnim[animID].tyw, &effectAnim[animID].tzw);
		fscanf(file, "ROTATION %f, %f, %f\n", &effectAnim[animID].rxw, &effectAnim[animID].ryw, &effectAnim[animID].rzw);
		fscanf(file, "SCALE %f, %f, %f\n", &effectAnim[animID].sxw, &effectAnim[animID].syw, &effectAnim[animID].szw);
		effectAnim[i].sx = effectAnim[i].sxw;
		effectAnim[i].sy = effectAnim[i].syw;
		effectAnim[i].sz = effectAnim[i].szw;
	}

	fscanf(file, "#CAMERA\nNEAR %f\nFAR %f\nFOV %f\nSPEED %f", &Singleton<Camera>::GetInstance()->nearPlane, &Singleton<Camera>::GetInstance()->farPlane,
		&Singleton<Camera>::GetInstance()->fov, &Singleton<Camera>::GetInstance()->speed);
	fclose(file);

	initBotFish();
	for (int i = 0; i < animNum; i++) {
		botFish[i].tzw = playerFish[0].tzw - (i * 0.001) - 0.001;
	}
}

void SceneManager::initBotFish()
{
	int ob, objectID, modelID, textureID, cubeTextureID, shaderID, textureNum, cubeTextureNum;
	float anim_speed;
	int animID;
	for (int i = 0; i < animNum; i++) {
		FILE *file;
		file = fopen("../Resources/modelfish.txt", "r");
		fscanf(file, "MODEL %d\n", &modelID);
		botFish[i].models = modelID;
		botFish[i].load_element("../Resources/sprites (1).txt");

		fscanf(file, "FRAME %d\n", &botFish[i].frameNum);
		botFish[i].frame = Singleton<ResourceManager>::GetInstance()->frames[botFish[i].frameNum];

		fscanf(file, "TEXTURES %d\n", &textureNum);
		botFish[i].texture = new int[textureNum];
		botFish[i].textureNum = textureNum;
		for (int j = 0; j < textureNum; j++) {
			fscanf(file, "TEXTURE %d\n", &textureID);
			botFish[i].texture[j] = textureID;
		}
		botFish[i].curent_texture = botFish[i].texture[0];
		botFish[i].play();

		fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
		for (int j = 0; j < cubeTextureNum; j++) {
			fscanf(file, "CUBETEX %d\n", &cubeTextureID);
		}

		fscanf(file, "SHADER %d\n", &shaderID);

		botFish[i].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
		int a = botFish[i].textureNum;
		botFish[i].shaders.m_texture = new int[a];
		fscanf(file, "SPEED %f\n", &botFish[i].speed);
		fscanf(file, "SIZE %d\n", &botFish[i].size);
		botFish[i].vb = 8 - botFish[i].size; // VAN TOC CA BOT
		fscanf(file, "POSITION %f, %f, %f\n", &botFish[i].txw, &botFish[i].tyw, &botFish[i].tzw);
		fscanf(file, "ROTATION %f, %f, %f\n", &botFish[i].rxw, &botFish[i].ryw, &botFish[i].rzw);
		fscanf(file, "SCALE %f, %f, %f\n", &botFish[i].sxw, &botFish[i].syw, &botFish[i].szw);
		fclose(file);
	}

	animNumLevel = 20;
	for (int i = 0; i < 12; i++) {
		botFish[i].frameNum = modelBotFish[1].frameNum;
		botFish[i].texture = modelBotFish[1].texture;
		botFish[i].speed = modelBotFish[1].speed;
		botFish[i].size = modelBotFish[1].size;
		botFish[i].sxw = modelBotFish[1].sxw; botFish[i].syw = modelBotFish[1].syw; botFish[i].szw = modelBotFish[1].szw;
		int res = rand() % (4 - 1 + 1) + 1;
		if (res == 1) {
			srand(time(NULL));
			botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
			botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 2) {
			botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
			botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 3) {
			botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
		else if (res == 4) {
			botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
	}
	for (int i = 12; i < 18; i++) {
		botFish[i].frameNum = modelBotFish[2].frameNum;
		botFish[i].texture = modelBotFish[2].texture;
		botFish[i].speed = modelBotFish[2].speed;
		botFish[i].size = modelBotFish[2].size;
		botFish[i].sxw = modelBotFish[2].sxw; botFish[i].syw = modelBotFish[2].syw; botFish[i].szw = modelBotFish[2].szw;
		int res = rand() % (4 - 1 + 1) + 1;
		if (res == 1) {
			srand(time(NULL));
			botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
			botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 2) {
			botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
			botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 3) {
			botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
		else if (res == 4) {
			botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
	}
	for (int i = 18; i < 20; i++) {
		botFish[i].frameNum = modelBotFish[3].frameNum;
		botFish[i].texture = modelBotFish[3].texture;
		botFish[i].speed = modelBotFish[3].speed;
		botFish[i].size = modelBotFish[3].size;
		botFish[i].sxw = modelBotFish[3].sxw; botFish[i].syw = modelBotFish[3].syw; botFish[i].szw = modelBotFish[3].szw;

		int res = rand() % (4 - 1 + 1) + 1;
		if (res == 1) {
			srand(time(NULL));
			botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
			botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 2) {
			botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
			botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 3) {
			botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
		else if (res == 4) {
			botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
	}
}

void SceneManager::setLevel()
{
	if (d == 0) {
		animNumLevel = 26;
		for (int i = 20; i < 21; i++) {
			botFish[i].frameNum = modelBotFish[1].frameNum;
			botFish[i].texture = modelBotFish[1].texture;
			botFish[i].speed = modelBotFish[1].speed;
			botFish[i].size = modelBotFish[1].size;
			botFish[i].sxw = modelBotFish[1].sxw; botFish[i].syw = modelBotFish[1].syw; botFish[i].szw = modelBotFish[1].szw;
			int res = rand() % (4 - 1 + 1) + 1;
			if (res == 1) {
				srand(time(NULL));
				botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 2) {
				botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 3) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
			else if (res == 4) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
		}
		for (int i = 21; i < 23; i++) {
			botFish[i].frameNum = modelBotFish[2].frameNum;
			botFish[i].texture = modelBotFish[2].texture;
			botFish[i].speed = modelBotFish[2].speed;
			botFish[i].size = modelBotFish[2].size;
			botFish[i].sxw = modelBotFish[2].sxw; botFish[i].syw = modelBotFish[2].syw; botFish[i].szw = modelBotFish[2].szw;
			int res = rand() % (4 - 1 + 1) + 1;
			if (res == 1) {
				srand(time(NULL));
				botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 2) {
				botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 3) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
			else if (res == 4) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
		}
		for (int i = 23; i < 26; i++) {
			botFish[i].frameNum = modelBotFish[3].frameNum;
			botFish[i].texture = modelBotFish[3].texture;
			botFish[i].speed = modelBotFish[3].speed;
			botFish[i].size = modelBotFish[3].size;
			botFish[i].sxw = modelBotFish[3].sxw; botFish[i].syw = modelBotFish[3].syw; botFish[i].szw = modelBotFish[3].szw;

			int res = rand() % (4 - 1 + 1) + 1;
			if (res == 1) {
				srand(time(NULL));
				botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 2) {
				botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 3) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
			else if (res == 4) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
		}
	}
	else if (d == 1) {
		animNumLevel = 30;
		for (int i = 26; i < 27; i++) {
			botFish[i].frameNum = modelBotFish[3].frameNum;
			botFish[i].texture = modelBotFish[3].texture;
			botFish[i].speed = modelBotFish[3].speed;
			botFish[i].size = modelBotFish[3].size;
			botFish[i].sxw = modelBotFish[3].sxw; botFish[i].syw = modelBotFish[3].syw; botFish[i].szw = modelBotFish[3].szw;

			int res = rand() % (4 - 1 + 1) + 1;
			if (res == 1) {
				srand(time(NULL));
				botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 2) {
				botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 3) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
			else if (res == 4) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
		}
		for (int i = 27; i < 30; i++) {
			//cout << animNumLevel << endl;
			botFish[i].frameNum = modelBotFish[4].frameNum;
			botFish[i].texture = modelBotFish[4].texture;
			botFish[i].speed = modelBotFish[4].speed;
			botFish[i].size = modelBotFish[4].size;
			botFish[i].sxw = modelBotFish[4].sxw; botFish[i].syw = modelBotFish[4].syw; botFish[i].szw = modelBotFish[4].szw;

			int res = rand() % (4 - 1 + 1) + 1;
			if (res == 1) {
				srand(time(NULL));
				botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 2) {
				botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
				botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
			}
			else if (res == 3) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
			else if (res == 4) {
				botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
				botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
			}
		}
	}
	else if (d == 2) {
	animNumLevel = 32;
	for (int i = 30; i < 32; i++) {
		botFish[i].frameNum = modelBotFish[5].frameNum;
		botFish[i].texture = modelBotFish[5].texture;
		botFish[i].speed = modelBotFish[5].speed;
		botFish[i].size = modelBotFish[5].size;
		botFish[i].sxw = modelBotFish[5].sxw; botFish[i].syw = modelBotFish[5].syw; botFish[i].szw = modelBotFish[5].szw;

		int res = rand() % (4 - 1 + 1) + 1;
		if (res == 1) {
			srand(time(NULL));
			botFish[i].txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
			botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 2) {
			botFish[i].txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
			botFish[i].tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 3) {
			botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			botFish[i].tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
		else if (res == 4) {
			botFish[i].txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			botFish[i].tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
	}
}
}

void SceneManager::draw() {
	Singleton<Camera>::GetInstance()->set_CamVP();
	objects[0].draw();
	cout << animNumLevel << endl;
	for (int i = animNumLevel - 1; i >= 0; i--) {
		botFish[i].draw_anim();
	}
	playerFish[0].draw_anim();
	for (int i = effectAnimNum - 1; i >= 0; i--) {
		effectAnim[i].draw_anim();
	}
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


	playerFish[0].update(deltaTime);
	for (int i = 0; i < animNumLevel; i++) {
		botFish[i].update(deltaTime);
	}
	for (int i = 0; i < effectAnimNum; i++) {
		effectAnim[i].update(deltaTime);
	}
	if (m_time > 0.03) {
		m_time = 0;
		for (int i = 0; i < animNumLevel; i++) {
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
	if (i >= 10 && i < 100 && d == 0) {
		playerFish[0].size = 4;
		playerFish[0].sxw = 0.15;
		playerFish[0].syw = 0.15;
		playerFish[0].szw = 0.15;
		objects[24].sxw = 0.273;
		objects[24].syw = 0.273;
		objects[24].szw = 0.273;
		s = 1;
		effectAnim[3].countFrameTransform = 0;
		effectAnim[3].play();
		setLevel();
		d++;
	}
	else if(i >= 100 && i < 150 && d == 1 )
	{
		playerFish[0].size = 6;
		playerFish[0].sxw = 0.18;
		playerFish[0].syw = 0.18;
		playerFish[0].szw = 0.18;
		objects[24].sxw = 0.306;
		objects[24].syw = 0.306;
		objects[24].szw = 0.306;
		s = 1;
		effectAnim[3].countFrameTransform = 0;
		effectAnim[3].play();
		setLevel();
		d++;
	}
	else if (i >= 150 && d == 2) {
		playerFish[0].size = 8;
		playerFish[0].sxw = 0.20;
		playerFish[0].syw = 0.20;
		playerFish[0].szw = 0.20;
		objects[24].sxw = 0.34;
		objects[24].syw = 0.34;
		objects[24].szw = 0.34;
		s = 1;
		effectAnim[3].countFrameTransform = 0;
		effectAnim[3].play();
		setLevel();
		d++;
	}
	if (s == 1) {
		effectAnim[3].txw = playerFish[0].txw;
		effectAnim[3].tyw = playerFish[0].tyw;
	}
	if (effectAnim[3].countFrameTransform == 10) {
		effectAnim[3].txw = 2;
		effectAnim[3].tyw = 2;
		effectAnim[3].countFrameTransform = 0;
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
	for (int i = 0; i < animNumLevel; i++) {
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
	
	for (int i = 1; i < animNumLevel - 1; i++) {
		for (int j = i + 1; j < animNumLevel; j++) {
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
	for (int i = 1; i < animNumLevel; i++) {
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
