#include "stdafx.h"
#include "PlayerFish.h"
#include "SceneManager.h"
#include <time.h>
bool dis = false;
float x = 0;
PlayerFish::PlayerFish()
{
}

PlayerFish::~PlayerFish()
{
}

void PlayerFish::bite()
{
	if (signal == 3 && c == 0 && bite_wait == 0) {
		curent_texture = texture[4];
		play();
		signal = 0;
		bite_wait = 1;
		countFrame = 0;
		//scoreScene();
	}
	else if (signal == 3 && c == 1 && bite_wait == 0) {
		curent_texture = texture[5];
		play();
		signal = 0;
		bite_wait = 1;
		countFrame = 0;
		//scoreScene();
	}
	/*for (int i = 0; i < 3; i++) {
		Singleton<SceneManager>::GetInstance()->objects[i + 7].tyw += 0.002;
	}
	if (bite_wait == 0) {
		for (int i = 0; i < 3; i++) {
			Singleton<SceneManager>::GetInstance()->objects[i + 7].txw = 1.8;
			Singleton<SceneManager>::GetInstance()->objects[i + 7].tyw = 1.8;
		}
	}*/
}

void PlayerFish::disapear()
{
	if (disapear_wait == 1) {
		sxw = sx;
		syw = sy;
		szw = sz;
		txw = ((rand() % (100 - 0 + 1) + 0) - 50) / 100;
		tyw = 1.7;
		m_time = 0;
		dis = true;
	}
}


void PlayerFish::scoreScene(int i)
{	
	Singleton<SceneManager>::GetInstance()->objects[i+7].txw = txw + 0.02;
	Singleton<SceneManager>::GetInstance()->objects[i+7].tyw = tyw + 0.02;
}


void PlayerFish::update_animation_move_player(int x, int y)
{
	if (m_time < 300) {
		m_time++;
	}
	else {
		dis = false;
	}
	initShape();
	int v = 7;//vận tốc tính theo pixel ban đầu mặc định
	float a = (txw + 1.5) * Globals::screenWidth / 3;
	float b = (1.5 - tyw) * Globals::screenHeight / 3;//toa do vi tri cua player hien tai tinh theo pixel
	x_temp = a;
	y_temp = b;
	float j = x - a;//vector chi huong chuyen dong 
	float k = y - b;

	float cc, d;
	if ((j < -5 || j > 5) || (k < -5 || k > 5)) {
		cc = v*(float)j / sqrt(j * j + k * k);
		d = v*(float)k / sqrt(j * j + k * k);

		a += cc;//vị trí sau khi di chuyển
		b += d;

		txw = ((float)a / Globals::screenWidth) * 3.0 - 1.5;
		tyw = -(((float)b / Globals::screenHeight) * 3.0 - 1.5);
	}
	else {
		cc = 0; d = 0;
	}
	if (j <= -2 && c == 0) { // bat su kien ca quay dau
		countFrame = 0;
		c = 1;
		signal = 1;
	}
	else if (j > 2 && c == 1) {
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

void PlayerFish::update_animation_flash_player(int x, int y)
{
	if (m_time < 300) {
		m_time++;
	}
	else {
		dis = false;
	}
	initShape();
	int v = 15;//vận tốc tính theo pixel ban đầu mặc định
	float a = (txw + 1.5) * Globals::screenWidth / 3;
	float b = (1.5 - tyw) * Globals::screenHeight / 3;//toa do vi tri cua player hien tai tinh theo pixel
	x_temp = a;
	y_temp = b;
	float j = x - a;//vector chi huong chuyen dong 
	float k = y - b;
	float cc = v * (float)j / sqrt(j * j + k * k);
	float d = v * (float)k / sqrt(j * j + k * k);

	a += cc;//vị trí sau khi di chuyển
	b += d;

	txw = ((float)a / Globals::screenWidth) * 3.0 - 1.5;
	tyw = -(((float)b / Globals::screenHeight) * 3.0 - 1.5);
	if (j <= -5 && c == 0) { // bat su kien ca quay dau
		countFrame = 0;
		c = 1;
		signal = 1;
	}
	else if (j > 5 && c == 1) {
		countFrame = 0;
		signal = 1;
		c = 0;
	}
	zoom();
	turning();
	bite();

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

