#pragma once
#include "GameEntity.h"
#include "Timer.h"
#include "Background.h"
#include "Player.h"
#include "LevelTwoP.h"
#include "AnimatedTex.h"
#include "InputMgr.h"
#include "Fish.h"
#include <iostream>
#include <fstream>

class TwoPlayer :public GameEntity {
private:
	Timer* timer;
	InputMgr* input;

	Background* background;
	Texture* grass;

	float labelTimer;

	//---message

	//dinner's ready label
	Texture* dinner;
	float dinnerOn;
	float dinnerOff;

	//choose food
	Texture* instr;
	float instrOn;
	float instrOff;

	//controls

	GameEntity* conPanel1;
	Texture* controls;

	GameEntity* conPanel2;
	Texture* controls2;

	Texture* esc;
	Texture* enterStart;

	float controlsOn;
	float controlsOff;

	LevelTwoP* level;

	Player* cat1;
	Player* cat2;

	bool levelStarted;
	bool gameStarted;

private:
	void StartLevel();

public:
	TwoPlayer();
	~TwoPlayer();

	void SetStartedLevel(bool b);
	bool GameOver();
	void Activate();
	void Center();

	void Update();
	void Render();

};

