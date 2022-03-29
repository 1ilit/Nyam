#pragma once
#include "GameEntity.h"
#include "Timer.h"
#include "Background.h"
#include "Player.h"
#include "Scoreboard.h"
#include "AnimatedTex.h"
#include "InputMgr.h"
#include <fstream>

class GameoverScreen : public GameEntity{
public:
	enum Record {
		newrecord,
		same,
		grey,
		brown
	};

private:
	AnimatedTex* cat1;
	AnimatedTex* cat2;

	Texture* gameOverLabel;

	Texture* currentScore;
	Texture* highScore;
	Scoreboard* currS;
	Scoreboard* highS;

	Texture* youWon;
	Texture* yourTotal;
	Scoreboard* yourScore;
	
	Texture* controls;
	
	Texture* newRecord;
	Scoreboard* record;

	Record rec;

private:
	int ReadScore(std::string filename);

public:
	GameoverScreen();
	~GameoverScreen();

	void UpdateCurrent(int n);
	void UpdateRecord(int n);
	void UpdateMode(Record r);
	void UpdateTotal(int n);

	void Update();
	void Render();
};