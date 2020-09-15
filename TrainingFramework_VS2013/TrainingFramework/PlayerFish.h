#pragma once
#include "../Utilities/utilities.h"
#include "Animation2D.h"
#include "Game.h"

class PlayerFish: public Animation2D
{
public:
	int m_time = 201;
	bool dis = false;
	PlayerFish();
	~PlayerFish();
	int x_temp = (txw + 1.5) * Globals::screenWidth / 3;
	int y_temp = (1.5 - tyw) * Globals::screenHeight / 3;
	void bite();
	void disapear();
	void scoreScene(int);
	void update_animation_move_player(int x, int y);
	void update_animation_flash_player(int x, int y);
private:
};
