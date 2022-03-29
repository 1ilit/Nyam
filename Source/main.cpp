#include <iostream>
#include "GameManager.h"
#include <SDL.h>
#include <SDL_image.h>


int main(int argc, char* args[]) {

	GameManager* game = GameManager::Instance();

	game->Run();

	GameManager::Release();
	game = NULL;

	return 0;
}