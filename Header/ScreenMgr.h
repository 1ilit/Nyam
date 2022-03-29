#pragma once

#include "StartScreen.h"
#include "OnePlayer.h"
#include "TwoPlayer.h"

class ScreenMgr {
private:
	enum SCREEN {
		start,
		playOne,
		playTwo
	};

	Background* background;
	static ScreenMgr* instance;
	InputMgr* input;

	StartScreen* startScreen;
	OnePlayer* onePlayerScreen;
	TwoPlayer* twoPlayerScreen;

	SCREEN currentScreen;

public:
	static ScreenMgr* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenMgr();
	~ScreenMgr();
};
