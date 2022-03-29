#pragma once

#include "GameEntity.h"
#include "InputMgr.h"
#include "Background.h"
#include "Player.h"
#include "Fish.h"
#include "Scoreboard.h"
#include "GameoverScreen.h"
#include <fstream>
#include <vector>
class Level : public GameEntity {
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

	Player* player;
	bool playerHit;
	bool playerAte;

	AnimatedTex* gameOverLabel;
	bool gameOver;
	float gameOverDelay;
	float gameOverTimer;
	float gameOverOn;
	float gameOverOff;

	GameEntity* topBar;

	Texture* highScore;
	Scoreboard* highS;

	Texture* currentScore;
	Scoreboard* currS;

	int max = 0;
	int count = 0;
	bool prenderDone;

	std::vector<Fish*> fish;
	float waveTimer;
	float waveTimerOff;

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
	void WriteScore(std::string filename, int n);
	int ReadScore(std::string filename);
	void Push();
	void Pop();

public:
	Level(Player* p);
	~Level();

	level_states State();
	bool StageStarted();
	bool DoneDeathAnim();

	void Update();
	void Render();

};
