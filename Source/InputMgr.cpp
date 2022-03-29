#include "InputMgr.h"

InputMgr* InputMgr::instance = NULL;

InputMgr* InputMgr::Instance() {
	if (instance == NULL)
		instance = new InputMgr();

	return instance;
}

void InputMgr::Release() {
	delete instance;
	instance = NULL;
}

InputMgr::InputMgr() {
	keyboardStates = SDL_GetKeyboardState(&keyLen);
	prevKeyboardState = new Uint8[keyLen];
	memcpy(prevKeyboardState, keyboardStates, keyLen);
}

InputMgr::~InputMgr() {
	delete[] prevKeyboardState;
	prevKeyboardState = NULL;
}

bool InputMgr::KeyDown(SDL_Scancode sC) {
	return keyboardStates[sC];
}

bool InputMgr::KeyPressed(SDL_Scancode sC) {
	return !prevKeyboardState[sC] && keyboardStates[sC];
}

bool InputMgr::KeyReleased(SDL_Scancode sC) {
	return prevKeyboardState[sC] && !keyboardStates[sC];
}

void InputMgr::UpdatePrevInput() {
	memcpy(prevKeyboardState, keyboardStates, keyLen);
}
