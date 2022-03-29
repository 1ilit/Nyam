#pragma once

#include "AnimatedTex.h"
#include "Background.h"
#include "InputMgr.h"
#include "Cloud.h"
#include "Texture.h"

class StartScreen :public GameEntity {
private:
	Timer* timer;
	InputMgr* input;

	//top
	GameEntity* topBar;
	Texture* day;

	//logo
	AnimatedTex* animatedLogo;

	//play modes
	GameEntity* playModes;
	Texture* onePlayerMode;
	Texture* twoPlayerMode;
	Texture* cursor;
	Vector2 cursorStart;
	Vector2 cursorOffset;
	int selectedMode;

	//bot bar
	GameEntity* botBar;
	Texture* table;

	//kitty cats
	AnimatedTex* cat1;
	AnimatedTex* cat2;

	float moveSpeed;

	Background* background;

private:
	void HandleMovement(int x);

public:
	StartScreen();
	~StartScreen();

	int SelectedMode();

	void ChangeSelectedMode(int change);

	void Update();
	void Render();

};

