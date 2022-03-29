#pragma once
#include "GameEntity.h"
#include "Timer.h"
#include "Background.h"
#include "Player.h"
#include "Level.h"
#include "Scoreboard.h"
#include "AnimatedTex.h"
#include "InputMgr.h"
#include "Fish.h"
#include <iostream>
#include <fstream>

class OnePlayer :public GameEntity {
private:
	Timer* timer;
	InputMgr* input;

	Background* background;
	Texture* grass;

	float labelTimer;

	//---top bar

	GameEntity* topBar;
	Texture* highScore;
	Scoreboard* score;

	//---message---//
	
	//dinner's ready label
	Texture* dinner;
	float dinnerOn;
	float dinnerOff;

	//choose food
	Texture* instr;
	float instrOn;
	float instrOff;

	//controls
	GameEntity* conPanel;
	Texture* controls;
	Texture* esc;
	Texture* enterStart;
	float controlsOn;
	float controlsOff;

	Level* level;
	bool levelStarted;

	Player* cat;

	bool gameStarted;

private:
	void StartLevel();
	int ReadScore(std::string filename);

public:
	OnePlayer();
	~OnePlayer();

	void SetStartedLevel(bool b);
	bool GameOver();
	void Activate();
	void Center();
	
	void Update();
	void Render();

};
