#include "ScreenMgr.h"

ScreenMgr* ScreenMgr::instance = NULL;

ScreenMgr* ScreenMgr::Instance() {
	if (instance == NULL)
		instance = new ScreenMgr();

	return instance;
}

void ScreenMgr::Release() {
	delete instance;
	instance = NULL;
}

ScreenMgr::ScreenMgr() {
	input = InputMgr::Instance();
	background = Background::Instance();
	startScreen = new StartScreen();
	onePlayerScreen = new OnePlayer();
	twoPlayerScreen = new TwoPlayer();

	currentScreen = start;
}

ScreenMgr::~ScreenMgr() {
	input = NULL;

	Background::Release();
	background = NULL;

	delete startScreen;
	startScreen = NULL;

	delete onePlayerScreen;
	onePlayerScreen = NULL;

	delete twoPlayerScreen;
	twoPlayerScreen = NULL;
}

void ScreenMgr::Update() {
	background->Update();

	switch (currentScreen) {
	case start:
		startScreen->Update();
		if (startScreen->SelectedMode() == 0 && input->KeyPressed(SDL_SCANCODE_RETURN)) {
			currentScreen = playOne;
			onePlayerScreen->Activate();
		}

		if (startScreen->SelectedMode() == 1 && input->KeyPressed(SDL_SCANCODE_RETURN)) {
			currentScreen = playTwo;
		}
		break;

	case playOne:
		onePlayerScreen->Update();
		if (input->KeyPressed(SDL_SCANCODE_ESCAPE) && !onePlayerScreen->GameOver()) {
			currentScreen = start;
		}
		if (onePlayerScreen->GameOver() && input->KeyPressed(SDL_SCANCODE_RETURN)) {
			currentScreen = start;
			onePlayerScreen->SetStartedLevel(false);
			onePlayerScreen->Activate();
			onePlayerScreen->Center();
		}
		break;
	case playTwo:
		twoPlayerScreen->Update();
		if (input->KeyPressed(SDL_SCANCODE_ESCAPE) && !onePlayerScreen->GameOver()) {
			currentScreen = start;
		}
		if (twoPlayerScreen->GameOver() && input->KeyPressed(SDL_SCANCODE_RETURN)) {
			currentScreen = start;
			twoPlayerScreen->SetStartedLevel(false);
			twoPlayerScreen->Activate();
			twoPlayerScreen->Center();
		}
		break;
	}
}

void ScreenMgr::Render() {
	background->Render();

	switch (currentScreen) {
	case start:
		startScreen->Render();
		break;
	case playOne:
		onePlayerScreen->Render();
		break;
	case playTwo:
		twoPlayerScreen->Render();
		break;
	}
}