#pragma once
#include "Timer.h"
#include "Graphics.h"
#include "Texture.h"
#include "InputMgr.h"
#include "Cloud.h"
#include "AnimatedTex.h"
#include "AssetMgr.h"
#include "ScreenMgr.h"
#include "StartScreen.h"

class GameManager {
private:
	static GameManager* instance;
	const int frameRate = 60;
	bool quit;

	Timer* timer;
	SDL_Event e;

	Graphics* graphics;
	AssetMgr* assetMgr;
	InputMgr* inputMgr;
	Cloud* clouds[25];

	ScreenMgr* screenMgr;

public:
	static GameManager* Instance();
	static void Release();

	void Run();

private:
	GameManager();
	~GameManager();

	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();

};

