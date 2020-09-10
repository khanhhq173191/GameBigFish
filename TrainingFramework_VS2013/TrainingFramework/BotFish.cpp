﻿#include "stdafx.h"
#include "BotFish.h"
#include "SceneManager.h"
#include <time.h>

BotFish::BotFish()
{
}

BotFish::~BotFish()
{
}

void BotFish::bite()
{
		if (signal == 3 && c == 0 && bite_wait == 0) {
			curent_texture = texture[4];
			play();
			//countFrame = 0;
			signal = 0;
			bite_wait = 1;
		}
		else if (signal == 3 && c == 1 && bite_wait == 0) {
			curent_texture = texture[5];
			play();
			//countFrame = 0;
			signal = 0;
			bite_wait = 1;
		}
}

void BotFish::disapear()
{
	if (disapear_wait == 1) {
		sxw = sx;
		syw = sy;
		szw = sz;
		int res = rand() % (4 - 1 + 1) + 1;
		if (res == 1) {
			srand(time(NULL));
			txw = -(rand() % (320 - 300 + 1) + 300) / 100.0000;
			tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 2) {
			txw = (rand() % (320 - 300 + 1) + 300) / 100.0000;
			tyw = ((rand() % (640 - 0 + 1) + 0) - 300) / 100.0000;
		}
		else if (res == 3) {
			txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			tyw = (rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
		else if (res == 4) {
			txw = ((rand() % (600 - 0 + 1) + 0) - 300) / 100.0000;
			tyw = -(rand() % (640 - 300 + 1) + 300) / 100.0000;
		}
	}
	for (int i = 0; i < 12; i++) {
		Singleton<SceneManager>::GetInstance()->objects[i + 7].tyw += 0.002;
	}
	if (frameCountScore == 12) {
		for (int i = 0; i < 12; i++) {
			Singleton<SceneManager>::GetInstance()->objects[i + 7].txw = 1.8;
			Singleton<SceneManager>::GetInstance()->objects[i + 7].tyw = 1.8;
		}
	}
}

void BotFish::scoreScene(int i)
{
	switch (size)
	{
	case 1:
		Singleton<SceneManager>::GetInstance()->objects[i + 7].txw = txw;
		Singleton<SceneManager>::GetInstance()->objects[i + 7].tyw = tyw;
		Singleton<SceneManager>::GetInstance()->point += 10;
		break;
	case 3:
		Singleton<SceneManager>::GetInstance()->objects[i + 11].txw = txw;
		Singleton<SceneManager>::GetInstance()->objects[i + 11].tyw = tyw;
		Singleton<SceneManager>::GetInstance()->point += 20;
		break;
	case 5:
		Singleton<SceneManager>::GetInstance()->objects[i + 15].txw = txw;
		Singleton<SceneManager>::GetInstance()->objects[i + 15].tyw = tyw ;
		Singleton<SceneManager>::GetInstance()->point += 50;
		break;
	case 7:
		Singleton<SceneManager>::GetInstance()->point += 100;
		break;
	default:
		break;
	}
}

void BotFish::update_animation_move_boss(float deltaTime)
{
	frameCountScore++;
	initShape();
	float a = (txw + 1.5) * Globals::screenWidth / 3;
	float b = (1.5 - tyw) * Globals::screenHeight / 3;//toa do vi tri cua player hien tai tinh theo pixel
	x_temp = a;
	y_temp = b;
	SetVectorh(a, b, deltaTime);
	float j = m_hx;//vector chi huong chuyen dong
	float k = m_hy;
	float cc = vb * (float)j / sqrt(j * j + k * k);
	float d = vb * (float)k / sqrt(j * j + k * k);

	a += cc;//vị trí sau khi di chuyển
	b += d;

	txw = ((float)a / Globals::screenWidth) * 3.0 - 1.5;
	tyw = -(((float)b / Globals::screenHeight) * 3.0 - 1.5);
	if (j <= 0 && c == 0) { // bat su kien ca quay dau
		countFrame = 0;
		c = 1;
		signal = 1;
	}
	else if (j > 0 && c == 1) {
		countFrame = 0;
		signal = 1;
		c = 0;
	}
	turning();
	bite();
	zoom();
	if (countFrame == 5 && c == 1) {
		curent_texture = texture[1];
		play();
		countFrame = 0;
		signal = 0;
		bite_wait = 0;
		disapear_wait = 0;
	}
	else if (countFrame == 5 && c == 0) {
		curent_texture = texture[0];
		play();
		countFrame = 0;
		signal = 0;
		bite_wait = 0;
		disapear_wait = 0;
	}
}
