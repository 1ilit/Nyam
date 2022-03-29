#pragma once
#include <SDL.h>
#include <string.h>

class InputMgr {
private:
	static InputMgr* instance;

	Uint8* prevKeyboardState;
	const Uint8* keyboardStates;
	int keyLen;

public:
	static InputMgr* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode sC);
	bool KeyPressed(SDL_Scancode sC);
	bool KeyReleased(SDL_Scancode sC);

	void UpdatePrevInput();

private:
	InputMgr();
	~InputMgr();

};