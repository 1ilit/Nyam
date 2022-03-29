#pragma once

#include "GameEntity.h"
#include "InputMgr.h"
#include "Background.h"
#include "Player.h"
#include "Fish.h"
#include "Scoreboard.h"
#include "GameoverScreen.h"
#include <vector>
class LevelTwoP : public GameEntity {
public:
	enum level_states {
		running,
		finished,
		gameover
	};

private:
	Timer* timer;
	Background* background;
	Texture* grass;

	int stage;
	bool stageStarted;

	float labelTimer;
	Texture* readyLabel;
	float readyOn;
	float readyOff;

	Player* player1;
	bool player1Hit;
	bool player1Ate;
	int lives1;

	Player* player2;
	bool player2Hit;
	bool player2Ate;
	int lives2;

	bool gameOver;
	float gameOverDelay;
	float gameOverTimer;
	float gameOverOn;
	float gameOverOff;

	bool levelOver;

	GameEntity* topBar;
	Texture* bar[9];
	Texture* cat1;
	Texture* cat2;

	int count1 = 0;
	int count2 = 0;

	int totalcount1;
	int totalcount2;

	bool prenderDone;

	std::vector<Fish*> fish;
	float waveTimer;
	float waveTimerOff;

	GameEntity* h1;
	Texture* health1[3];
	GameEntity* h2;
	Texture* health2[3];

	bool readyFinished;

	level_states currentState;

	GameoverScreen* g;

private:
	void HandleLabels();
	void HandleEating();
	void StartStage();
	void HandleDeath();
	void HandleCollisions();
	void HandleFishSpawning();
	void Push();

public:
	LevelTwoP(Player* p1, Player* p2);
	~LevelTwoP();

	level_states State();
	bool StageStarted();
	bool DoneDeathAnim();

	void Update();
	void Render();
};
