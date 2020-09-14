#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "physic.h"
#include "PlayerFish.h"
#include "BotFish.h"
#include "EffectAnim.h"
#include <vector>
class Animation2D;
class PlayerFish;
class BotFish;
class EffectAnim;

using namespace std;

class SceneManager
{
public:
	float m_time = 0;
	float m_pTime = 0;
	int point = 0;
	int d = 0;
	int s = 0;
	Objects* objects;
	Animation2D* anim;
	PlayerFish* playerFish;
	BotFish* botFish;
	BotFish* modelBotFish;
	EffectAnim* effectAnim;
	int effectAnimNum;
	int objectNum;
	int countFrameScene = 0;
	int animNumLevel;
	int animNum;
	int modelBotFishNum;
	void setLevel();
	void loadObjects(char *l);
	void draw();
	void update_animation(float);
	void mouse_animation_move(int x, int y, float deltatime);
	void mouse_animation_flash(int x, int y, float deltatime);
	void updateScore();
	void LevelUp(int i);
	void free();
	void initBotFish();
	bool checkEvent();
	SceneManager();
	~SceneManager();
	bool checkCoRec(Rectangl rec, Circle cir);
	bool checkCoCirCir();
	bool checkColRecRec();
	void checkColRecRecP();
	static SceneManager* GetInstance(float);
private:
	static SceneManager* s_Instance;
};

